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
* scale.cpp
* -------------------------------------------------------
* Created: 6/9/2025
* -------------------------------------------------------
*/
#include <xMath/includes/epsilon.h>
#include <xMath/includes/scale.h>

/// -----------------------------------------------------

namespace xMath
{

	Mat4 Scale(const Vec3 &s)
	{
	    return Mat4({
	        {s.x, 0.0f, 0.0f, 0.0f}, /// Scale X
	        {0.0f, s.y, 0.0f, 0.0f}, /// Scale Y
	        {0.0f, 0.0f, s.z, 0.0f}, /// Scale Z
	        {0.0f, 0.0f, 0.0f, 1.0f} /// Homogeneous coordinate (no translation)
	    });
	}

    Vec3 Scale(const Vec3 &vector, float desiredLength)
    {
        /// Compute magnitude without relying on GLM
        const float mag = std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
        if (epsilonEqual(mag, 0.0f, ::xMath::epsilon<float>()))
            return Vec3(0.0f);
	
        return vector * desiredLength / mag;
    }

    Mat4 Scale(const Vec2 &s)
    {
        return Mat4({
            {s.x, 0.0f, 0.0f, 0.0f},  /// Scale X
            {0.0f, s.y, 0.0f, 0.0f},  /// Scale Y
            {0.0f, 0.0f, 1.0f, 0.0f}, /// Scale Z (no scaling)
            {0.0f, 0.0f, 0.0f, 1.0f}  /// Homogeneous coordinate (no translation)
        });
    }

    Mat4 Scale(const Mat4 &m, const Vec3 &s)
    {
        return m * Scale(s);
    }

    Mat4 Scale(const Mat4 &m, const Vec2 &s)
    {
        return m * Scale(s);
    }

    Mat3 Scale2D(const Vec2 &s)
    {
        return {
            s.x, 0.0f, 0.0f, /// Scale X
            0.0f, s.y, 0.0f, /// Scale Y
            0.0f, 0.0f, 1.0f /// Homogeneous coordinate (no translation)
        };
    }

    Mat3 Scale2D(const Mat3 &m, const Vec2 &s)
	{
	    return m * Scale2D(s);
	}


}

/// -----------------------------------------------------
