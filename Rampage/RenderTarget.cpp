#include "stdafx.h"
#include "RenderTarget.h"
#include "D3DHelpers.h"

RenderTarget::RenderTarget(void) 
{
}

RenderTarget::~RenderTarget(void)
{
}

static ID3D11DepthStencilViewPtr CreateDepthStencilView(D3DHelpers* Helpers, ID3D11Texture2D* Texture)
{
    D3D11_TEXTURE2D_DESC textureDesc;
    Texture->GetDesc(&textureDesc);

    _ASSERTE(textureDesc.Format == DXGI_FORMAT_R24G8_TYPELESS);

    CD3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc(D3D11_DSV_DIMENSION_TEXTURE2D, textureDesc.Format);

    return Helpers->CreateDepthStencilView(Texture, dsvDesc);
}

static void CreateShaderResourceViews(D3DHelpers* Helpers, int Count, ID3D11Texture2DPtr Textures[],
                                      ID3D11ShaderResourceViewPtr ShaderResourceViews[])
{
    // The shader resource view for the depth stencil buffer is created separately,
    // no need to check for it here.
    for(int i = 0; i < Count; i++)
    {
        ShaderResourceViews[i] = Helpers->CreateShaderResourceView(Textures[i]);
    }
}

RenderTarget* RenderTarget::Create(ID3D11Device* Device, ID3D11Texture2D* Texture, UINT Flags,
                                   ID3D11Texture2D* DepthTexture)
{
    std::unique_ptr<RenderTarget> renderTarget(new RenderTarget());
    D3DHelpers helpers(Device);

    D3D11_TEXTURE2D_DESC desc;
    Texture->GetDesc(&desc);   

    _ASSERTE(desc.BindFlags & D3D11_BIND_RENDER_TARGET);

    D3D11_VIEWPORT& vp = renderTarget->m_Viewport;
    vp.Width = static_cast<float>(desc.Width);
    vp.Height = static_cast<float>(desc.Height);
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MaxDepth = 1.0f;
    vp.MinDepth = 0.0f;

    renderTarget->m_RenderTargetViews.push_back(helpers.CreateRenderTargetView(Texture));
    
    if(DepthTexture)
    {
        renderTarget->m_DepthStencilView = CreateDepthStencilView(&helpers, DepthTexture);
    }

    if(!(Flags & RT_NOT_SHADER_RESOURCE))
    {
        _ASSERTE(desc.BindFlags & D3D11_BIND_SHADER_RESOURCE);

        renderTarget->m_ShaderResourceViews.push_back(helpers.CreateShaderResourceView(Texture));

        CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION_TEXTURE2D, DXGI_FORMAT_R24_UNORM_X8_TYPELESS);
        renderTarget->m_DepthStencilSRV = helpers.CreateShaderResourceView(DepthTexture, &srvDesc);
    }

    return renderTarget.release();
}

RenderTarget* RenderTarget::Create(ID3D11Device* Device, int Width, int Height, int NumTextures,
                                   const DXGI_FORMAT* TextureFormats, UINT Flags) 
{
    D3DHelpers helpers(Device);
    std::unique_ptr<RenderTarget> renderTarget(new RenderTarget());

    renderTarget->m_RenderTargetViews.reserve(NumTextures);
    
    CD3D11_TEXTURE2D_DESC textureDesc(DXGI_FORMAT_UNKNOWN, Width, Height);
    textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET;

    bool createSRVs = !(Flags & RT_NOT_SHADER_RESOURCE);
    if(createSRVs)
    {
        renderTarget->m_ShaderResourceViews.reserve(NumTextures);
        textureDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    }

    for(int i = 0; i < NumTextures; i++)
    {
        textureDesc.Format = TextureFormats[i];

        ID3D11Texture2DPtr texture = helpers.CreateTexture2D(textureDesc);
        renderTarget->m_RenderTargetViews.push_back(helpers.CreateRenderTargetView(texture));

        if(createSRVs)
        {
            renderTarget->m_ShaderResourceViews.push_back(helpers.CreateShaderResourceView(texture));
        }
    }
    
    if(Flags & RT_CREATE_DEPTH_STENCIL)
    {
        textureDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
        textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

        if(createSRVs)
        {
            textureDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
        }

        ID3D11Texture2DPtr depthTexture = helpers.CreateTexture2D(textureDesc);

        CD3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc(D3D11_DSV_DIMENSION_TEXTURE2D, DXGI_FORMAT_D24_UNORM_S8_UINT);
        renderTarget->m_DepthStencilView = helpers.CreateDepthStencilView(depthTexture, dsvDesc);

        if(createSRVs)
        {
            CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION_TEXTURE2D, DXGI_FORMAT_R24_UNORM_X8_TYPELESS);
            renderTarget->m_DepthStencilSRV = helpers.CreateShaderResourceView(depthTexture, &srvDesc);
        }
    }

    D3D11_VIEWPORT& vp = renderTarget->m_Viewport;
    vp.Width = static_cast<float>(Width);
    vp.Height = static_cast<float>(Height);
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MaxDepth = 1.0f;
    vp.MinDepth = 0.0f;

    return renderTarget.release();
}

void RenderTarget::Bind(ID3D11DeviceContext* DeviceContext)
{
    ID3D11RenderTargetView* rtvs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
    D3D11_VIEWPORT viewports[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];

    int count = m_RenderTargetViews.size();
    
    for(int i = 0; i < count; i++)
    {
        rtvs[i] = m_RenderTargetViews[i];
        viewports[i] = m_Viewport;
    }

    DeviceContext->OMSetRenderTargets(count, rtvs, m_DepthStencilView);
    DeviceContext->RSSetViewports(count, viewports);
}

void RenderTarget::BindAsShaderResource(ID3D11DeviceContext* DeviceContext)
{
    int count = m_ShaderResourceViews.size();
    ID3D11ShaderResourceView* srvs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT + 1];

    for(int i = 0; i < count; i++)
    {
        srvs[i] = m_ShaderResourceViews[i];
    }

    if(m_DepthStencilSRV)
    {
        srvs[count] = m_DepthStencilSRV;
        count++;
    }

    DeviceContext->PSSetShaderResources(0, count, srvs);
}

void RenderTarget::Clear(ID3D11DeviceContext* DeviceContext, const float Color[4])
{
    int count = m_RenderTargetViews.size();

    for(int i = 0; i < count; i++)
    {
        DeviceContext->ClearRenderTargetView(m_RenderTargetViews[i], Color);
    }

    if(m_DepthStencilView)
    {
        DeviceContext->ClearDepthStencilView(m_DepthStencilView, 0, 1.0f, 0);
    }
}

bool RenderTarget::IsShaderResource() const
{
    return !m_ShaderResourceViews.empty();
}

bool RenderTarget::HasDepthStencil() const
{
    return m_DepthStencilView != nullptr;
}

int RenderTarget::GetBufferSRVCount() const
{
    int ret = m_ShaderResourceViews.size();

    // The depth stencil shader resource view is stored separately from the other buffers,
    // so take that into account.
    if(m_DepthStencilSRV)
    {
        return ret + 1;
    }

    return ret;
}