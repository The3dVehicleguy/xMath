/**
* -------------------------------------------------------
* Copyright (c) 2025 Thomas Ray
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
* copies of the Software, and to permit persons to whom the Software is furnished
* to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
* -------------------------------------------------------
* math_config.h
* -------------------------------------------------------
* Created: 16/8/2025
* -------------------------------------------------------
*/
#pragma once

// -----------------------------------------------------------------------------
// xMath DLL export/import configuration
// -----------------------------------------------------------------------------
// Expected usage:
//   When building the xMath DLL target, CMake defines XMATH_API which causes
//   symbols marked with XMATH_API to be exported.  Downstream consumers that
//   include these headers (without defining XMATH_API) will import the
//   symbols.  On non-Windows platforms the macro collapses to empty so it is
//   harmless.
// -----------------------------------------------------------------------------

// Export macro pattern: when building the DLL define XMATH_BUILD in CMake.
// Consumers do NOT define XMATH_BUILD and thus import the symbols.
#if defined(_WIN32) || defined(_WINDOWS)
    #if defined(XMATH_BUILD)
        #define XMATH_API __declspec(dllexport)
    #else
        #define XMATH_API __declspec(dllimport)
    #endif
#else
    #define XMATH_API
#endif

// -----------------------------------------------------------------------------
