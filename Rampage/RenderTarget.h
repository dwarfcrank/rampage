#pragma once

#include <memory>
#include <vector>
#include <d3d11.h>

#include "ComPtrDef.h"

enum RenderTargetCreateFlags
{
    RT_CREATE_DEPTH_STENCIL =   (1 << 0),
    RT_NOT_SHADER_RESOURCE =    (1 << 1),
};

enum GBufferRenderTargets
{
    GBRT_DIFFUSE_SPECULAR_INTENSITY = 0,
    GBRT_NORMAL_SPECULAR_POWER,
    NUM_GBUFFER_RENDER_TARGETS,
};

/// <summary>   A render target class, encapsulating one or more textures and optionally a depth
///             stencil buffer. 
/// </summary>
class RenderTarget
{
public:
    ~RenderTarget(void);

    // Create a render target from an existing texture
    static RenderTarget* Create(ID3D11Device* Device, ID3D11Texture2D* Texture, UINT Flags = 0,
        ID3D11Texture2D* DepthTexture = nullptr);

    static RenderTarget* Create(ID3D11Device* Device, int Width, int Height, int NumTextures,
        const DXGI_FORMAT* TextureFormats, UINT Flags = 0);

    void Bind(ID3D11DeviceContext* DeviceContext);
    void BindAsShaderResource(ID3D11DeviceContext* DeviceContext);
    int GetBufferSRVCount() const;

    void Clear(ID3D11DeviceContext* DeviceContext, const float Color[4]);

    bool IsShaderResource() const;
    bool HasDepthStencil() const;

private:
    RenderTarget(void);

    std::vector<ID3D11RenderTargetViewPtr> m_RenderTargetViews;
    std::vector<ID3D11ShaderResourceViewPtr> m_ShaderResourceViews;
    ID3D11DepthStencilViewPtr m_DepthStencilView;
    ID3D11ShaderResourceViewPtr m_DepthStencilSRV;

    D3D11_VIEWPORT m_Viewport;
};

