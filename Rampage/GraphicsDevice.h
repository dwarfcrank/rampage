#pragma once

#include <d3d11.h>
#include "ComPtrDef.h"
#include "RenderTarget.h"
#include "RenderContext.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "D3DHelpers.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Window;

/// <summary>   The graphics device class is used for creating various resources,
///             similar to the D3D device. </summary>
class GraphicsDevice
{
public:
    ~GraphicsDevice(void);

    /// <summary>   Creates a graphics device. </summary>
    ///
    /// <param name="OutputWindow"> [in] The render output window. </param>
    ///
    /// <returns>   null if it fails, else the created graphics device. </returns>
    static GraphicsDevice* Create(Window* OutputWindow);

    RenderContext* GetRenderContext();

    RenderTarget* CreateGBuffer(int Width, int Height);

    PixelShader* CreatePixelShader(const void* ShaderData, int ShaderDataSize);
    VertexShader* CreateVertexShader(const void* ShaderData, int ShaderDataSize);

    // Note: Size is in _elements_
    VertexBuffer* CreateVertexBuffer(int Size, int Stride, const void* Data);
    IndexBuffer* CreateIndexBuffer(ArrayRef<unsigned int> Data);

private:
    GraphicsDevice(void);

    void InitializeD3D(Window* OutputWindow);
    RenderTarget* InitBackbufferRenderTarget();

    void InitRenderContext();

    std::unique_ptr<RenderContext> m_RenderContext;

    ID3D11DevicePtr m_Device;
    ID3D11DeviceContextPtr m_ImmediateContext;
    IDXGISwapChainPtr m_SwapChain;

    std::unique_ptr<RenderTarget> m_BackbufferRT;

    D3DHelpers m_Helpers;

    D3D_FEATURE_LEVEL m_CurrentFeatureLevel;
};

// This function is separate from the GraphicsDevice class, because the class will
// be hidden behind an interface class later.
template<typename TVertex>
VertexBuffer* CreateVertexBuffer(GraphicsDevice* Device, ArrayRef<TVertex> Vertices)
{
    return Device->CreateVertexBuffer(Vertices.size(), sizeof(TVertex), Vertices.data());
}
