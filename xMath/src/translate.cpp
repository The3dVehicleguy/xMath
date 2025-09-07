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
* translate.cpp
* -------------------------------------------------------
* Created: 6/9/2025
* -------------------------------------------------------
*/
#include <xMath/includes/translate.h>

/// -------------------------------------------------------

namespace xMath
{

	Mat4 Translate(const Vec3 &t)
	{
	    /// Row-major: translation in last column
	    return Mat4({
	        {1.0f, 0.0f, 0.0f, t.x}, /// Translate X
	        {0.0f, 1.0f, 0.0f, t.y}, /// Translate Y
	        {0.0f, 0.0f, 1.0f, t.z}, /// Translate Z
	        {0.0f, 0.0f, 0.0f, 1.0f} /// Homogeneous coordinate (no translation)
	    });
	}

    Mat4 Translate(const Mat4 &m, const Vec3 &t)
	{
	    return m * Translate(t);
	}

    Mat3 Translate2D(const TVector2<float> &t)
    {
        return {
            1.0f, 0.0f, t.x, /// Translate X
            0.0f, 1.0f, t.y, /// Translate Y
            0.0f, 0.0f, 1.0f /// Homogeneous coordinate (no translation)
        };
    }

    Mat3 Translate2D(const Mat3 &m, const TVector2<float> &t)
    {
        return m * Translate2D(t);
    }


}

/// -------------------------------------------------------
