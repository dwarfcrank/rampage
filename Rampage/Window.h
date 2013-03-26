#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class Window
{
public:
    typedef LRESULT (CALLBACK *WindowProcedure)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
        void* Context);

    ~Window();

    void SetSize(int Width, int Height);
    void GetSize(int* Width, int* Height) const;

    void SetTitle(const wchar_t* Title);

    void SetContextPointer(void* Context);

    void SetWindowProcedure(WindowProcedure WndProc);

    HWND GetHandle();

    static std::unique_ptr<Window> Create(int Width, int Height, const wchar_t* Title, 
        WindowProcedure WindowProc, void* Context = nullptr);

private:
    static void SetupWindowClass();
    static bool ms_IsWindowClassSetUp;
    static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    WindowProcedure m_WindowProcedure;
    void* m_WindowProcedureContext;

    Window();

    HWND m_WindowHandle;

    int m_Width;
    int m_Height;
};

