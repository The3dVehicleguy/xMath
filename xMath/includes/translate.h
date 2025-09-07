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
* translate.h
* -------------------------------------------------------
* Created: 13/8/2025
* -------------------------------------------------------
*/
#pragma once
#include <mat3.h>
#include <mat4.h>
#include <math_config.h>
#include <xMath/includes/vector.h>

/// -------------------------------------------------------

namespace xMath
{
    ///////////////////////////////////////////////////////////
	//					3D translation (Mat4)				 //
    ///////////////////////////////////////////////////////////

    /**
     * @brief Creates a translation matrix that translates by the given vector.
     *
     * This function generates a 4x4 translation matrix that can be used to translate
     * 3D points in space. The translation is applied in the order of the matrix multiplication,
     * meaning it will translate points by the vector t when multiplied with the matrix.
     *
     * @param t translation matrix vector
     * @return Mat4 A 4x4 translation matrix that translates points by the vector t.
     *
     * @code
     * Mat4 translationMatrix = Translate(Vec3(1.0f, 2.0f, 3.0f));
     * Mat4 combinedMatrix = Translate(translationMatrix, Vec3(4.0f, 5.0f, 6.0f));
     * @endcode
     */
    XMATH_API Mat4 Translate(const Vec3 &t);

    /**
     * @brief Creates a translation matrix that translates by the given vector.
     *
     * This function generates a 4x4 translation matrix that can be used to translate
     * 3D points in space. The translation is applied in the order of the matrix multiplication,
     * meaning it will translate points by the vector t when multiplied with the matrix.
     *
     * @param m
     * @param t transform matrix vector
     * @return
     *
     * @code
     * Mat4 translationMatrix = Translate(Vec3(1.0f, 2.0f, 3.0f));
     * Mat4 combinedMatrix = Translate(translationMatrix, Vec3(4.0f, 5.0f, 6.0f));
     * @endcode
     */
    XMATH_API Mat4 Translate(const Mat4 &m, const Vec3 &t);

    ///////////////////////////////////////////////////////////
	//			2D translation (homogeneous Mat3)			 //
    ///////////////////////////////////////////////////////////

    /**
     * @brief Creates a translation matrix that translates by the given 2D vector.
     *
     * This function generates a 3x3 translation matrix that can be used to translate
     * 2D points in space. The translation is applied in the order of the matrix multiplication,
     * meaning it will translate points by the vector t when multiplied with the matrix.
     *
     * @param t translation matrix vector
     * @return Mat3 A 3x3 translation matrix that translates points by the vector t.
     *
     * @code
     * Mat3 translationMatrix = Translate2D(TVector2<float>(1.0f, 2.0f));
     * Mat3 combinedMatrix = Translate2D(translationMatrix, TVector2<float>(3.0f, 4.0f));
     * @endcode
     */
    XMATH_API Mat3 Translate2D(const TVector2<float> &t);

    /**
     * @brief Creates a translation matrix that translates by the given 2D vector.
     *
     * This function generates a 3x3 translation matrix that can be used to translate
     * 2D points in space. The translation is applied in the order of the matrix multiplication,
     * meaning it will translate points by the vector t when multiplied with the matrix.
     *
     * @param m matrix to translate
     * @param t transform matrix vector
     * @return Mat3 A 3x3 translation matrix that translates points by the vector t.
     *
     * @code
     * Mat3 translationMatrix = Translate2D(TVector2<float>(1.0f, 2.0f));
     * Mat3 combinedMatrix = Translate2D(translationMatrix, TVector2<float>(3.0f, 4.0f));
     * @endcode
     */
    XMATH_API Mat3 Translate2D(const Mat3 &m, const TVector2<float> &t);

}

/// -------------------------------------------------------
