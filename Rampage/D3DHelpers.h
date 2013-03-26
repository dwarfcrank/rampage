#pragma once

#include "ComPtrDef.h"
#include "ArrayRef.h"

/// <summary>
///     Basic wrapper class for ID3D11Device to simplify resource creation. Instead of returning
///     a HRESULT and outputting the resulting interface via a pointer, it simply checks the
///     HRESULT by itself and returns the created interface.
/// </summary>
struct D3DHelpers
{
    D3DHelpers(ID3D11Device* Device = nullptr);	

    ID3D11Texture2DPtr CreateTexture2D(const D3D11_TEXTURE2D_DESC& Desc,
                                       const D3D11_SUBRESOURCE_DATA* InitialData = nullptr);

    ID3D11RenderTargetViewPtr CreateRenderTargetView(ID3D11Texture2D* Texture,
                                                     const D3D11_RENDER_TARGET_VIEW_DESC* Desc = nullptr);

    ID3D11DepthStencilViewPtr CreateDepthStencilView(ID3D11Texture2D* Texture,
                                                     const D3D11_DEPTH_STENCIL_VIEW_DESC& Desc);

    ID3D11ShaderResourceViewPtr CreateShaderResourceView(ID3D11Resource* Resource,
                                                         const D3D11_SHADER_RESOURCE_VIEW_DESC* Desc = nullptr);

    ID3D11VertexShaderPtr CreateVertexShader(ArrayRef<BYTE> Bytecode);
    ID3D11VertexShaderPtr CreateVertexShader(const void* Bytecode, int BytecodeSize);

    ID3D11PixelShaderPtr CreatePixelShader(ArrayRef<BYTE> Bytecode);
    ID3D11PixelShaderPtr CreatePixelShader(const void* Bytecode, int BytecodeSize);

    ID3D11BufferPtr CreateBuffer(const D3D11_BUFFER_DESC& Desc,
                                 const D3D11_SUBRESOURCE_DATA* InitialData = nullptr);
                                    
    ID3D11InputLayoutPtr CreateInputLayout(ArrayRef<D3D11_INPUT_ELEMENT_DESC> InputElements,
        ArrayRef<BYTE> ShaderBytecode);


    // Not a smart pointer - we don't need to hold a reference to the device.
    ID3D11Device* Device;
};