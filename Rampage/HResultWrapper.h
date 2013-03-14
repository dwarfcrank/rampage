#pragma once

#include <windows.h>
#include <crtdbg.h>

// A basic wrapper class for validating HRESULTs.
// It simply has an op= which asserts on invalid HRESULTs.
struct HResultWrapper
{
    HResultWrapper& operator=(HRESULT HResult)
    {
        if(FAILED(HResult))
        {
            // Not the most optimal solution, but you still see the failing line
            // from the call stack :) TODO: make better
            _CrtDbgBreak();
        }

        return *this;
    }
};