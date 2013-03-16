#pragma once

#include <d3d11.h>
#include <memory>
#include "ComPtrDef.h"
#include "RenderTarget.h"

class RenderContext
{
public:
    RenderContext(ID3D11DeviceContextPtr DeviceContext, IDXGISwapChainPtr SwapChain,
        RenderTarget* BackbufferRenderTarget);
    ~RenderContext(void);

    void BeginFrame();
    void EndFrame();

    void BindBackbufferRenderTarget();

private:
    ID3D11DeviceContextPtr m_DeviceContext;
    IDXGISwapChainPtr m_SwapChain;
    std::unique_ptr<RenderTarget> m_BackbufferRT;
};

