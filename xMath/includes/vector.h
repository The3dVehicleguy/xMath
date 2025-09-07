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
* vector.h
* -------------------------------------------------------
* Created: 15/7/2025
* -------------------------------------------------------
*/
#pragma once
#include <xMath/config/math_config.h>
#include <xMath/includes/vec2.h>
#include <xMath/includes/vec3.h>
#include <xMath/includes/vec4.h>

/// -----------------------------------------------------

namespace xMath
{
	using Vec2 = TVector2<float>;
	using Vec3 = TVector3<float>;
	using Vec4 = TVector4<float>;

	#ifndef SEDX_MATH_HAS_VECTOR_ALIASES
	#define SEDX_MATH_HAS_VECTOR_ALIASES 1
	#endif
}

/// -----------------------------------------------------
