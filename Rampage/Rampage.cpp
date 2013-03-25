// Rampage.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <memory>

#include "Window.h"
#include "GraphicsDevice.h"
#include "RenderContext.h"
#include "ShaderUtils.h"

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                                   void* Context)
{
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                       _In_opt_ HINSTANCE hPrevInstance,
                       _In_ LPTSTR    lpCmdLine,
                       _In_ int       nCmdShow)
{
    std::unique_ptr<Window> window(Window::Create(1280, 720, L"Rampage", WindowProc));
    std::unique_ptr<GraphicsDevice> gfxDevice(GraphicsDevice::Create(window.get()));
    
    auto renderContext = gfxDevice->GetRenderContext();

    float vertices[] =
    {
        // Upper left corner
        -1.0f, 1.0f, 0.5f, 1.0f,
        // Lower right corner
        1.0f, -1.0f, 0.5f, 1.0f,
        // Lower left corner
        -1.0f, -1.0f, 0.5f, 1.0f,
    };

    auto buffer = gfxDevice->CreateVertexBuffer(3, 12, vertices);

    MSG msg;
    while(true)
    {
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            renderContext->BeginFrame();
            renderContext->EndFrame();
        }
    }

    return 0;
}
