#include "stdafx.h"
#include "Window.h"

#include <memory>

bool Window::ms_IsWindowClassSetUp = false;

static wchar_t* WindowClassName = L"RampageWindow";

void Window::SetupWindowClass()
{
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(wcex));
    
    wcex.cbSize = sizeof(wcex);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = StaticWindowProc;
    wcex.cbWndExtra = sizeof(Window*); // Reserve extra space for a pointer to the actual Window object
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.lpszClassName = WindowClassName;

    _ASSERT(RegisterClassEx(&wcex));
}

Window* Window::Create(int Width, int Height, const wchar_t* Title, WindowProcedure WindowProc, 
                       void* Context)
{
    std::unique_ptr<Window> window(new Window());

    window->m_WindowProcedureContext = Context;
    window->m_WindowProcedure = WindowProc;

    if(!ms_IsWindowClassSetUp)
    {
        SetupWindowClass();
        ms_IsWindowClassSetUp = true;
    }

    auto windowhandle = CreateWindow(WindowClassName, Title,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, GetModuleHandle(nullptr), window.get());

    _ASSERT(windowhandle);
    if(!windowhandle)
    {
        return nullptr;
    }

    window->m_WindowHandle = windowhandle;
    window->SetSize(Width, Height);

    ShowWindow(windowhandle, SW_SHOW);
    UpdateWindow(windowhandle);

    return window.release();
}

void Window::SetWindowProcedure(WindowProcedure WndProc)
{
    m_WindowProcedure = WndProc;
}

Window::Window(void)
{
}

Window::~Window(void)
{
}

/// <summary>	Calculates the size of the window, including the non-client area </summary>
///
/// <param name="Width"> 	[in,out] Width of the window. </param>
/// <param name="Height">	[in,out] Height of the window. </param>
static void CalculateSize(int* Width, int* Height)
{
    RECT rc = { 0, 0, *Width, *Height };

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

    *Width = rc.right - rc.left;
    *Height = rc.bottom - rc.top;
}

void Window::SetSize(int Width, int Height)
{
    m_Width = Width;
    m_Height = Height;

    CalculateSize(&Width, &Height);

    SetWindowPos(m_WindowHandle, nullptr, 0, 0, m_Width, m_Height, SWP_NOMOVE | SWP_NOZORDER);
}

void Window::GetSize(int* Width, int* Height) const
{
    *Width = m_Width;
    *Height = m_Height;
}

void Window::SetTitle(const wchar_t* Title)
{
    SetWindowText(m_WindowHandle, Title);
}

LRESULT CALLBACK Window::StaticWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Window* window;

    // Window is created, set up the pointers
    if(uMsg == WM_NCCREATE)
    {
        // Get the window object pointer
        auto createParams = reinterpret_cast<CREATESTRUCT*>(lParam);
        
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createParams->lpCreateParams));

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if(!window)
    {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return window->m_WindowProcedure(hWnd, uMsg, wParam, lParam, window->m_WindowProcedureContext);
}

HWND Window::GetHandle()
{
    return m_WindowHandle;
}