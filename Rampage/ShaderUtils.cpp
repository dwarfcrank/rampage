#include "stdafx.h"
#include "ShaderUtils.h"
#include "GraphicsDevice.h"

// TODO: Remove once filesystem abstraction stuff is done, leave for now...
static void LoadFile(const wchar_t* Path, char** Buffer, int* Size)
{
    auto file = CreateFile(Path, GENERIC_READ, FILE_SHARE_READ, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    auto filesize = GetFileSize(file, nullptr);
    *Size = static_cast<int>(filesize);

    auto data = new char[filesize];
    *Buffer = data;

    ReadFile(file, data, filesize, nullptr, nullptr);

    CloseHandle(file);
}

PixelShader* LoadPixelShader(const wchar_t* Path, GraphicsDevice* Device)
{
    std::unique_ptr<char[]> buffer;
    char* buf;
    int size;

    LoadFile(Path, &buf, &size);
    buffer.reset(buf);

    return Device->CreatePixelShader(buffer.get(), size);
}

VertexShader* LoadVertexShader(const wchar_t* Path, GraphicsDevice* Device)
{
    std::unique_ptr<char[]> buffer;
    char* buf;
    int size;

    LoadFile(Path, &buf, &size);
    buffer.reset(buf);

    return Device->CreateVertexShader(buffer.get(), size);
}

