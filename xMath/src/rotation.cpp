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
* rotation.cpp
* -------------------------------------------------------
* Created: 6/9/2025
* -------------------------------------------------------
*/
#include <xMath/includes/constants.h>
#include <xMath/includes/mat3.h>
#include <xMath/includes/mat4.h>
#include <xMath/includes/math_utils.h>
#include <xMath/includes/rotation.h>

/// -------------------------------------------------------

namespace xMath
{

	Mat4 RotateZDegrees(float degrees)
	{
	    const float r = degrees * DEG_TO_RAD;
	    const float c = std::cos(r);
	    const float s = std::sin(r);
	    return Mat4({
	        { c, -s, 0.0f, 0.0f },
	        { s,  c, 0.0f, 0.0f },
	        {0.0f, 0.0f, 1.0f, 0.0f},
	        {0.0f, 0.0f, 0.0f, 1.0f}
	    });
	}

    Mat4 RotateZDegrees(const Mat4 &m, float degrees)
	{
	    return m * RotateZDegrees(degrees);
	}

    Mat4 RotateEulerRadians(const Vec3 &euler)
    {
        const float cx = std::cos(euler.x), sx = std::sin(euler.x);
        const float cy = std::cos(euler.y), sy = std::sin(euler.y);
        const float cz = std::cos(euler.z), sz = std::sin(euler.z);

        /// Y * X * Z order (YXZ)
        const Mat4 Ry({ { cy, 0.0f, sy, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { -sy, 0.0f, cy, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f } });
        const Mat4 Rx({ { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, cx, -sx, 0.0f }, { 0.0f, sx, cx, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f } });
        const Mat4 Rz({ { cz, -sz, 0.0f, 0.0f }, { sz, cz, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f } });
        return Ry * Rx * Rz;
    }

    Mat4 RotateEulerDegrees(const Vec3 &eulerDeg)
    {
        return RotateEulerRadians({ eulerDeg.x * DEG_TO_RAD, eulerDeg.y * DEG_TO_RAD, eulerDeg.z * DEG_TO_RAD });
    }

    Mat4 RotateEulerRadians(const Mat4 &m, const Vec3 &euler)
    {
        return m * RotateEulerRadians(euler);
    }

    Mat4 RotateEulerDegrees(const Mat4 &m, const Vec3 &eulerDeg)
    {
        return m * RotateEulerDegrees(eulerDeg);
    }

    Mat4 RotateAxisAngleRadians(const Vec3 &axis, float angle)
    {
        /// Normalize axis
        const float len2 = axis.x * axis.x + axis.y * axis.y + axis.z * axis.z;
        float invLen = len2 > 0.0f ? 1.0f / std::sqrt(len2) : 0.0f;
        const float x = axis.x * invLen;
        const float y = axis.y * invLen;
        const float z = axis.z * invLen;

        const float c = std::cos(angle);
        const float s = std::sin(angle);
        const float omc = 1.0f - c;

        return Mat4({
            { c + x * x * omc,     x * y * omc - z * s, x * z * omc + y * s, 0.0f },
            { y * x * omc + z * s, c + y * y * omc,     y * z * omc - x * s, 0.0f },
            { z * x * omc - y * s, z * y * omc + x * s, c + z * z * omc,     0.0f },
            { 0.0f,                0.0f,                0.0f,                1.0f }
        });
    }

    Mat4 RotateAxisAngleRadians(const Mat4 &m, const Vec3 &axis, float angle)
    {
        return m * RotateAxisAngleRadians(axis, angle);
    }

    Mat4 RotateAxisAngleDegrees(const Vec3 &axis, float degrees)
    {
        return RotateAxisAngleRadians(axis, degrees * DEG_TO_RAD);
    }

    Mat4 AxisAngleRadians(const Vec3 &axis, float angle)
    {
        // Normalize axis
        Vec3 nAxis = Normalize(axis);
        float c = std::cos(angle);
        float s = std::sin(angle);
        float t = 1.0f - c;
        float x = nAxis.x, y = nAxis.y, z = nAxis.z;

        // Rodrigues' rotation formula for 3x3
        Mat4 result = Mat4::Identity();
        result[0][0] = t * x * x + c;
        result[0][1] = t * x * y - s * z;
        result[0][2] = t * x * z + s * y;
        result[1][0] = t * x * y + s * z;
        result[1][1] = t * y * y + c;
        result[1][2] = t * y * z - s * x;
        result[2][0] = t * x * z - s * y;
        result[2][1] = t * y * z + s * x;
        result[2][2] = t * z * z + c;
        // The last row/column remain as for affine transform
        return result;
    }

    Mat4 RotateAxisAngleDegrees(const Mat4 &m, const Vec3 &axis, float degrees)
    {
        return m * RotateAxisAngleDegrees(axis, degrees);
    }

    Mat3 Rotate2D(float radians)
    {
        const float c = std::cos(radians);
        const float s = std::sin(radians);
        return {
            c, -s, 0.0f,
            s,  c, 0.0f,
            0.0f, 0.0f, 1.0f
        };
    }

    Mat3 Rotate2D(const Mat3 &m, float radians)
    {
        return m * Rotate2D(radians);
    }


}

/// -------------------------------------------------------
