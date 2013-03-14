#include "stdafx.h"
#include <memory>
#include "GraphicsDevice.h"
#include "HResultWrapper.h"
#include "Window.h"

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
}

GraphicsDevice* GraphicsDevice::Create(Window* OutputWindow)
{
	std::unique_ptr<GraphicsDevice> gfxDevice(new GraphicsDevice());

	gfxDevice->InitializeD3D(OutputWindow);

	return gfxDevice.release();
}