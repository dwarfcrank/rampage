#include "stdafx.h"
#include "RenderTarget.h"
#include "D3DHelpers.h"

RenderTarget::RenderTarget(void)
{
}

RenderTarget::~RenderTarget(void)
{
}

RenderTarget* RenderTarget::Create(ID3D11Device* Device, ID3D11Texture2DPtr Texture)
{
    std::unique_ptr<RenderTarget> renderTarget(new RenderTarget());
    D3DHelpers helpers(Device);

    D3D11_TEXTURE2D_DESC desc;
    Texture->GetDesc(&desc);   

    D3D11_VIEWPORT& vp = renderTarget->m_Viewport;
    vp.Width = static_cast<float>(desc.Width);
    vp.Height = static_cast<float>(desc.Height);
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MaxDepth = 1.0f;
    vp.MinDepth = 0.0f;

    renderTarget->m_RenderTargetView = helpers.CreateRenderTargetView(Texture);

    return renderTarget.release();
}

void RenderTarget::Bind(ID3D11DeviceContext* DeviceContext)
{
    ID3D11RenderTargetView* rtv = m_RenderTargetView;

    DeviceContext->OMSetRenderTargets(1, &rtv, nullptr);
    DeviceContext->RSSetViewports(1, &m_Viewport);
}

void RenderTarget::Clear(ID3D11DeviceContext* DeviceContext, const float Color[4])
{
    DeviceContext->ClearRenderTargetView(m_RenderTargetView, Color);
}