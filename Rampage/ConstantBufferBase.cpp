#include "stdafx.h"
#include "ConstantBufferBase.h"


ConstantBufferBase::ConstantBufferBase(ID3D11Buffer* Buffer, int Size) :
    m_Buffer(Buffer), m_Size(Size), m_SourceData(nullptr)
{
}

ConstantBufferBase::~ConstantBufferBase(void)
{
}

void ConstantBufferBase::SetUpdateSource(const void* SourceData)
{
    m_SourceData = SourceData;
}

void ConstantBufferBase::Update(ID3D11DeviceContext* DeviceContext)
{
    _ASSERTE(m_SourceData);

    D3D11_MAPPED_SUBRESOURCE mappedResource;

    DeviceContext->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    memcpy(mappedResource.pData, m_SourceData, m_Size);
    DeviceContext->Unmap(m_Buffer, 0);
}

ID3D11Buffer* ConstantBufferBase::GetBuffer()
{
    return m_Buffer;
}

int ConstantBufferBase::GetSize()
{
    return m_Size;
}