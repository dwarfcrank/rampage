#pragma once

#include <memory>
#include <d3d11.h>

#include "ComPtrDef.h"

/// <summary>   A simple render target class, used mainly for wrapping the backbuffer
///             or similar outputs. 
///             Does not provide a depth stencil buffer, use a GBuffer for more complex
///             rendering tasks.</summary>
class RenderTarget
{
public:
    ~RenderTarget(void);

    static RenderTarget* Create(ID3D11Device* Device, ID3D11Texture2DPtr Texture);

    void Bind(ID3D11DeviceContext* DeviceContext);
    void Clear(ID3D11DeviceContext* DeviceContext, const float Color[4]);

private:
    RenderTarget(void);

    ID3D11RenderTargetViewPtr m_RenderTargetView;
    D3D11_VIEWPORT m_Viewport;
};

