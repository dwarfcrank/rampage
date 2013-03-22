#include "stdafx.h"
#include "D3DHelpers.h"
#include "HResultWrapper.h"

D3DHelpers::D3DHelpers(ID3D11Device* Device) :
    Device(Device)
{
}	

ID3D11Texture2DPtr D3DHelpers::CreateTexture2D(const D3D11_TEXTURE2D_DESC& Desc,
                                        const D3D11_SUBRESOURCE_DATA* InitialData)
{
    HResultWrapper hr;
    ID3D11Texture2DPtr result;

    hr = Device->CreateTexture2D(&Desc, InitialData, &result);

    return result;
}

ID3D11RenderTargetViewPtr D3DHelpers::CreateRenderTargetView(ID3D11Texture2D* Texture,
                                        const D3D11_RENDER_TARGET_VIEW_DESC* Desc)
{
    HResultWrapper hr;
    ID3D11RenderTargetViewPtr result;

    hr = Device->CreateRenderTargetView(Texture, Desc, &result);

    return result;
}

ID3D11DepthStencilViewPtr D3DHelpers::CreateDepthStencilView(ID3D11Texture2D* Texture,
                                        const D3D11_DEPTH_STENCIL_VIEW_DESC& Desc)
{
    HResultWrapper hr;
    ID3D11DepthStencilViewPtr result;

    hr = Device->CreateDepthStencilView(Texture, &Desc, &result);

    return result;
}

ID3D11ShaderResourceViewPtr D3DHelpers::CreateShaderResourceView(ID3D11Resource* Resource,
                                        const D3D11_SHADER_RESOURCE_VIEW_DESC* Desc)
{
    HResultWrapper hr;
    ID3D11ShaderResourceViewPtr result;

    hr = Device->CreateShaderResourceView(Resource, Desc, &result);

    return result;
}

ID3D11VertexShaderPtr D3DHelpers::CreateVertexShader(ID3DBlob* ShaderData)
{
    return CreateVertexShader(ShaderData->GetBufferPointer(), ShaderData->GetBufferSize());
}

ID3D11VertexShaderPtr D3DHelpers::CreateVertexShader(const void* Bytecode, int BytecodeSize)
{
    HResultWrapper hr;
    ID3D11VertexShaderPtr result;

    hr = Device->CreateVertexShader(Bytecode, BytecodeSize, nullptr, &result);

    return result;
}

ID3D11PixelShaderPtr D3DHelpers::CreatePixelShader(ID3DBlob* ShaderData)
{
    return CreatePixelShader(ShaderData->GetBufferPointer(), ShaderData->GetBufferSize());
}

ID3D11PixelShaderPtr D3DHelpers::CreatePixelShader(const void* Bytecode, int BytecodeSize)
{
    HResultWrapper hr;
    ID3D11PixelShaderPtr result;

    hr = Device->CreatePixelShader(Bytecode, BytecodeSize, nullptr, &result);

    return result;
}