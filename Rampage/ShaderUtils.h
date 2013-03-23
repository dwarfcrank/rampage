#pragma once

class GraphicsDevice;
class PixelShader;
class VertexShader;

PixelShader* LoadPixelShader(const wchar_t* Path, GraphicsDevice* Device);
VertexShader* LoadVertexShader(const wchar_t* Path, GraphicsDevice* Device);