#pragma once

#include <memory>
#include <d3d11.h>

#include "ComPtrDef.h"

class ConstantBufferBase
{
public:
    ConstantBufferBase(ID3D11Buffer* Buffer, int Size);
    ~ConstantBufferBase(void);

    int GetSize();
    ID3D11Buffer* GetBuffer();

    // Sets the pointer from which to copy data for updating the buffer.
    // It should be 16-byte aligned.
    void SetUpdateSource(const void* SourceData);

    void Update(ID3D11DeviceContext* DeviceContext);

private:
    int m_Size;
    const void* m_SourceData;
    ID3D11BufferPtr m_Buffer;
};

