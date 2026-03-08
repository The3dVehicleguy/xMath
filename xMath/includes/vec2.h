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
* vec2.h - TVector2 template
* -------------------------------------------------------
* Created: 12/8/2025
* -------------------------------------------------------
*/
#pragma once
#include <cmath>
#include <limits>

/// -----------------------------------------------------

namespace xMath
{

	template<typename T>
	struct TVector2
	{
		// Provide multiple semantic aliases for components (position/color/texcoord)
		union
		{
			struct { T x, y; }; // Cartesian
			struct { T r, g; }; // Color
			struct { T s, t; }; // Texture
			struct { T u, v; }; // UV (alternative texture coordinate naming)
		};

		constexpr TVector2() noexcept = default;
	    constexpr explicit TVector2(T s) noexcept : x(s), y(s) {}
		constexpr TVector2(T _x, T _y) noexcept : x(_x), y(_y) {}

		TVector2(const TVector2 &vector) = default;
		~TVector2() = default;

		// Basic arithmetic (all pure, mark [[nodiscard]])
		[[nodiscard]] constexpr TVector2 operator+(const TVector2& r) const noexcept { return {x + r.x, y + r.y}; }
		[[nodiscard]] constexpr TVector2 operator-(const TVector2& r) const noexcept { return {x - r.x, y - r.y}; }
		//[[nodiscard]] constexpr TVector2 operator*(T s) const noexcept { return {x * s, y * s}; }
		//[[nodiscard]] constexpr TVector2 operator/(T s) const noexcept { return {x / s, y / s}; }
	    TVector2 operator-() const { return TVector2(-x, -y); }
        TVector2 operator/(const TVector2& rhs) const { return TVector2(x / rhs.x, y / rhs.y); }
        TVector2 operator/(const float rhs) const { return TVector2(x / rhs, y / rhs); }
	    TVector2 operator*(const float value) const { return TVector2(x * value, y * value); }
        TVector2 operator*(const TVector2 &b) const { return TVector2(x * b.x, y * b.y); }

        // Equality
		[[nodiscard]] constexpr bool operator==(const TVector2& r) const noexcept { return x == r.x && y == r.y; }
		[[nodiscard]] constexpr bool operator!=(const TVector2& r) const noexcept { return !(*this == r); }

	    void operator-=(const TVector2& rhs) { x -= rhs.x; y -= rhs.y; }
        void operator*=(const TVector2 &b) { x *= b.x; y *= b.y; }
	    void operator/=(const TVector2& rhs) { x /= rhs.x; y /= rhs.y; }
		// Avoid division by zero
	    void Normalize() { float length = Length(); if (length > 0.0001f) { x /= length; y /= length; } else { x = 0.0f; y = 0.0f; } }

	    [[nodiscard]] TVector2 Normalized() const { TVector2 result = *this; result.Normalize(); return result; }
		constexpr TVector2& operator+=(const TVector2& r) noexcept { x += r.x; y += r.y; return *this; }
		//constexpr TVector2& operator-=(const TVector2& r) noexcept { x -= r.x; y -= r.y; return *this; }
		constexpr TVector2& operator*=(T s) noexcept { x *= s; y *= s; return *this; }
		constexpr TVector2& operator/=(T s) noexcept { x /= s; y /= s; return *this; }

		// Named constant vectors
		static const TVector2 Zero;
		static const TVector2 One;
		static const TVector2 Left;
		static const TVector2 Right;
		static const TVector2 Up;
		static const TVector2 Down;
		static const TVector2 Forward;
		static const TVector2 Backward;
		static const TVector2 Infinity;
		static const TVector2 InfinityNeg;

		//Non-Number Check
		[[nodiscard]] constexpr bool IsNaN() const noexcept { return x != x || y != y; }
		[[nodiscard]] TVector2 Abs() const { return TVector2(abs(x), abs(y)); }

        // Min/Max
        static TVector2 Min(const TVector2 &a, const TVector2 &b) { return TVector2(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y); }
        static TVector2 Max(const TVector2 &a, const TVector2 &b) { return TVector2(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y); }

		// Utility
		[[nodiscard]] constexpr T& operator[](int i) noexcept { return i == 0 ? x : y; }
		[[nodiscard]] constexpr const T& operator[](int i) const noexcept { return i == 0 ? x : y; }
	    [[nodiscard]] const float* Data() const { return &x; }

		// Length helpers (for floating-point specializations)
	    [[nodiscard]] float Length() const { return sqrt(x * x + y * y); }
		[[nodiscard]] constexpr T Length2() const noexcept { return x * x + y * y; }

	    static float Distance(const TVector2& a, const TVector2& b) { return (b - a).Length(); }
        static float DistanceSquared(const TVector2& a, const TVector2& b) { return (b - a).Length2(); }
	};

	// Named constant vector definitions (out-of-class so TVector2<T> is a complete type)
	template<typename T> inline constexpr TVector2<T> TVector2<T>::Zero{T(0), T(0)};
	template<typename T> inline constexpr TVector2<T> TVector2<T>::One{T(1), T(1)};
	template<typename T> inline constexpr TVector2<T> TVector2<T>::Left{T(-1), T(0)};
	template<typename T> inline constexpr TVector2<T> TVector2<T>::Right{T(1), T(0)};
	template<typename T> inline constexpr TVector2<T> TVector2<T>::Up{T(0), T(1)};
	template<typename T> inline constexpr TVector2<T> TVector2<T>::Down{T(0), T(-1)};
	template<typename T> inline constexpr TVector2<T> TVector2<T>::Forward{T(0), T(0)};
	template<typename T> inline constexpr TVector2<T> TVector2<T>::Backward{T(0), T(0)};
	template<typename T> inline constexpr TVector2<T> TVector2<T>::Infinity{std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()};
	template<typename T> inline constexpr TVector2<T> TVector2<T>::InfinityNeg{-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()};

}

/// -----------------------------------------------------
