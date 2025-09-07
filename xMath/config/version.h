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
* version.h
* -------------------------------------------------------
* Created: 7/9/2025
* -------------------------------------------------------
*/
#ifndef XMATH_VERSION_H
#define XMATH_VERSION_H

/// -------------------------------------------------------

#define XMATH_VERSION_MAJOR 0
#define XMATH_VERSION_MINOR 1
#define XMATH_VERSION_PATCH 3
#define XMATH_VERSION_REVISION 12
#define XMATH_VERSION 861
#define XMATH_VERSION_MESSAGE "xMath: version 0.1.3.12"

#define XMATH_SETUP_INCLUDED XMATH_VERSION

/// -------------------------------------------------------

#define XMATH_DISABLE 0
#define XMATH_ENABLE 1

/// -------------------------------------------------------

#define XMATH_CXX14_FLAG (1 << 1)
#define XMATH_CXX17_FLAG (1 << 2)
#define XMATH_CXX2A_FLAG (1 << 3)
#define XMATH_CXXMS_FLAG (1 << 4)
#define XMATH_CXXGNU_FLAG (1 << 5)

#define XMATH_CXX17 (XMATH_CXX17_FLAG)
#define XMATH_CXX2A (XMATH_CXX17 | XMATH_CXX2A_FLAG)
#define XMATH_CXXMS XMATH_CXXMS_FLAG
#define XMATH_CXXGNU XMATH_CXXGNU_FLAG

/// -------------------------------------------------------

#if (defined(MVSC_EXTENSIONS))
    #define XMATH_EXT XMATH_CXXMS_FLAG
#elif ((XMATH_COMPILER & (XMATH_COMPILER_CLANG | XMATH_COMPILER_GCC)) && (XMATH_ARCH & XMATH_ARCH_SIMD_BIT))
    #define XMATH_EXT XMATH_CXXMS_FLAG
#else
    #define XMATH_EXT 0
#endif

/// -------------------------------------------------------

#if (defined(XMATH_FORCE_CXX_UNKNOWN))
    #define XMATH_LANG 0
#elif defined(XMATH_FORCE_CXX17)
    #define XMATH_LANG (XMATH_LANG_CXX17 | XMATH_LANG_EXT)
    #define XMATH_LANG_STL11_FORCED
#else
	#if XMATH_COMPILER & XMATH_COMPILER_VC && defined(_MSVC_LANG)
		#if XMATH_COMPILER >= XMATH_COMPILER_VC15_7
		    #define XMATH_LANG_PLATFORM _MSVC_LANG
		#elif XMATH_COMPILER >= XMATH_COMPILER_VC15
			#if _MSVC_LANG > 201402L
			    #define XMATH_LANG_PLATFORM 201402L
			#else
			    #define XMATH_LANG_PLATFORM _MSVC_LANG
			#endif
		#else
		    #define XMATH_LANG_PLATFORM 0
		#endif
	#else
	    #define XMATH_LANG_PLATFORM 0
	#endif
	
	#if __cplusplus > 201703L || XMATH_LANG_PLATFORM > 201703L
	    #define XMATH_LANG (XMATH_LANG_CXX2A | XMATH_LANG_EXT)
	    #elif __cplusplus == 201703L || XMATH_LANG_PLATFORM == 201703L
	        #define XMATH_LANG (XMATH_LANG_CXX17 | XMATH_LANG_EXT)
	    #endif
#endif

#endif // XMATH_VERSION_H

/// -------------------------------------------------------
