#pragma once
#include "stdafx.h"
#include "ComPtrDef.h"
#include <d3d11.h>

class IndexBuffer
{
public:
    IndexBuffer(ID3D11BufferPtr Buffer, int Size);
    ~IndexBuffer(void);

    ID3D11Buffer* GetBuffer();
    
    // Size is in elements, byte size is buffer size * sizeof(uint)
    int GetBufferSize();

private:
    ID3D11BufferPtr m_Buffer;

    int m_BufferSize;
};