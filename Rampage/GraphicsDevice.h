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

	ID3D11DevicePtr m_Device;
	ID3D11DeviceContextPtr m_ImmediateContext;
};

