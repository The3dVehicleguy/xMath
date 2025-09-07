﻿/**
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
* constants.h
* -------------------------------------------------------
* Created: 12/8/2025
* -------------------------------------------------------
*/
#pragma once
#include <xMath/config/math_config.h>

/// -------------------------------------------------------

namespace xMath
{
	///////////////////////////////////////////////////////////
	///					Mathematical Constants				///
	///////////////////////////////////////////////////////////

    constexpr float PI = 3.14159265358979323846f;			/// Pi constant (π)
    constexpr float TWO_PI = 2.0f * PI;						/// Two times pi (2π)
    constexpr float HALF_PI = PI * 0.5f;					/// Half pi (π/2)
    constexpr float DEG_TO_RAD = PI / 180.0f;				/// Degrees to radians conversion factor
    constexpr float RAD_TO_DEG = 180.0f / PI;				/// Radians to degrees conversion factor
    constexpr float E = 2.71828182845904523536f;			/// Euler's number (e)
    constexpr float SQRT2 = 1.41421356237309504880f;		/// Square root of 2
    constexpr float SQRT3 = 1.73205080756887729352f;		/// Square root of 3
    constexpr float INV_PI = 1.0f / PI;						/// 1 / π
    constexpr float INV_TWO_PI = 1.0f / TWO_PI;				/// 1 / (2π)
    constexpr float PI_OVER_4 = PI * 0.25f;					/// π/4
    constexpr float PI_OVER_6 = PI / 6.0f;					/// π/6
    constexpr float LN2 = 0.69314718055994530942f;			/// Natural log of 2
    constexpr float LN10 = 2.30258509299404568402f;			/// Natural log of 10
    constexpr float EPSILON_F = 1.1920928955078125e-07f;	/// Float epsilon (FLT_EPSILON)
    constexpr float HUGE_F = 3.402823466e+38f;				/// Max float (approx)
    constexpr float TINY_F = 1.175494351e-38f;				/// Min positive normal float (approx)

}

/// -------------------------------------------------------

