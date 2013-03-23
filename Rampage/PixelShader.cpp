#include "stdafx.h"
#include "PixelShader.h"


PixelShader::PixelShader(ID3D11PixelShaderPtr Shader) :
    m_Shader(Shader)
{
}

PixelShader::~PixelShader(void)
{
}

ID3D11PixelShader* PixelShader::GetShader()
{
    return m_Shader;
}
