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
* vec4.h - TVector4 template
* -------------------------------------------------------
* Created: 12/8/2025
* -------------------------------------------------------
*/
#pragma once

/// -----------------------------------------------------

namespace xMath
{

	template<typename T> struct TVector3;

	template<typename T>
	struct TVector4
	{
		// Provide multiple semantic aliases for components (position/color/texcoord)
		union
		{
			struct { T x, y, z, w; }; // Cartesian
			struct { T r, g, b, a; }; // Color
			struct { T s, t, p, q; }; // Texture (p,q = 3rd/4th coords)
		};

		constexpr TVector4() noexcept : x(0), y(0), z(0), w(0) {}
		constexpr explicit TVector4(T s) noexcept : x(s), y(s), z(s), w(s) {}
		constexpr TVector4(T _x, T _y, T _z, T _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}
		constexpr TVector4(const TVector3<T>& v, T _w) noexcept : x(v.x), y(v.y), z(v.z), w(_w) {}

		/// Basic arithmetic
		[[nodiscard]] constexpr TVector4 operator+(const TVector4& r) const noexcept { return {x + r.x, y + r.y, z + r.z, w + r.w}; }
		[[nodiscard]] constexpr TVector4 operator-(const TVector4& r) const noexcept { return {x - r.x, y - r.y, z - r.z, w - r.w}; }
		[[nodiscard]] constexpr TVector4 operator*(T s) const noexcept { return {x * s, y * s, z * s, w * s}; }
		[[nodiscard]] constexpr TVector4 operator/(T s) const noexcept { return {x / s, y / s, z / s, w / s}; }

		/// Equality
		[[nodiscard]] constexpr bool operator==(const TVector4& r) const noexcept { return x == r.x && y == r.y && z == r.z && w == r.w; }
		[[nodiscard]] constexpr bool operator!=(const TVector4& r) const noexcept { return !(*this == r); }

		constexpr TVector4& operator+=(const TVector4& r) noexcept { x += r.x; y += r.y; z += r.z; w += r.w; return *this; }
		constexpr TVector4& operator-=(const TVector4& r) noexcept { x -= r.x; y -= r.y; z -= r.z; w -= r.w; return *this; }
		constexpr TVector4& operator*=(T s) noexcept { x *= s; y *= s; z *= s; w *= s; return *this; }
		constexpr TVector4& operator/=(T s) noexcept { x /= s; y /= s; z /= s; w /= s; return *this; }

		/// Conversions
		[[nodiscard]] constexpr operator TVector3<T>() const noexcept { return TVector3<T>(x, y, z); }
	    // Allow explicit construction of a Vec3 from a Vec4 without relying on operator cast.
		friend struct TVector3<T>; // Grant access for converting ctor definition below.


		/// Indexing helpers
		[[nodiscard]] constexpr T& operator[](int i) noexcept { return (&x)[i]; }
		[[nodiscard]] constexpr const T& operator[](int i) const noexcept { return (&x)[i]; }
	};

}

/// -----------------------------------------------------
