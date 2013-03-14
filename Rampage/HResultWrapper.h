#pragma once

#include <windows.h>
#include <crtdbg.h>

// A basic wrapper class for validating HRESULTs.
// It simply has an op= which asserts on invalid HRESULTs.
struct HResultWrapper
{
	HResultWrapper& operator=(HRESULT HResult)
	{
		_ASSERTE(SUCCEEDED(HResult));

		return *this;
	}
};