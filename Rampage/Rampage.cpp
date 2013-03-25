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
    std::unique_ptr<PixelShader> ps(LoadPixelShader(L"TestPS.cso", gfxDevice.get()));
    std::unique_ptr<VertexShader> vs(LoadVertexShader(L"DummyMeshVS.cso", gfxDevice.get()));
    auto renderContext = gfxDevice->GetRenderContext();

    float vertices[] =
    {
        // Upper left corner
        -1.0f, 1.0f, 0.5f, //1.0f,
        // Lower right corner
        1.0f, -1.0f, 0.5f, //1.0f,
        // Lower left corner
        -1.0f, -1.0f, 0.5f, //1.0f,
    };

    auto buffer = gfxDevice->CreateVertexBuffer(3, 12, vertices);
    renderContext->SetPixelShader(ps.get());
    renderContext->SetVertexShader(vs.get());
    renderContext->BindVertexBuffers(1, &buffer);

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
            renderContext->BindBackbufferRenderTarget();
            renderContext->Draw(3);
            renderContext->EndFrame();
        }
    }

    return 0;
}
