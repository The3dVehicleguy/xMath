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
* Umbrella math header (renamed from math.h to xmath.hpp to avoid collision with <math.h>)
* -------------------------------------------------------
* Provides consolidated inclusion of all public math types and utilities.
* -------------------------------------------------------
*/
#pragma once
#include <math_config.h>
// Provide engine alias types (Vec2/Vec3/etc.) expected by legacy tests.

// Public module includes
// Order matters: vector types must be available before dot/epsilon overloads.
#include <xMath/includes/bounding_box.h>
#include <xMath/includes/constants.h>
#include <xMath/includes/vector.h>
// ReSharper disable once CppWrongIncludesOrder
#include <xMath/includes/epsilon.h>
//#include <xMath/includes/dot.h> // Dot was removed and placed into math_util.h
#include <xMath/includes/frustum.h>
#include <xMath/includes/mat2.h>
#include <xMath/includes/mat3.h>
#include <xMath/includes/mat4.h>
#include <xMath/includes/math_utils.h>
#include <xMath/includes/matrix.h>
#include <xMath/includes/plane.h>
#include <xMath/includes/projection.h>
#include <xMath/includes/quat.h>
#include <xMath/includes/rectangle.h>
#include <xMath/includes/rotation.h>
#include <xMath/includes/scale.h>
#include <xMath/includes/sphere.h>
#include <xMath/includes/transforms.h>
#include <xMath/includes/translate.h>

// Legacy forwarding namespace (kept for backward compatibility with previous API usage)
namespace xMath::Utils
{
	using ::xMath::Normalize;
	//using ::xMath::Dot; // Dot was removed and placed into math_util.h
	using ::xMath::Cross;
	using ::xMath::ToRadians;
	using ::xMath::ToDegrees;
	using ::xMath::epsilon;      // templates
	using ::xMath::epsilonEqual; // templates
}
