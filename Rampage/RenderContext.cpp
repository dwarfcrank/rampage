#include "stdafx.h"
#include "RenderContext.h"

RenderContext::RenderContext(ID3D11DeviceContextPtr DeviceContext, IDXGISwapChainPtr SwapChain,
        RenderTarget* BackbufferRenderTarget) :
    m_DeviceContext(DeviceContext),
    m_SwapChain(SwapChain),
    m_BackbufferRT(BackbufferRenderTarget),
    m_ActiveRenderTarget(nullptr)
{
    InitInputLayouts();
}

RenderContext::~RenderContext(void)
{
}

void RenderContext::BindBackbufferRenderTarget()
{
    m_BackbufferRT->Bind(m_DeviceContext);
}

void RenderContext::BindRenderTarget(RenderTarget* RenderTarget)
{
    m_ActiveRenderTarget = RenderTarget;

    if(!RenderTarget)
    {
        // Unbind all render targets.
        m_DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
        return;
    }

    if(m_ActiveRenderTargetSRV == RenderTarget)
    {
        // The render target is bound for reading, unbind it
        int count = RenderTarget->GetBufferSRVCount();

        ID3D11ShaderResourceView* resources[8];
        ZeroMemory(resources, sizeof(resources));

        m_DeviceContext->PSSetShaderResources(0, count, resources);
        m_ActiveRenderTargetSRV = nullptr;
    }

    RenderTarget->Bind(m_DeviceContext);
}

void RenderContext::BindRenderTargetAsShaderResource(RenderTarget* RenderTarget)
{
    // If this render target is bound for writing, unbind it first.
    if(m_ActiveRenderTarget == RenderTarget)
    {
        BindRenderTarget(nullptr);
    }

    m_ActiveRenderTargetSRV = RenderTarget;
    RenderTarget->BindAsShaderResource(m_DeviceContext);
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

void RenderContext::SetPixelShader(PixelShader* Shader)
{
    m_DeviceContext->PSSetShader(Shader->GetShader(), nullptr, 0);
}

void RenderContext::SetVertexShader(VertexShader* Shader)
{
    m_DeviceContext->VSSetShader(Shader->GetShader(), nullptr, 0);
}

void RenderContext::BindVertexBuffers(int Count, VertexBuffer** Buffers)
{
    ID3D11Buffer* buffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
    UINT strides[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
    UINT offsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT] = { 0 };

    for(int i = 0; i < Count; i++)
    {
        buffers[i] = Buffers[i]->GetBuffer();
        strides[i] = Buffers[i]->GetStride();
    }

    m_DeviceContext->IASetVertexBuffers(0, Count, buffers, strides, offsets);
}

void RenderContext::Draw(int VertexCount)
{
    m_DeviceContext->IASetInputLayout(m_InputLayouts[0]);
    m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_DeviceContext->Draw(VertexCount, 0);
}