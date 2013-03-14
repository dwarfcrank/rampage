// Rampage.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Window.h"

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
	Window* w = Window::Create(1280, 720, L"Asdf", WindowProc);

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
			
		}
	}

	return 0;
}
