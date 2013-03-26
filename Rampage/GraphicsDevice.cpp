#include "stdafx.h"
#include <memory>
#include "GraphicsDevice.h"
#include "HResultWrapper.h"
#include "Window.h"

// Just to make lines a bit shorter..
using std::unique_ptr;

GraphicsDevice::GraphicsDevice(void)
{
}

GraphicsDevice::~GraphicsDevice(void)
{
}

static void SetupSwapChainDesc(DXGI_SWAP_CHAIN_DESC* SwapChainDesc, Window* OutputWindow)
{
    int width, height;
    OutputWindow->GetSize(&width, &height);

    ZeroMemory(SwapChainDesc, sizeof(*SwapChainDesc));

    SwapChainDesc->BufferCount = 1;
    
    SwapChainDesc->BufferDesc.Width = width;
    SwapChainDesc->BufferDesc.Height = height;
    SwapChainDesc->BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SwapChainDesc->BufferDesc.RefreshRate.Numerator = 60;
    SwapChainDesc->BufferDesc.RefreshRate.Denominator = 1;
    
    SwapChainDesc->BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    SwapChainDesc->OutputWindow = OutputWindow->GetHandle();

    SwapChainDesc->SampleDesc.Count = 1;
    SwapChainDesc->SampleDesc.Quality = 0;

    SwapChainDesc->Windowed = TRUE;
}

void GraphicsDevice::InitializeD3D(Window* OutputWindow)
{
    DXGI_SWAP_CHAIN_DESC sd;
    SetupSwapChainDesc(&sd, OutputWindow);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };
    UINT featureLevelCount = ARRAYSIZE(featureLevels);

    UINT deviceFlags = 0;
#ifdef _DEBUG
    deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    HResultWrapper hr;

    hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        deviceFlags, featureLevels, featureLevelCount, D3D11_SDK_VERSION, &sd,
        &m_SwapChain, &m_Device, &m_CurrentFeatureLevel, &m_ImmediateContext);

    m_Helpers.Device = m_Device;

    InitRenderContext();
}

RenderTarget* GraphicsDevice::InitBackbufferRenderTarget()
{
    ID3D11Texture2DPtr backbuffer;
    HResultWrapper hr;

    hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backbuffer));
    
    // The backbuffer won't be used as a shader resource, so don't create an SRV from it.
    return RenderTarget::Create(m_Device, backbuffer, RT_NOT_SHADER_RESOURCE);
}

unique_ptr<GraphicsDevice> GraphicsDevice::Create(Window* OutputWindow)
{
    unique_ptr<GraphicsDevice> gfxDevice(new GraphicsDevice());

    gfxDevice->InitializeD3D(OutputWindow);

    return gfxDevice;
}

void GraphicsDevice::InitRenderContext()
{
    auto backbufferRT = InitBackbufferRenderTarget();
    m_RenderContext.reset(new RenderContext(m_ImmediateContext, m_SwapChain, backbufferRT));
}

RenderContext* GraphicsDevice::GetRenderContext()
{
    return m_RenderContext.get();
}

unique_ptr<RenderTarget> GraphicsDevice::CreateGBuffer(int Width, int Height)
{
    unique_ptr<RenderTarget> ret;

    DXGI_FORMAT bufferFormats[] =
    {
        DXGI_FORMAT_R8G8B8A8_UNORM,
        DXGI_FORMAT_R8G8B8A8_UNORM,
    };

    ret.reset(RenderTarget::Create(m_Device, Width, Height, ArrayRef<DXGI_FORMAT>(bufferFormats,
        NUM_GBUFFER_RENDER_TARGETS), RT_CREATE_DEPTH_STENCIL));

    return ret;
}

unique_ptr<PixelShader> GraphicsDevice::CreatePixelShader(const void* ShaderData, int ShaderDataSize)
{
    auto result = m_Helpers.CreatePixelShader(ShaderData, ShaderDataSize);
    
    return unique_ptr<PixelShader>(new PixelShader(result));
}

unique_ptr<VertexShader> GraphicsDevice::CreateVertexShader(const void* ShaderData, int ShaderDataSize)
{
    auto result = m_Helpers.CreateVertexShader(ShaderData, ShaderDataSize);
    
    return unique_ptr<VertexShader>(new VertexShader(result));
}

unique_ptr<VertexBuffer> GraphicsDevice::CreateVertexBuffer(int Size, int Stride, const void* Data)
{
    CD3D11_BUFFER_DESC desc(Size * Stride, D3D11_BIND_VERTEX_BUFFER);
    D3D11_SUBRESOURCE_DATA data;

    data.pSysMem = Data;
    data.SysMemPitch = 0;
    data.SysMemSlicePitch = 0;

    ID3D11BufferPtr buffer = m_Helpers.CreateBuffer(desc, &data);

    return unique_ptr<VertexBuffer>(new VertexBuffer(buffer, Size, Stride));
}

unique_ptr<IndexBuffer> GraphicsDevice::CreateIndexBuffer(ArrayRef<unsigned int> Data) 
{
    CD3D11_BUFFER_DESC desc(Data.size() * sizeof(unsigned int), D3D11_BIND_INDEX_BUFFER);
    D3D11_SUBRESOURCE_DATA data;

    data.pSysMem = Data.data();
    data.SysMemPitch = 0;
    data.SysMemSlicePitch = 0;

    ID3D11BufferPtr buffer = m_Helpers.CreateBuffer(desc, &data);

    return unique_ptr<IndexBuffer>(new IndexBuffer(buffer, Data.size()));
}
