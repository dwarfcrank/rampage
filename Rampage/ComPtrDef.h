#pragma once

#include <windows.h>
#include <comdef.h>
#include <d3d11.h>
#include <dxgi.h>

#define COM_PTR_TYPEDEF(iface) _COM_SMARTPTR_TYPEDEF(iface, __uuidof(iface))

COM_PTR_TYPEDEF(ID3D11Device);
COM_PTR_TYPEDEF(ID3D11DeviceContext);