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

// -----------------------------------------------------

namespace xMath
{
	/* @brief 2D vector type with single-precision floating-point components (x, y). */
	typedef TVector2<float> Vec2;

	/* @brief 3D vector type with single-precision floating-point components (x, y, z). */
	typedef TVector3<float> Vec3;

	/* @brief 4D vector type with single-precision floating-point components (x, y, z, w). */
	typedef TVector4<float> Vec4;

}

// -----------------------------------------------------
