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

// -----------------------------------------------------

namespace xMath
{

	template<typename T> struct TVector3;

	/**
	 * @brief 4D vector type with components (x, y, z, w).
	 * @tparam T The type of the vector components.
	 */
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

		/* @brief Default constructor initializes all components to zero. */
		constexpr TVector4() noexcept : x(0), y(0), z(0), w(0) {}

		/**
		 * @brief Constructor that initializes all components to the same value.
		 *
		 * @param s The value to set all components to.
		 */
		constexpr explicit TVector4(T s) noexcept : x(s), y(s), z(s), w(s) {}

		/**
		 * @brief Constructor that initializes each component individually.
		 *
		 * @param _x The value for the x component.
		 * @param _y The value for the y component.
		 * @param _z The value for the z component.
		 * @param _w The value for the w component.
		 */
		constexpr TVector4(T _x, T _y, T _z, T _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}

		/**
		 * @brief Constructor that initializes a 4D vector from a 3D vector and an additional w component.
		 *
		 * @param v The 3D vector to initialize the x, y, and z components.
		 * @param _w The value for the w component.
		 */
		constexpr TVector4(const TVector3<T>& v, T _w) noexcept : x(v.x), y(v.y), z(v.z), w(_w) {}

		/**
		 * @brief Adds another vector to this vector and returns the result as a new vector.
		 *
		 * @param r The vector to add to this vector.
		 * @return A new TVector4 that is the sum of this vector and the input vector r. 
		 */
		[[nodiscard]] constexpr TVector4 operator+(const TVector4& r) const noexcept { return {x + r.x, y + r.y, z + r.z, w + r.w}; }

		/**
		 * @brief Subtracts another vector from this vector and returns the result as a new vector.
		 *
		 * @param r The vector to subtract from this vector.
		 * @return A new TVector4 that is the difference between this vector and the input vector r.
		 */
		[[nodiscard]] constexpr TVector4 operator-(const TVector4& r) const noexcept { return {x - r.x, y - r.y, z - r.z, w - r.w}; }

		/**
		 * @brief Multiplies this vector by a scalar and returns the result as a new vector.
		 *
		 * @param s The scalar value to multiply each component by.
		 * @return A new TVector4 that is the result of multiplying this vector by the scalar s.
		 */
		[[nodiscard]] constexpr TVector4 operator*(T s) const noexcept { return {x * s, y * s, z * s, w * s}; }

		/**
		 * @brief Divides this vector by a scalar and returns the result as a new vector.
		 *
		 * @param s The scalar value to divide each component by.
		 * @return A new TVector4 that is the result of dividing this vector by the scalar s.
		 */
		[[nodiscard]] constexpr TVector4 operator/(T s) const noexcept { return {x / s, y / s, z / s, w / s}; }

		/**
		 * @brief Checks if this vector is equal to another vector.
		 *
		 * @param r The vector to compare with.
		 * @return true if the vectors are equal, false otherwise.
		 */
		[[nodiscard]] constexpr bool operator==(const TVector4& r) const noexcept { return x == r.x && y == r.y && z == r.z && w == r.w; }

		/**
		 * @brief Checks if this vector is not equal to another vector.
		 *
		 * @param r The vector to compare with.
		 * @return true if the vectors are not equal, false otherwise.
		 */
		[[nodiscard]] constexpr bool operator!=(const TVector4& r) const noexcept { return !(*this == r); }

		/**
		 * @brief Adds another vector to this vector and updates this vector.
		 *
		 * @param r The vector to add to this vector.
		 * @return A reference to this vector after the addition.
		 */
		constexpr TVector4& operator+=(const TVector4& r) noexcept { x += r.x; y += r.y; z += r.z; w += r.w; return *this; }

		/**
		 * @brief Subtracts another vector from this vector and returns the result as a new vector.
		 *
		 * @param r The vector to subtract from this vector.
		 * @return A new TVector4 that is the result of subtracting the input vector r from this vector.
		 */
		constexpr TVector4& operator-=(const TVector4& r) noexcept { x -= r.x; y -= r.y; z -= r.z; w -= r.w; return *this; }

		/**
		 * @brief Multiplies this vector by a scalar and returns the result as a new vector.
		 *
		 * @param s The scalar value to multiply each component by.
		 * @return A new TVector4 that is the result of multiplying this vector by the scalar s.
		 */
		constexpr TVector4& operator*=(T s) noexcept { x *= s; y *= s; z *= s; w *= s; return *this; }

		/**
		 * @brief Divides this vector by a scalar and returns the result as a new vector.
		 *
		 * @param s The scalar value to divide each component by.
		 * @return A new TVector4 that is the result of dividing this vector by the scalar s.
		 */
		constexpr TVector4& operator/=(T s) noexcept { x /= s; y /= s; z /= s; w /= s; return *this; }

		/**
		 * @brief Converts this 4D vector to a 3D vector by discarding the w component.
		 *
		 * @return A TVector3 containing the x, y, and z components of this vector.
		 */
		[[nodiscard]] constexpr operator TVector3<T>() const noexcept { return TVector3<T>(x, y, z); }

		// Allow explicit construction of a Vec3 from a Vec4 without relying on operator cast.
		friend struct TVector3<T>; // Grant access for converting ctor definition below.

		/**
		 * @brief Accesses the i-th component of the vector.
		 * @param i The index of the component (0-based index: 0=x, 1=y, 2=z, 3=w).
		 * @return A reference to the i-th component of the vector.
		 */
		[[nodiscard]] constexpr T& operator[](int i) noexcept { return (&x)[i]; }

		/**
		 * @brief Accesses the i-th component of the vector (const version).
		 * @param i The index of the component (0-based index: 0=x, 1=y, 2=z, 3=w).
		 * @return The value of the i-th component of the vector.
		 */
		[[nodiscard]] constexpr const T& operator[](int i) const noexcept { return (&x)[i]; }
	};

}

// -----------------------------------------------------
