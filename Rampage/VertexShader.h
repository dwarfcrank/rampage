#pragma once

#include "stdafx.h"
#include "ComPtrDef.h"
#include <d3d11.h>

class VertexShader
{
public:
    VertexShader(ID3D11VertexShaderPtr Shader);
    ~VertexShader(void);

    ID3D11VertexShader* GetShader();

private:
    ID3D11VertexShaderPtr m_Shader;
};

