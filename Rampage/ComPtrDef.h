#pragma once

#include <windows.h>
#include <comdef.h>
#include <d3d11.h>
#include <dxgi.h>

#define COM_PTR_TYPEDEF(iface) _COM_SMARTPTR_TYPEDEF(iface, __uuidof(iface))

COM_PTR_TYPEDEF(ID3D11Device);
COM_PTR_TYPEDEF(ID3D11DeviceContext);

COM_PTR_TYPEDEF(IDXGISwapChain);

COM_PTR_TYPEDEF(ID3D11Texture2D);

COM_PTR_TYPEDEF(ID3D11RenderTargetView);
COM_PTR_TYPEDEF(ID3D11DepthStencilView);
COM_PTR_TYPEDEF(ID3D11ShaderResourceView);

COM_PTR_TYPEDEF(ID3D11VertexShader);
COM_PTR_TYPEDEF(ID3D11PixelShader);

COM_PTR_TYPEDEF(ID3D11Buffer);

COM_PTR_TYPEDEF(ID3D11InputLayout);