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
// ReSharper disable IdentifierTypo
#pragma once
#include <xMath/config/math_config.h>
#include <xMath/includes/platform.h>

///////////////////////////////////////////////////////////
///				ACTIVE STATE DEFINITION 				///
///////////////////////////////////////////////////////////

#define XMATH_DISABLED 0
#define XMATH_ENABLED  1

#ifndef SEDX_MATH_HAS_VECTOR_ALIASES
#define SEDX_MATH_HAS_VECTOR_ALIASES 1
#endif

#ifdef XMATH_USE_XYZW
#define XMATH_XYZW_CONFIG 1
#else
#define XMATH_XYZW_CONFIG 0
#endif

// Coordinate system configuration
// Users may define exactly one of the following macros before including xmath.hpp:
//   XMATH_COORD_LEFT_HAND_CONFIG
//   XMATH_COORD_RIGHT_HAND_CONFIG
// If none are defined, default to right-handed coordinates.
#if defined(XMATH_COORD_LEFT_HAND_CONFIG) && defined(XMATH_COORD_RIGHT_HAND_CONFIG)
#error "Both XMATH_COORD_LEFT_HAND_CONFIG and XMATH_COORD_RIGHT_HAND_CONFIG are defined. Define only one."
#endif

#if !defined(XMATH_COORD_LEFT_HAND_CONFIG) && !defined(XMATH_COORD_RIGHT_HAND_CONFIG)
#define XMATH_COORD_RIGHT_HAND_CONFIG 1
#endif

// Normalize the defined coordinate macro to value 1 for simple checks
#ifdef XMATH_COORD_LEFT_HAND_CONFIG
#undef XMATH_COORD_LEFT_HAND_CONFIG
#define XMATH_COORD_LEFT_HAND_CONFIG 1
#endif

#ifdef XMATH_COORD_RIGHT_HAND_CONFIG
#undef XMATH_COORD_RIGHT_HAND_CONFIG
#define XMATH_COORD_RIGHT_HAND_CONFIG 1
#endif

// Indicate a coordinate configuration is present
#ifndef XMATH_COORD_DEFINED
#define XMATH_COORD_DEFINED 1
#endif

// Matrix storage order configuration
// Provide numeric constants for conditional compilation. Users may set
// XMATH_MATRIX_ORDER to either MATRIX_ROW_MAJOR or MATRIX_COLUMN_MAJOR before
// including this header. Default is row-major.
#ifndef MATRIX_ROW_MAJOR
#define MATRIX_ROW_MAJOR 0
#endif

#ifndef MATRIX_COLUMN_MAJOR
#define MATRIX_COLUMN_MAJOR 1
#endif

#ifndef XMATH_MATRIX_ORDER
#define XMATH_MATRIX_ORDER MATRIX_ROW_MAJOR
#endif

#if XMATH_MATRIX_ORDER == MATRIX_ROW_MAJOR
#define XMATH_MATRIX_IS_ROW_MAJOR 1
#define XMATH_MATRIX_IS_COLUMN_MAJOR 0
#else
#define XMATH_MATRIX_IS_ROW_MAJOR 0
#define XMATH_MATRIX_IS_COLUMN_MAJOR 1
#endif

///////////////////////////////////////////////////////////
///					INCLUDE UMBRELLA 					///
///////////////////////////////////////////////////////////

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
	using ::xMath::Epsilon;      // templates
	using ::xMath::EpsilonEqual; // templates
}
