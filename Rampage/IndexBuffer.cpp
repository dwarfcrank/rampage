#include "stdafx.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(ID3D11BufferPtr Buffer, int Size) :
    m_Buffer(Buffer), m_BufferSize(Size)
{

}

IndexBuffer::~IndexBuffer(void)
{
}

ID3D11Buffer* IndexBuffer::GetBuffer()
{
    return m_Buffer;
}

int IndexBuffer::GetBufferSize()
{
    return m_BufferSize;
}
