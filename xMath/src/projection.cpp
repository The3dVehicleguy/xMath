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
* projection.cpp
* -------------------------------------------------------
* Created: 6/9/2025
* -------------------------------------------------------
*/
#include <xMath/includes/mat4.h>
#include <xMath/includes/math_utils.h>
#include <xMath/includes/projection.h>

/// -------------------------------------------------------

namespace xMath
{

	Mat4 PerspectiveFov(float fovyRadians, float width, float height, float zNear, float zFar)
	{
	    const float aspect = (height != 0.0f) ? (width / height) : 1.0f;	/// Calculate aspect ratio, defaulting to 1.0 if height is zero
	    const float f = 1.0f / std::tan(fovyRadians * 0.5f);				/// Calculate the cotangent of half the field of view
	    const float A = f / aspect;											/// Scale X based on aspect ratio
	    const float B = f;													/// Scale Y
	    const float C = (zFar + zNear) / (zNear - zFar);					/// Scale Z
	    const float D = (2.0f * zFar * zNear) / (zNear - zFar);				/// Translate factor
	
	    return Mat4({
	        { A,    0.0f, 0.0f, 0.0f }, /// Scale X
	        { 0.0f, B,    0.0f, 0.0f }, /// Scale Y
	        { 0.0f, 0.0f, C,    D    }, /// Scale Z and translation
	        {0.0f, 0.0f, -1.0f, 0.0f}   /// Homogeneous coordinate (no translation)
	    });
	}

    Mat4 Perspective(float fovyRadians, float aspect, float zNear, float zFar)
    {
        const float f = 1.0f / std::tan(fovyRadians * 0.5f); /// Calculate the cotangent of half the field of view
        const float A = f / ((aspect == 0.0f) ? 1.0f : aspect); /// Scale X based on aspect ratio, defaulting to 1.0 if aspect is zero
        const float B = f;                                      /// Scale Y
        const float C = (zFar + zNear) / (zNear - zFar);        /// Scale Z
        const float D = (2.0f * zFar * zNear) / (zNear - zFar); /// Translate factor

        return Mat4({
            { A,    0.0f, 0.0f, 0.0f }, /// Scale X
            { 0.0f, B,    0.0f, 0.0f }, /// Scale Y
            { 0.0f, 0.0f, C,    D    }, /// Scale Z and translation
            { 0.0f, 0.0f, -1.0f,0.0f }  /// Homogeneous coordinate (no translation)
        });
    }

    Mat4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        const float rl = (right - left); /// Right - Left
        const float tb = (top - bottom); /// Top - Bottom
        const float fn = (zFar - zNear); /// Far - Near

        const float sx = rl != 0.0f ? 2.0f / rl : 0.0f;  /// Scale X
        const float sy = tb != 0.0f ? 2.0f / tb : 0.0f;  /// Scale Y
        const float sz = fn != 0.0f ? -2.0f / fn : 0.0f; /// Scale Z (inverted for right-handed coordinate system)

        const float tx = -(right + left) / (rl == 0.0f ? 1.0f : rl); /// Translate X
        const float ty = -(top + bottom) / (tb == 0.0f ? 1.0f : tb); /// Translate Y
        const float tz = -(zFar + zNear) / (fn == 0.0f ? 1.0f : fn); /// Translate Z (inverted for right-handed coordinate system)

        return Mat4({
            { sx,   0.0f, 0.0f, tx },  /// Scale X and translation
            { 0.0f, sy,   0.0f, ty },  /// Scale Y and translation
            { 0.0f, 0.0f, sz,   tz },  /// Scale Z and translation
            { 0.0f, 0.0f, 0.0f, 1.0f } /// Homogeneous coordinate (no translation)
        });
    }

    Mat4 LookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up)
    {
        const Vec3 f = Normalize({ center.x - eye.x, center.y - eye.y, center.z - eye.z });
        /// side = normalize(cross(f, up))
        const Vec3 side = Normalize(Cross(f, up));
        const Vec3 up2 = Cross(side, f);

        /// Row-major with column-vector multiply; translation in last column
        return Mat4({
            { side.x,  side.y,  side.z,  - (side.x * eye.x + side.y * eye.y + side.z * eye.z) }, /// Right vector
            { up2.x,   up2.y,   up2.z,   - (up2.x * eye.x  + up2.y * eye.y  + up2.z * eye.z)  }, /// Up vector
            { -f.x,    -f.y,    -f.z,      (f.x * eye.x    + f.y * eye.y    + f.z * eye.z)    }, /// Forward vector (negative for right-handed)
            { 0.0f,    0.0f,    0.0f,    1.0f }
        });
    }


}

/// -------------------------------------------------------
