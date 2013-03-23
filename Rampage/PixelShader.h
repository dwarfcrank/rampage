#pragma once

#include "stdafx.h"
#include "ComPtrDef.h"
#include <d3d11.h>

class PixelShader
{
public:
    PixelShader(ID3D11PixelShaderPtr Shader);
    ~PixelShader(void);

    ID3D11PixelShader* GetShader();

private:
    ID3D11PixelShaderPtr m_Shader;
};

