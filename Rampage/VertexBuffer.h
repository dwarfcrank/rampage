#pragma once

#include "stdafx.h"
#include "ComPtrDef.h"
#include <d3d11.h>

class VertexBuffer
{
public:
    VertexBuffer(ID3D11BufferPtr Buffer, int Size, int Stride);
    ~VertexBuffer(void);

    ID3D11Buffer* GetBuffer();
    
    // Size is in elements - size in bytes is size * stride!
    int GetBufferSize();
    int GetStride();

private:
    ID3D11BufferPtr m_Buffer;

    int m_BufferSize;
    int m_Stride;
};

