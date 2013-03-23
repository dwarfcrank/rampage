#include "stdafx.h"
#include "VertexShader.h"


VertexShader::VertexShader(ID3D11VertexShaderPtr Shader) :
    m_Shader(Shader)
{
}

VertexShader::~VertexShader(void)
{
}

ID3D11VertexShader* VertexShader::GetShader()
{
    return m_Shader;
}
