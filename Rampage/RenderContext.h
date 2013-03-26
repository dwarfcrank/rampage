#pragma once

#include <d3d11.h>
#include <memory>
#include "ComPtrDef.h"
#include "RenderTarget.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

enum InputLayoutIndex
{
    IL_MESH = 0,
    NUM_INPUT_LAYOUTS
};

class RenderContext
{
public:
    RenderContext(ID3D11DeviceContextPtr DeviceContext, IDXGISwapChainPtr SwapChain,
        RenderTarget* BackbufferRenderTarget);
    ~RenderContext(void);

    void BeginFrame();
    void EndFrame();

    void BindBackbufferRenderTarget();
    
    void SetPixelShader(PixelShader* Shader);
    void SetVertexShader(VertexShader* Shader);

    void BindRenderTarget(RenderTarget* Target);
    void BindRenderTargetAsShaderResource(RenderTarget* Target);

    void BindVertexBuffers(ArrayRef<std::unique_ptr<VertexBuffer>> Buffers);
    void BindIndexBuffer(IndexBuffer* Buffer);

    void Draw(int VertexCount);

private:
    void InitInputLayouts();

    ID3D11DeviceContextPtr m_DeviceContext;
    IDXGISwapChainPtr m_SwapChain;
    std::unique_ptr<RenderTarget> m_BackbufferRT;
    
    RenderTarget* m_ActiveRenderTarget;
    RenderTarget* m_ActiveRenderTargetSRV;

    ID3D11InputLayoutPtr m_InputLayouts[NUM_INPUT_LAYOUTS];
};

