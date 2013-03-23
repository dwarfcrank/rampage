#include "stdafx.h"
#include "ShaderUtils.h"
#include "GraphicsDevice.h"

// TODO: Remove once filesystem abstraction stuff is done, leave for now...
static void LoadFile(const wchar_t* Path, char** Buffer, int* Size)
{
    auto file = CreateFile(Path, GENERIC_READ, FILE_SHARE_READ, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if(file == INVALID_HANDLE_VALUE)
    {
        *Buffer = nullptr;
        *Size = -1;

        return;
    }

    auto filesize = GetFileSize(file, nullptr);
    *Size = static_cast<int>(filesize);

    auto data = new char[filesize];
    *Buffer = data;

    DWORD bytesRead;
    ReadFile(file, data, filesize, &bytesRead, nullptr);

    if(bytesRead != filesize)
    {
        delete[] data;
        
        *Buffer = nullptr;
        *Size = -1;

        return;
    }

    CloseHandle(file);
}

PixelShader* LoadPixelShader(const wchar_t* Path, GraphicsDevice* Device)
{
    std::unique_ptr<char[]> buffer;
    char* buf;
    int size;

    LoadFile(Path, &buf, &size);

    if(!buf)
    {
        return nullptr;
    }

    buffer.reset(buf);

    return Device->CreatePixelShader(buffer.get(), size);
}

VertexShader* LoadVertexShader(const wchar_t* Path, GraphicsDevice* Device)
{
    std::unique_ptr<char[]> buffer;
    char* buf;
    int size;

    LoadFile(Path, &buf, &size);

    if(!buf)
    {
        return nullptr;
    }

    buffer.reset(buf);

    return Device->CreateVertexShader(buffer.get(), size);
}

