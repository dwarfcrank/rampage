#include "stdafx.h"
#include "GraphicsDevice.h"

static const D3D11_INPUT_ELEMENT_DESC meshVSInputElements[] =
{
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


struct InputLayoutDesc
{
    const D3D11_INPUT_ELEMENT_DESC* InputElements;
    int InputElementCount;

    // Shader bytecode is for input layout validation
    const BYTE* ShaderBytecode;
    int ShaderBytecodeSize;
};

#include "DummyMeshVS.h"

static const InputLayoutDesc layouts[NUM_INPUT_LAYOUTS] =
{
    // IL_MESH
    { meshVSInputElements, _countof(meshVSInputElements), DummyMeshVS, _countof(DummyMeshVS) },
};

void RenderContext::InitInputLayouts()
{
    ID3D11DevicePtr device;
    m_DeviceContext->GetDevice(&device);
    D3DHelpers helpers(device);

    for(int i = 0; i < NUM_INPUT_LAYOUTS; i++)
    {
        const InputLayoutDesc& layoutDesc = layouts[i];
        ArrayRef<D3D11_INPUT_ELEMENT_DESC> inputElements(layoutDesc.InputElements, layoutDesc.InputElementCount);
        ArrayRef<BYTE> shaderBytecode(layoutDesc.ShaderBytecode, layoutDesc.ShaderBytecodeSize);

        m_InputLayouts[i] = helpers.CreateInputLayout(inputElements, shaderBytecode);
    }
}