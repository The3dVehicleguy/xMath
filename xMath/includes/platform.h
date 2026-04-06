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
* platform.h - Platform-specific definitions
* -------------------------------------------------------
* Created: 04/05/2026
* -------------------------------------------------------
*/
// ReSharper disable IdentifierTypo
#pragma once

#define XMATH_PLATFORM_UNKNOWN		0x00000000
#define XMATH_PLATFORM_WINDOWS		0x00010000
#define XMATH_PLATFORM_LINUX		0x00020000
#define XMATH_PLATFORM_APPLE		0x00040000
#define XMATH_PLATFORM_UNIX			0x00400000

#ifdef XMATH_FORCE_PLATFORM_UNKNOWN
#define XMATH_PLATFORM XMATH_PLATFORM_UNKNOWN
#elif defined(__APPLE__)
#define XMATH_PLATFORM XMATH_PLATFORM_APPLE
#elif defined(WINCE)
#define XMATH_PLATFORM XMATH_PLATFORM_WINCE
#elif defined(_WIN32)
#define XMATH_PLATFORM XMATH_PLATFORM_WINDOWS
#elif defined(__native_client__)
#define XMATH_PLATFORM XMATH_PLATFORM_CHROME_NACL
#elif defined(__ANDROID__)
#define XMATH_PLATFORM XMATH_PLATFORM_ANDROID
#elif defined(__linux)
#define XMATH_PLATFORM XMATH_PLATFORM_LINUX
#elif defined(__unix)
#define XMATH_PLATFORM XMATH_PLATFORM_UNIX
#else
#define XMATH_PLATFORM_UNKNOWN XMATH_PLATFORM_UNKNOWN
#endif

#define XMATH_PLATFORM_32BIT				0x00000010
#define XMATH_PLATFORM_64BIT				0x00000020
