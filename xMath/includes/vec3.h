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
* vec3.h - TVector3 template
* -------------------------------------------------------
* Created: 12/8/2025
* -------------------------------------------------------
*/
#pragma once
#include <limits>

/// -----------------------------------------------------

namespace xMath
{

    // Forward declaration to allow declaring converting constructor without including vec4.h here.
	template<typename T> struct TVector4;

	template<typename T>
	struct TVector3
	{
		// Provide multiple semantic aliases for components (position/color/texcoord)
		union
		{
			struct { T x, y, z; }; // Cartesian
			struct { T r, g, b; }; // Color
			struct { T s, t, p; }; // Texture (p = third coordinate)
		};
        constexpr TVector3() noexcept = default;
		//constexpr TVector3() noexcept : x(0), y(0), z(0) {}
		constexpr explicit TVector3(T s) noexcept : x(s), y(s), z(s) {}
		constexpr TVector3(T _x, T _y, T _z) noexcept : x(_x), y(_y), z(_z) {}

		/**
		 * @brief Converting constructor from a 4D vector (drops w component).
		 *
		 * Marked explicit to avoid competing with TVector4<T>::operator TVector3<T>() and
		 * thereby preventing ambiguous user-defined conversions (MSVC E0348) when
		 * assigning a TVector4<T> to a TVector3<T> destination.
		 * @param v The 4D vector to convert from.
         */
	    explicit constexpr TVector3(const TVector4<T>& v) noexcept : x(v.x), y(v.y), z(v.z) {}

		// Basic arithmetic
		[[nodiscard]] constexpr TVector3 operator+(const TVector3& r) const noexcept { return {x + r.x, y + r.y, z + r.z}; }
		[[nodiscard]] constexpr TVector3 operator-(const TVector3& r) const noexcept { return {x - r.x, y - r.y, z - r.z}; }
		[[nodiscard]] constexpr TVector3 operator*(T s) const noexcept { return {x * s, y * s, z * s}; }
		[[nodiscard]] constexpr TVector3 operator/(T s) const noexcept { return {x / s, y / s, z / s}; }

		// Equality
		[[nodiscard]] constexpr bool operator==(const TVector3& r) const noexcept { return x == r.x && y == r.y && z == r.z; }
		[[nodiscard]] constexpr bool operator!=(const TVector3& r) const noexcept { return !(*this == r); }

		// Unary minus
		[[nodiscard]] constexpr TVector3 operator-() const noexcept { return TVector3{-x, -y, -z}; }

		constexpr TVector3& operator+=(const TVector3& r) noexcept { x += r.x; y += r.y; z += r.z; return *this; }
		constexpr TVector3& operator-=(const TVector3& r) noexcept { x -= r.x; y -= r.y; z -= r.z; return *this; }
		constexpr TVector3& operator*=(T s) noexcept { x *= s; y *= s; z *= s; return *this; }
		constexpr TVector3& operator/=(T s) noexcept { x /= s; y /= s; z /= s; return *this; }
	    //TVector3& operator*(float scalar) const { return TVector3(x * scalar, y * scalar, z * scalar); }

		// Indexing helpers
		[[nodiscard]] constexpr T& operator[](int i) noexcept { return (&x)[i]; }
		[[nodiscard]] constexpr const T& operator[](int i) const noexcept { return (&x)[i]; }

		// Named constant vectors
		template<typename T>
        static inline constexpr TVector3<T> Zero = TVector3<T>(T(0), T(0), T(0));
		template<typename T>
        static inline constexpr TVector3<T> One = TVector3(T(1), T(1), T(1));
		template<typename T>
        static inline constexpr TVector3<T> Left = TVector3(T(-1), T(0), T(0));
		template<typename T>
        static inline constexpr TVector3<T> Right = TVector3(T(1), T(0), T(0));
		template<typename T>
        static inline constexpr TVector3<T> Up = TVector3(T(0), T(1), T(0));
		template<typename T>
        static inline constexpr TVector3<T> Down = TVector3(T(0), T(-1), T(0));
		template<typename T>
		static inline constexpr TVector3<T> Forward = TVector3(T(0), T(0), T(1));
		template<typename T>
		static inline constexpr TVector3<T> Backward = TVector3(T(0), T(0), T(-1));
		template<typename T>
		static inline constexpr TVector3<T> Infinity = TVector3(std::numeric_limits<T>::infinity(),  std::numeric_limits<T>::infinity(),  std::numeric_limits<T>::infinity());
		template<typename T>
		static inline constexpr TVector3<T> InfinityNeg = TVector3(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity());

		//Non-Number Check
		[[nodiscard]] constexpr bool IsNaN() const noexcept { return x != x || y != y || z != z; }
	    [[nodiscard]] TVector3 Abs() const { return TVector3(abs(x), abs(y), abs(z)); }
	};

	// Free-function scalar multiplication to support expressions like: float * Vec3
	template<typename T>
	[[nodiscard]] constexpr TVector3<T> operator*(T s, const TVector3<T>& v) noexcept { return TVector3<T>(v.x * s, v.y * s, v.z * s); }

}

/// -----------------------------------------------------
