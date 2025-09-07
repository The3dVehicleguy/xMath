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
#include <math_config.h>
#include <random>
#include <type_traits>
#include <xMath/includes/constants.h>
#include <xMath/includes/quat.h>
#include <xMath/includes/vector.h>

/// -------------------------------------------------------

namespace xMath
{

    /// Angle conversion helpers
    constexpr float ToRadians(float degrees) { return degrees * DEG_TO_RAD; }
    constexpr float ToDegrees(float radians) { return radians * RAD_TO_DEG; }

    XMATH_API Vec2 ToRadians(const Vec2& d);
    XMATH_API Vec3 ToRadians(const Vec3& d);
    XMATH_API Vec4 ToRadians(const Vec4& d);

    XMATH_API Vec2 ToDegrees(const Vec2& r);
    XMATH_API Vec3 ToDegrees(const Vec3& r);
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


    /// Floating-point helpers
    XMATH_API bool IsEqual(float a, float b, float epsilon = 1e-6f);
    XMATH_API bool IsZero(float value, float epsilon = 1e-6f);

    /// Vector operations (Vec3)
    XMATH_API float Distance(const Vec3& a, const Vec3& b);
    XMATH_API float Length(const Vec3& v);
    XMATH_API float Length2(const Vec3& v);
    XMATH_API Vec3 Normalize(const Vec3& vector);
    XMATH_API float Dot(const Vec3& a, const Vec3& b);
    XMATH_API Vec3 Cross(const Vec3& a, const Vec3& b);

    /// Vector operations (Vec2)
    XMATH_API float Length(const Vec2& v);
    XMATH_API float Length2(const Vec2& v);
    XMATH_API Vec2 Normalize(const Vec2& v);

    /// Vector operations (Vec4)
    XMATH_API float Length(const Vec4& v);
    XMATH_API float Length2(const Vec4& v);
    XMATH_API Vec4 Normalize(const Vec4& v);

    template <typename T>
    constexpr T saturate(T x) { return std::clamp<T>(x, static_cast<T>(0), static_cast<T>(1)); }

    template <class T, class U>
    constexpr T lerp(T lhs, T rhs, U t) { return lhs * (static_cast<U>(1) - t) + rhs * t; }

    template <class T>
    constexpr bool approximate_equals(T lhs, T rhs, T error = std::numeric_limits<T>::epsilon()) { return lhs + error >= rhs && lhs - error <= rhs; }

    template <typename T>
    constexpr int sign(T x) { return (static_cast<T>(0) < x) - (x < static_cast<T>(0)); }

    template <class T>
    inline T random(T from = static_cast<T>(0), T to = static_cast<T>(1))
    {
        std::random_device rd;                             // obtain a random number from hardware
        std::mt19937 eng(rd());                            // seed the generator
        std::uniform_real_distribution<T> distr(from, to); // define the range
        return distr(eng);
    }

    XMATH_API constexpr uint32_t power_of_two_previous(uint32_t x)
    {
        x = x | (x >> 1);
        x = x | (x >> 2);
        x = x | (x >> 4);
        x = x | (x >> 8);
        x = x | (x >> 16);
        return x - (x >> 1);
    }

    XMATH_API constexpr uint32_t power_of_two_next(uint32_t x)
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

    /// Rounding helpers
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
            return x;
    }

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

	/// ---------------------------------------------------------------------

    /// Basic trig wrappers (keep localized for potential SIMD replacement later)
    XMATH_API float  Sin(float v);
    XMATH_API double Sin(double v);
    XMATH_API float  Cos(float v);
    XMATH_API double Cos(double v);
    XMATH_API float  Tan(float v);
    XMATH_API double Tan(double v);
    
    /// TRS (translation, rotation, scale) helpers using native math types
    XMATH_API bool DecomposeTransform(const Mat4 &mat, Vec3 &translation, Quat &rotation, Vec3 &scale);
    XMATH_API Mat4 ComposeTransform(const Vec3 &translation, const Quat &rotation, const Vec3 &scale);
    
    /// Absolute value overloads
    XMATH_API float   Abs(float v);
    XMATH_API double  Abs(double v);
    XMATH_API int32_t Abs(int32_t v);
    XMATH_API int64_t Abs(int64_t v);
    
    /// Root and power
    XMATH_API float Sqrt(float v);

    template<typename T1, typename T2>
    static auto Pow(T1 base, T2 power) { return std::pow(base, power); }
    
    /// Min/Max over initializer_list
    template<typename T>
    static T Min(std::initializer_list<T> list)
    {
        auto it = list.begin();
        T minVal = *it;
        for (++it; it != list.end(); ++it) minVal = (*it < minVal) ? *it : minVal;
        return minVal;
    }
    
    template<typename T>
    static T Max(std::initializer_list<T> list)
    {
        auto it = list.begin();
        T maxVal = *it;
        for (++it; it != list.end(); ++it) maxVal = (*it > maxVal) ? *it : maxVal;
        return maxVal;
    }
    
    /// Binary Min/Max
    template<typename T>
    static T Min(T a, T b) { return a < b ? a : b; }
    
    template<typename T>
    static T Max(T a, T b) { return a > b ? a : b; }
    
    /// Clamping
    template<typename T>
    static T Clamp(T value, T min, T max)
    {
        if (min > max) std::swap(min, max);
        return Min(Max(value, min), max);
    }
    
    template<typename T>
    static T Clamp01(T value) { return Clamp<T>(value, 0, 1); }
    
    /// Rounding
    XMATH_API float   Round(float v);
    XMATH_API double  Round(double v);
    XMATH_API int32_t RoundToInt(float v);
    XMATH_API int64_t RoundToInt64(float v);
    XMATH_API int32_t RoundToInt(double v);
    XMATH_API int64_t RoundToInt64(double v);
    
    /// Interpolation
    XMATH_API float Lerp(float from, float to, float t);
    XMATH_API float LerpUnclamped(float from, float to, float t);
    
    /// Float16 -> Float conversion
    XMATH_API float ToFloat32(uint16_t float16);

    /// NaN check
    template<typename T>
    inline bool IsNan(T value)
    {
        if constexpr (std::is_floating_point_v<T>)
            return std::isnan(value);
        else
            return false;
    }

}

/// -------------------------------------------------------

// -------------------------------------------------------
// GLM compatibility shims for radians/degrees conversions (global ::glm)
// -------------------------------------------------------
namespace glm
{
    float radians(float degrees);
    float degrees(float radians);

    xMath::Vec2 radians(const xMath::Vec2& d);
    xMath::Vec3 radians(const xMath::Vec3& d);
    xMath::Vec4 radians(const xMath::Vec4& d);
    xMath::Vec2 degrees(const xMath::Vec2& r);
    xMath::Vec3 degrees(const xMath::Vec3& r);
    xMath::Vec4 degrees(const xMath::Vec4& r);
}
