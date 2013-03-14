#pragma once

#include <d3d11.h>
#include "ComPtrDef.h"

class Window;

class GraphicsDevice
{
public:
	~GraphicsDevice(void);

	static GraphicsDevice* Create(Window* OutputWindow);

private:
	GraphicsDevice(void);

	void InitializeD3D(Window* OutputWindow);

	ID3D11DevicePtr m_Device;
	ID3D11DeviceContextPtr m_ImmediateContext;
	IDXGISwapChainPtr m_SwapChain;

	D3D_FEATURE_LEVEL m_CurrentFeatureLevel;
};

