#include "stdafx.h"
#include "RenderContext.h"

RenderContext::RenderContext(ID3D11DeviceContextPtr DeviceContext, IDXGISwapChainPtr SwapChain,
        RenderTarget* BackbufferRenderTarget) :
    m_DeviceContext(DeviceContext),
    m_SwapChain(SwapChain),
    m_BackbufferRT(BackbufferRenderTarget)
{
}

RenderContext::~RenderContext(void)
{
}

void RenderContext::BindBackbufferRenderTarget()
{
    m_BackbufferRT->Bind(m_DeviceContext);
}

void RenderContext::BeginFrame()
{
    float color[] = { 0.1f, 0.2f, 0.3f, 1.0f };
    m_BackbufferRT->Clear(m_DeviceContext, color);
}

void RenderContext::EndFrame()
{
    m_SwapChain->Present(0, 0);
}
