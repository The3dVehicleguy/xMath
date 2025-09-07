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
* math_utils.cpp - Mathematical utility functions
* -------------------------------------------------------
* Created: 12/8/2025
* -------------------------------------------------------
*/
#include <math_utils.h>
#include <xMath/includes/quat.h>
#include <xMath/includes/transforms.h>
#include <xMath/includes/vector.h>

/// -----------------------------------------------------

namespace xMath
{

    Vec2 ToRadians(const Vec2 &d)
    {
        return { d.x * DEG_TO_RAD, d.y * DEG_TO_RAD };
    }

    Vec3 ToRadians(const Vec3 &d)
    {
        return { d.x * DEG_TO_RAD, d.y * DEG_TO_RAD, d.z * DEG_TO_RAD };
    }

    Vec4 ToRadians(const Vec4 &d)
    {
        return { d.x * DEG_TO_RAD, d.y * DEG_TO_RAD, d.z * DEG_TO_RAD, d.w * DEG_TO_RAD };
    }

    Vec2 ToDegrees(const Vec2 &r)
    {
        return { r.x * RAD_TO_DEG, r.y * RAD_TO_DEG };
    }

    Vec3 ToDegrees(const Vec3 &r)
    {
        return { r.x * RAD_TO_DEG, r.y * RAD_TO_DEG, r.z * RAD_TO_DEG };
    }

    Vec4 ToDegrees(const Vec4 &r)
    {
        return { r.x * RAD_TO_DEG, r.y * RAD_TO_DEG, r.z * RAD_TO_DEG, r.w * RAD_TO_DEG };
    }

    /**
	 * @brief Checks if two floating-point numbers are approximately equal within a given epsilon.
	 *
	 * This function compares the absolute difference between two numbers.
	 *
	 * @param a
	 * @param b
	 * @param epsilon
	 * @return true if the absolute difference between a and b is less than or equal to epsilon, false otherwise.
	 */
	bool IsEqual(float a, float b, float epsilon)
	{
	    return fabsf(a - b) <= epsilon;
	}

    /**
     * @brief Checks if a floating-point number is approximately zero within a given epsilon.
     *
     * This function determines if the absolute value of the number
     * is less than or equal to epsilon.
     *
     * @param value
     * @param epsilon
     * @return true if the absolute value of the number is less than or equal to epsilon, false otherwise.
     */
    bool IsZero(float value, float epsilon)
	{
	    return fabsf(value) <= epsilon;
	}

    /**
     * @brief Calculates the distance between two 3D points.
     *
     * This function computes the Euclidean distance between two points in 3D space.
     *
     * @param a
     * @param b
     * @return The Euclidean distance between points a and b.
     */
    float Distance(const Vec3& a, const Vec3& b)
	{
	    const float dx = b.x - a.x;
	    const float dy = b.y - a.y;
	    const float dz = b.z - a.z;
	    return sqrtf(dx*dx + dy*dy + dz*dz);
	}

    /**
	 * @brief Calculates the length of a 3D vector.
	 *
	 * This function computes the Euclidean length (magnitude) of the vector
	 *
	 * @param v
	 * @return The Euclidean length of the vector v.
	 */
	float Length(const Vec3& v)
	{
		return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	}

    /**
     * @brief Calculates the squared length of a 3D vector.
     *
     * This function is useful for performance when you only need to compare lengths
     *
     * @param v
     * @return The squared length of the vector v.
     */
    float Length2(const Vec3& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}

    /**
     * @brief Normalizes a 3D vector.
     *
     * This function returns a new vector that has the same direction
     * as the input vector but with a length of 1.
     *
     * @param v
     * @return A new Vec3 that is the normalized version of v.
     */
    Vec3 Normalize(const Vec3& v)
	{
	    const float len2 = v.x*v.x + v.y*v.y + v.z*v.z;
	    if (len2 <= 0.0f)
            return {0.0f, 0.0f, 0.0f};

        const float invLen = 1.0f / sqrtf(len2);
	    return {v.x*invLen, v.y*invLen, v.z*invLen};
	}

    /**
     * @brief Calculates the dot product of two 3D vectors.
     *
     * This function computes the dot product, which is a measure of how
     * aligned two vectors are. It is defined as the sum of the products
     * of their corresponding components.
     *
     * @param a First vector a
     * @param b Second vector b
     * @return The dot product of vectors a and b.
     */
    float Dot(const Vec3& a, const Vec3& b)
	{
	    return a.x*b.x + a.y*b.y + a.z*b.z;
	}

    /**
     * @brief Calculates the cross product of two 3D vectors.
     *
     * This function computes the cross product, which results in a vector
     * that is perpendicular to both input vectors. The direction of the
     * resulting vector follows the right-hand rule.
     *
     * @param a First vector a
     * @param b Second vector b
     * @return A new Vec3 that is the cross product of a and b.
     */
    Vec3 Cross(const Vec3& a, const Vec3& b)
	{
	    return {
	        a.y * b.z - a.z * b.y,	/// X
	        a.z * b.x - a.x * b.z,	/// Y
	        a.x * b.y - a.y * b.x		/// Z
	    };
	}

	/// ---------------------------------------------------------------------
	/// Compatibility wrappers (glm::quat <-> native Quat)
	/// ---------------------------------------------------------------------

    /*
    bool xMath::DecomposeTransform(const Mat4 &mat, Vec3 &translation, Quat &rotation, Vec3 &scale)
	{
		Quat nativeQ;
		const bool ok = DecomposeTransform(mat, translation, nativeQ, scale);
		if (ok)
            rotation = Quat(nativeQ.w, nativeQ.x, nativeQ.y, nativeQ.z);
		return ok;
	}
	*/

	/*
    Mat4 xMath::ComposeTransform(const Vec3 &translation, const Quat &rotation, const Vec3 &scale)
	{
		const Quat q(rotation.w, rotation.x, rotation.y, rotation.z);
		return ComposeTransform(translation, q, scale);
	}
	*/

    float Sin(float v)
    {
        return std::sin(v);
    }

    double Sin(double v)
    {
        return std::sin(v);
    }

    float Cos(float v)
    {
        return std::cos(v);
    }

    double Cos(double v)
    {
        return std::cos(v);
    }

    float Tan(float v)
    {
        return std::tan(v);
    }

    double Tan(double v)
    {
        return std::tan(v);
    }

    /// ---------------------------------------------------------------------
    /// Native Quat overloads (no GLM types)
    /// ---------------------------------------------------------------------

    /**
     * @brief Decomposes a transformation matrix into translation, rotation, and scale components.
     *
     * This function extracts the translation, rotation (as a quaternion), and scale
     * from a 4x4 transformation matrix. It is useful for breaking down complex
     * transformations into their individual components for further manipulation or analysis.
     *
     * @param mat The transformation matrix to decompose
     * @param translation Output parameter for the translation vector
     * @param rotation Output parameter for the rotation quaternion
     * @param scale Output parameter for the scale vector
     * @return true if the decomposition was successful, false otherwise.
     */
	bool DecomposeTransform(const Mat4 &mat, Vec3 &translation, Quat &rotation, Vec3 &scale)
	{
        return Transforms::Decompose(mat, translation, rotation, scale);
	}

    /**
     * @brief Composes a transformation Mat4 matrix from translation, rotation, and scale components.
     *
     * This function creates a 4x4 transformation matrix that combines
     * the specified translation, rotation (as a quaternion), and scale.
     *
     * @param translation
     * @param rotation
     * @param scale
     * @return A 4x4 transformation matrix representing the combined transformation.
     */
    Mat4 ComposeTransform(const Vec3 &translation, const Quat &rotation, const Vec3 &scale)
    {
        return Transforms::Compose(translation, rotation, scale);
	}

    float Abs(float v)
    {
        return std::fabs(v);
    }

    double Abs(double v)
    {
        return std::fabs(v);
    }

    int32_t Abs(int32_t v)
    {
        return v < 0 ? -v : v;
    }

    int64_t Abs(int64_t v)
    {
        return v < 0 ? -v : v;
    }

    float Sqrt(float v)
    {
        return std::sqrt(v);
    }

    float Round(float v)
    {
        return std::round(v);
    }

    double Round(double v)
    {
        return std::round(v);
    }

    int32_t RoundToInt(float v)
    {
        return static_cast<int32_t>(std::lround(v));
    }

    int64_t RoundToInt64(float v)
    {
        return static_cast<int64_t>(std::llround(v));
    }

    int32_t RoundToInt(double v)
    {
        return static_cast<int32_t>(std::lround(v));
    }

    int64_t RoundToInt64(double v)
    {
        return static_cast<int64_t>(std::llround(v));
    }

    float Lerp(float from, float to, float t)
    {
        const float tt = Clamp01(t);
        return from * (1.0f - tt) + to * tt;
    }

    float LerpUnclamped(float from, float to, float t)
    {
        return from * (1.0f - t) + to * t;
    }

    float ToFloat32(uint16_t float16)
    {
        uint32_t t1 = float16 & 0x7fffu;       /// Non-sign bits
        uint32_t t2 = float16 & 0x8000u;       /// Sign bit
        const uint32_t t3 = float16 & 0x7c00u; /// Exponent

        t1 <<= 13u;            /// Align mantissa on MSB
        t2 <<= 16u;            /// Shift sign into position
        t1 += 0x38000000;      /// Adjust bias
        t1 = t3 == 0 ? 0 : t1; /// Denormals-as-zero
        t1 |= t2;              /// Re-insert sign bit
        return *reinterpret_cast<float *>(&t1);
    }

}

/// -------------------------------------------------------

float glm::radians(float degrees)
{
    return ::xMath::ToRadians(degrees);
}

float glm::degrees(float radians)
{
    return ::xMath::ToDegrees(radians);
}

xMath::Vec2 glm::radians(const xMath::Vec2 &d)
{
    return { ::xMath::ToRadians(d.x), ::xMath::ToRadians(d.y) };
}

xMath::Vec3 glm::radians(const xMath::Vec3 &d)
{
    return { ::xMath::ToRadians(d.x), ::xMath::ToRadians(d.y), ::xMath::ToRadians(d.z) };
}

xMath::Vec4 glm::radians(const xMath::Vec4 &d)
{
    return { ::xMath::ToRadians(d.x), ::xMath::ToRadians(d.y), ::xMath::ToRadians(d.z), ::xMath::ToRadians(d.w) };
}

xMath::Vec2 glm::degrees(const xMath::Vec2 &r)
{
    return { ::xMath::ToDegrees(r.x), ::xMath::ToDegrees(r.y) };
}

xMath::Vec3 glm::degrees(const xMath::Vec3 &r)
{
    return { ::xMath::ToDegrees(r.x), ::xMath::ToDegrees(r.y), ::xMath::ToDegrees(r.z) };
}

xMath::Vec4 glm::degrees(const xMath::Vec4 &r)
{
    return { ::xMath::ToDegrees(r.x), ::xMath::ToDegrees(r.y), ::xMath::ToDegrees(r.z), ::xMath::ToDegrees(r.w) };
}


/// -------------------------------------------------------
