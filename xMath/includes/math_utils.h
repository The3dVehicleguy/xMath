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
* math_utils.h - Mathematical utility functions
* -------------------------------------------------------
* Created: 14/7/2025
* -------------------------------------------------------
*/
#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <initializer_list>
#include <mat4.h>
#include <random>
#include <type_traits>
#include <xMath/config/math_config.h>
#include <xMath/includes/constants.h>
#include <xMath/includes/quat.h>
#include <xMath/includes/vector.h>

// -------------------------------------------------------

namespace xMath
{

	/**
	 * @brief Converts degrees to radians.
	 *
	 * @param degrees The angle in degrees.
	 * @return The angle in radians.
	 */
	constexpr float ToRadians(float degrees) { return degrees * DEG_TO_RAD; }

	/**
	 * @brief Converts radians to degrees.
	 *
	 * @param radians The angle in radians.
	 * @return The angle in degrees.
	 */
	constexpr float ToDegrees(float radians) { return radians * RAD_TO_DEG; }

	/**
	 * @brief Converts a 2D vector from degrees to radians.
	 *
	 * @param d The vector in degrees.
	 * @return The vector in radians.
	 */
	XMATH_API Vec2 ToRadians(const Vec2& d);

	/**
	 * @brief Converts a 3D vector from degrees to radians.
	 *
	 * @param d The vector in degrees.
	 * @return The vector in radians.
	 */
	XMATH_API Vec3 ToRadians(const Vec3& d);

	/**
	 * @brief Converts a 4D vector from degrees to radians.
	 *
	 * @param d The vector in degrees.
	 * @return The vector in radians.
	 */
	XMATH_API Vec4 ToRadians(const Vec4& d);

	/**
	 * @brief Converts a 2D vector from radians to degrees.
	 *
	 * @param r The vector in radians.
	 * @return The vector in degrees.
	 */
	XMATH_API Vec2 ToDegrees(const Vec2& r);

	/**
	 * @brief Converts a 3D vector from radians to degrees.
	 *
	 * @param r The vector in radians.
	 * @return The vector in degrees.
	 */
	XMATH_API Vec3 ToDegrees(const Vec3& r);

	/**
	 * @brief Converts a 4D vector from radians to degrees.
	 *
	 * @param r The vector in radians.
	 * @return The vector in degrees.
	 */
	XMATH_API Vec4 ToDegrees(const Vec4& r);

	/**
	 * @enum Intersection
	 * @brief Enumeration for intersection results
	 *
	 * Used to indicate the result of intersection tests between
	 * the BoundingBox and points or other bounding volumes.
	 *
	 * - Outside: No intersection, the object is completely outside the BoundingBox
	 * - Inside: The object is completely inside the BoundingBox
	 * - Intersects: Partial intersection, the object overlaps with the BoundingBox
	 */
	enum class Intersection : uint8_t
	{
		Outside,
		Inside,
		Intersects
	};


	/**
	 * @brief Checks if two floating-point values are approximately equal within a specified tolerance.
	 *
	 * @param a The first value to compare.
	 * @param b The second value to compare.
	 * @param epsilon The tolerance for comparison.
	 * @return True if the values are equal within the specified tolerance, false otherwise.
	 */
	XMATH_API bool IsEqual(float a, float b, float epsilon = 1e-6f);

	/**
	 * @brief Checks if a floating-point value is approximately zero within a specified tolerance.
	 *
	 * @param value The value to check.
	 * @param epsilon The tolerance for comparison.
	 * @return True if the value is approximately zero within the specified tolerance, false otherwise.
	 */
	XMATH_API bool IsZero(float value, float epsilon = 1e-6f);

	/**
	 * @brief Calculates the distance between two 3D points.
	 *
	 * @param a The first point.
	 * @param b The second point.
	 * @return The distance between the two points.
	 */
	XMATH_API float Distance(const Vec3& a, const Vec3& b);

	/**
	 * @brief Calculates the length (magnitude) of a 3D vector.
	 *
	 * @param v The vector.
	 * @return The length of the vector.
	 */
	XMATH_API float Length(const Vec3& v);

	/**
	 * @brief Calculates the squared length (magnitude) of a 3D vector.
	 *
	 * @param v The vector.
	 * @return The squared length of the vector.
	 */
	XMATH_API float Length2(const Vec3& v);

	/**
	 * @brief Normalizes a 3D vector.
	 *
	 * @param vector The vector to normalize.
	 * @return The normalized vector.
	 */
	XMATH_API Vec3 Normalize(const Vec3& vector);

	/**
	 * @brief Calculates the dot product of two 3D vectors.
	 *
	 * @param a The first vector.
	 * @param b The second vector.
	 * @return The dot product of the two vectors.
	 */
	XMATH_API float Dot(const Vec3& a, const Vec3& b);

	/**
	 * @brief Calculates the cross product of two 3D vectors.
	 *
	 * @param a The first vector.
	 * @param b The second vector.
	 * @return The cross product of the two vectors.
	 */
	XMATH_API Vec3 Cross(const Vec3& a, const Vec3& b);

	/**
	 * @brief Calculates the length (magnitude) of a 2D vector.
	 *
	 * @param v The vector.
	 * @return The length of the vector.
	 */
	XMATH_API float Length(const Vec2& v);

	/**
	 * @brief Calculates the squared length (magnitude) of a 2D vector.
	 *
	 * @param v The vector.
	 * @return The squared length of the vector.
	 */
	XMATH_API float Length2(const Vec2& v);

	/**
	 * @brief Normalizes a 2D vector.
	 *
	 * @param v The vector to normalize.
	 * @return The normalized vector.
	 */
	XMATH_API Vec2 Normalize(const Vec2& v);

	/**
	 * @brief Calculates the length (magnitude) of a 4D vector.
	 *
	 * @param v The vector.
	 * @return The length of the vector.
	 */
	XMATH_API float Length(const Vec4& v);

	/**
	 * @brief Calculates the squared length (magnitude) of a 4D vector.
	 *
	 * @param v The vector.
	 * @return The squared length of the vector.
	 */
	XMATH_API float Length2(const Vec4& v);

	/**
	 * @brief Normalizes a 4D vector.
	 *
	 * @param v The vector to normalize.
	 * @return The normalized vector.
	 */
	XMATH_API Vec4 Normalize(const Vec4& v);

	/**
	 * @brief Clamps a value between 0 and 1.
	 *
	 * @tparam T The type of the value.
	 * @param x The value to clamp.
	 * @return The clamped value.
	 */
	template <typename T>
	constexpr T Saturate(T x)
	{
		return std::clamp<T>(x, static_cast<T>(0), static_cast<T>(1));
	}

	/**
	 * @brief Linearly interpolates between two values.
	 *
	 * @tparam T The type of the values.
	 * @tparam U The type of the interpolation factor.
	 * @param lhs The starting value.
	 * @param rhs The ending value.
	 * @param t The interpolation factor.
	 * @return The interpolated value.
	 */
	template <class T, class U>
	constexpr T Lerp(T lhs, T rhs, U t)
	{
		return lhs * (static_cast<U>(1) - t) + rhs * t;
	}

	/**
	 * @brief Checks if two values are approximately equal within a specified error margin.
	 *
	 * @tparam T The type of the values.
	 * @param lhs The first value.
	 * @param rhs The second value.
	 * @param error The allowable error margin.
	 * @return True if the values are approximately equal, false otherwise.
	 */
	template <class T>
	constexpr bool ApproximateEquals(T lhs, T rhs, T error = std::numeric_limits<T>::epsilon())
	{
		return lhs + error >= rhs && lhs - error <= rhs;
	}

	/**
	 * @brief Determines the sign of a value.
	 *
	 * @tparam T The type of the value.
	 * @param x The value to check.
	 * @return The sign of the value.
	 */
	template <typename T>
	constexpr int Sign(T x)
	{
		return (static_cast<T>(0) < x) - (x < static_cast<T>(0));
	}

	/**
	 * @brief Generates a random number within a specified range.
	 *
	 * @tparam T The type of the random number.
	 * @param from The lower bound of the range.
	 * @param to The upper bound of the range.
	 * @return A random number within the specified range.
	 */
	template <class T>
	inline T Random(T from = static_cast<T>(0), T to = static_cast<T>(1))
	{
		std::random_device rd;                             // obtain a random number from hardware
		std::mt19937 eng(rd());                        // seed the generator
		std::uniform_real_distribution<T> distr(from, to); // define the range
		return distr(eng);
	}

	/**
	 * @brief Finds the previous power of two for a given value.
	 *
	 * @param x The value to find the previous power of two for.
	 * @return The previous power of two.
	 */
	XMATH_API constexpr uint32_t PowerOfTwoPrevious(uint32_t x)
	{
		x = x | (x >> 1);
		x = x | (x >> 2);
		x = x | (x >> 4);
		x = x | (x >> 8);
		x = x | (x >> 16);
		return x - (x >> 1);
	}

	/**
	 * @brief Finds the next power of two for a given value.
	 *
	 * @param x The value to find the next power of two for.
	 * @return The next power of two.
	 */
	XMATH_API constexpr uint32_t PowerOfTwoNext(uint32_t x)
	{
		if (x < 2)
			return 2;

		if (x % 2 == 0)
			return x << 1;

		--x;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		x |= x >> 16;
		return x++;
	}

	/**
	 * @brief Rounds a value down to the nearest multiple of a specified factor.
	 *
	 * @tparam T The type of the value.
	 * @param x The value to round down.
	 * @param fac The factor to round down to.
	 * @return The rounded down value.
	 */
	template <typename T>
	constexpr T RoundDown(T x, T fac)
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return fac == static_cast<T>(0) ? x : std::floor(x / fac) * fac;
		}
		else if constexpr (std::is_integral_v<T>)
		{
			return fac == static_cast<T>(0) ? x : static_cast<T>(x - (x % fac));
		}
		else
		{
			return x;
		}
	}

	/**
	 * @brief Rounds a value up to the nearest multiple of a specified factor.
	 *
	 * @tparam T The type of the value.
	 * @param x The value to round up.
	 * @param fac The factor to round up to.
	 * @return The rounded up value.
	 */
	template <typename T>
	constexpr T RoundUp(T x, T fac)
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return fac == static_cast<T>(0) ? x : std::ceil(x / fac) * fac;
		}
		else if constexpr (std::is_integral_v<T>)
		{
			if (fac == static_cast<T>(0))
				return x;
			return static_cast<T>(((x + (fac - 1)) / fac) * fac);
		}
		else
		{
			return x;
		}
	}

	/**
	 * @brief Computes the sine of a value.
	 *
	 * @param v The value in radians.
	 * @return The sine of the value.
	 */
	XMATH_API float  Sin(float v);

	/**
	 * @brief Computes the sine of a value.
	 *
	 * @param v The value in radians.
	 * @return The sine of the value.
	 */
	XMATH_API double Sin(double v);

	/**
	 * @brief Computes the cosine of a value.
	 *
	 * @param v The value in radians.
	 * @return The cosine of the value.
	 */
	XMATH_API float  Cos(float v);

	/**
	 * @brief Computes the cosine of a value.
	 *
	 * @param v The value in radians.
	 * @return The cosine of the value.
	 */
	XMATH_API double Cos(double v);

	/**
	 * @brief Computes the tangent of a value.
	 *
	 * @param v The value in radians.
	 * @return The tangent of the value.
	 */
	XMATH_API float  Tan(float v);

	/**
	 * @brief Computes the tangent of a value.
	 *
	 * @param v The value in radians.
	 * @return The tangent of the value.
	 */
	XMATH_API double Tan(double v);

	/**
	 * @brief Composes a transformation matrix from translation, rotation, and scale components.
	 *
	 * @param mat The transformation matrix to decompose.
	 * @param translation The output translation component.
	 * @param rotation The output rotation component.
	 * @param scale The output scale component.
	 * @return True if the decomposition was successful, false otherwise.
	 */
	XMATH_API bool DecomposeTransform(const Mat4 &mat, Vec3 &translation, Quat &rotation, Vec3 &scale);

	/**
	 * @brief Composes a transformation matrix from translation, rotation, and scale components.
	 *
	 * @param translation The translation component.
	 * @param rotation The rotation component.
	 * @param scale The scale component.
	 * @return The composed transformation matrix.
	 */
	XMATH_API Mat4 ComposeTransform(const Vec3 &translation, const Quat &rotation, const Vec3 &scale);

	/**
	 * @brief Computes the absolute value of a float.
	 *
	 * @param v The value.
	 * @return The absolute value.
	 */
	XMATH_API float   Abs(float v);

	/**
	 * @brief Computes the absolute value of a double.
	 *
	 * @param v The value.
	 * @return The absolute value.
	 */
	XMATH_API double  Abs(double v);

	/**
	 * @brief Computes the absolute value of a 32-bit integer.
	 *
	 * @param v The value.
	 * @return The absolute value.
	 */
	XMATH_API int32_t Abs(int32_t v);

	/**
	 * @brief Computes the absolute value of a 64-bit integer.
	 *
	 * @param v The value.
	 * @return The absolute value.
	 */
	XMATH_API int64_t Abs(int64_t v);


	/**
	 * @brief Computes the square root of a float.
	 *
	 * @param v The value.
	 * @return The square root of the value.
	 */
	XMATH_API float Sqrt(float v);

	/**
	 * @brief Raises a base to the power of an exponent.
	 *
	 * @tparam T1 The type of the base.
	 * @tparam T2 The type of the exponent.
	 * @param base The base value.
	 * @param power The exponent value.
	 * @return The result of raising the base to the power.
	 */
	template<typename T1, typename T2>
	static auto Pow(T1 base, T2 power)
	{
		return std::pow(base, power);
	}

	/**
	 * @brief Computes the minimum value in a list.
	 *
	 * @tparam T The type of the elements.
	 * @param list The list of values.
	 * @return The minimum value.
	 */
	template<typename T>
	static T Min(std::initializer_list<T> list)
	{
		auto it = list.begin();
		T minVal = *it;
		for (++it; it != list.end(); ++it) minVal = (*it < minVal) ? *it : minVal;
		return minVal;
	}

	/**
	 * @brief Computes the maximum value in a list.
	 *
	 * @tparam T The type of the elements.
	 * @param list The list of values.
	 * @return The maximum value.
	 */
	template<typename T>
	static T Max(std::initializer_list<T> list)
	{
		auto it = list.begin();
		T maxVal = *it;
		for (++it; it != list.end(); ++it) maxVal = (*it > maxVal) ? *it : maxVal;
		return maxVal;
	}

	/**
	 * @brief Computes the minimum of two values.
	 *
	 * @tparam T The type of the values.
	 * @param a The first value.
	 * @param b The second value.
	 * @return The minimum value.
	 */
	template<typename T>
	static T Min(T a, T b)
	{
		return a < b ? a : b;
	}

	/**
	 * @brief Computes the maximum of two values.
	 *
	 * @tparam T The type of the values.
	 * @param a The first value.
	 * @param b The second value.
	 * @return The maximum value.
	 */
	template<typename T>
	static T Max(T a, T b)
	{
		return a > b ? a : b;
	}

	/**
	 * @brief Clamps a value between a minimum and maximum.
	 *
	 * @tparam T The type of the value.
	 * @param value The value to clamp.
	 * @param min The minimum value.
	 * @param max The maximum value.
	 * @return The clamped value.
	 */
	template<typename T>
	static T Clamp(T value, T min, T max)
	{
		if (min > max) std::swap(min, max);
		return Min(Max(value, min), max);
	}

	/**
	 * @brief Clamps a value between 0 and 1.
	 *
	 * @tparam T The type of the value.
	 * @param value The value to clamp.
	 * @return The clamped value between 0 and 1.
	 */
	template<typename T>
	static T Clamp01(T value)
	{
		return Clamp<T>(value, 0, 1);
	}

	/**
	 * @brief Rounds a float to the nearest integer.
	 *
	 * @param v The value to round.
	 * @return The rounded value.
	 */
	XMATH_API float Round(float v);

	/**
	 * @brief Rounds a double to the nearest integer.
	 *
	 * @param v The value to round.
	 * @return The rounded value.
	 */
	XMATH_API double Round(double v);

	/**
	 * @brief Rounds a float to the nearest 32-bit integer.
	 *
	 * @param v The value to round.
	 * @return The rounded 32-bit integer.
	 */
	XMATH_API int32_t RoundToInt(float v);

	/**
	 * @brief Rounds a float to the nearest 64-bit integer.
	 *
	 * @param v The value to round.
	 * @return The rounded 64-bit integer.
	 */
	XMATH_API int64_t RoundToInt64(float v);

	/**
	 * @brief Rounds a double to the nearest 32-bit integer.
	 *
	 * @param v The value to round.
	 * @return The rounded 32-bit integer.
	 */
	XMATH_API int32_t RoundToInt(double v);

	/**
	 * @brief Rounds a double to the nearest 64-bit integer.
	 *
	 * @param v The value to round.
	 * @return The rounded 64-bit integer.
	 */
	XMATH_API int64_t RoundToInt64(double v);

	/**
	 * @brief Linearly interpolates between two values.
	 *
	 * @param from The starting value.
	 * @param to The ending value.
	 * @param t The interpolation factor (0.0 to 1.0).
	 * @return The interpolated value.
	 */
	XMATH_API float Lerp(float from, float to, float t);

	/**
	 * @brief Linearly interpolates between two values without clamping.
	 *
	 * @param from The starting value.
	 * @param to The ending value.
	 * @param t The interpolation factor.
	 * @return The interpolated value.
	 */
	XMATH_API float LerpUnclamped(float from, float to, float t);

	/**
	 * @brief Converts a 16-bit floating-point value to a 32-bit floating-point value.
	 *
	 * @param float16 The 16-bit floating-point value.
	 * @return The converted 32-bit floating-point value.
	 */
	XMATH_API float ToFloat32(uint16_t float16);

	/**
	 * @brief Checks if a value is NaN (Not a Number).
	 *
	 * @tparam T The type of the value.
	 * @param value The value to check.
	 * @return True if the value is NaN, false otherwise.
	 */
	template<typename T>
	inline bool IsNan(T value)
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return std::isnan(value);
		}
		else
		{
			return false;
		}
	}

}

// -------------------------------------------------------
// GLM compatibility shims for radians/degrees conversions (global ::glm)
// -------------------------------------------------------
namespace glm
{
	/**
	 * @brief Converts degrees to radians.
	 *
	 * @param degrees The angle in degrees.
	 * @return The angle in radians.
	 */
	float Radians(float degrees);

	/**
	 * @brief Converts radians to degrees.
	 *
	 * @param radians The angle in radians.
	 * @return The angle in degrees.
	 */
	float Degrees(float radians);

	/**
	 * @brief Converts a 2D vector from degrees to radians.
	 *
	 * @param d The 2D vector in degrees.
	 * @return The 2D vector in radians.
	 */
	xMath::Vec2 Radians(const xMath::Vec2& d);

	/**
	 * @brief Converts a 3D vector from degrees to radians.
	 *
	 * @param d The 3D vector in degrees.
	 * @return The 3D vector in radians.
	 */
	xMath::Vec3 Radians(const xMath::Vec3& d);

	/**
	 * @brief Converts a 4D vector from degrees to radians.
	 *
	 * @param d The 4D vector in degrees.
	 * @return The 4D vector in radians.
	 */
	xMath::Vec4 Radians(const xMath::Vec4& d);

	/**
	 * @brief Converts a 2D vector from radians to degrees.
	 *
	 * @param r The 2D vector in radians.
	 * @return The 2D vector in degrees.
	 */
	xMath::Vec2 Degrees(const xMath::Vec2& r);

	/**
	 * @brief Converts a 3D vector from radians to degrees.
	 *
	 * @param r The 3D vector in radians.
	 * @return The 3D vector in degrees.
	 */
	xMath::Vec3 Degrees(const xMath::Vec3& r);

	/**
	 * @brief Converts a 4D vector from radians to degrees.
	 *
	 * @param r The 4D vector in radians.
	 * @return The 4D vector in degrees.
	 */
	xMath::Vec4 Degrees(const xMath::Vec4& r);

}
