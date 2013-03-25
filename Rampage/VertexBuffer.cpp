#include "stdafx.h"
#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(ID3D11BufferPtr Buffer, int Size, int Stride) :
    m_Buffer(Buffer),
    m_BufferSize(Size),
    m_Stride(Stride)
{
}

VertexBuffer::~VertexBuffer(void)
{
}

ID3D11Buffer* VertexBuffer::GetBuffer()
{
    return m_Buffer;
}

int VertexBuffer::GetBufferSize()
{
    return m_BufferSize;
}

int VertexBuffer::GetStride()
{
    return m_Stride;
}
