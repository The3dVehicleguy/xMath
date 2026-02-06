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
#include <type_traits>

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
		};

        //TVector2() { x = 0; y = 0; }
		//constexpr TVector2() noexcept : x(0), y(0) {}

		// Fill-constructor for same-type scalar
		//constexpr explicit TVector2(T s) noexcept : x(s), y(s) {}

		// Cross-type fill-constructor for any arithmetic scalar (excluding identical T to avoid ambiguity)
		/*
	    template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && !std::is_same_v<U, T>>>
		constexpr explicit TVector2(U s) noexcept : x(static_cast<T>(s)), y(static_cast<T>(s)) {}
		*/

	    // Two-component constructor (same type)
		//constexpr TVector2(T _x, T _y) noexcept : x(_x), y(_y) {}

		// Cross-type two-component constructor for arithmetic inputs
		/*
		template<typename U, typename V, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_arithmetic_v<V>>>
		constexpr TVector2(U _x, V _y) noexcept : x(static_cast<T>(_x)), y(static_cast<T>(_y)) {}
		*/

        TVector2(const TVector2 &vector) = default;
        TVector2(float x) { this->x = x; this->y = x;}
        TVector2(float x, float y) { this->x = x; this->y = y; }
        TVector2(int x, int y) { this->x = static_cast<float>(x); this->y = static_cast<float>(y); }
        TVector2(uint32_t x, uint32_t y) { this->x = static_cast<float>(x); this->y = static_cast<float>(y); }
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

}

/// -----------------------------------------------------
