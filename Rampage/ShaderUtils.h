#pragma once

#include <memory>
#include "VertexShader.h"
#include "PixelShader.h"

class GraphicsDevice;
class PixelShader;
class VertexShader;

std::unique_ptr<PixelShader> LoadPixelShader(const wchar_t* Path, GraphicsDevice* Device);
std::unique_ptr<VertexShader> LoadVertexShader(const wchar_t* Path, GraphicsDevice* Device);