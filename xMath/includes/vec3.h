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

// -----------------------------------------------------

namespace xMath
{

	template<typename T> struct TVector4;
	template<typename T> struct TVector2;

	/**
	 * @class TVector3
	 * @brief A 3D vector template class for various mathematical operations.
	 * @tparam T The type of the vector components (e.g., float, double, int).
	 */
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

		/**
		 * @brief Default constructor. Initializes all components to zero.
		 */
		constexpr TVector3() noexcept = default;

		//constexpr TVector3() noexcept : x(0), y(0), z(0) {}

		/**
		 * @brief Constructor that initializes all components to the same value.
		 * @param s The value to set for all components.
		 */
		constexpr explicit TVector3(T s) noexcept : x(s), y(s), z(s) {}

		/**
		 * @brief Constructor that initializes each component to a specific value.
		 * @param _x The value to set for the x component.
		 * @param _y The value to set for the y component.
		 * @param _z The value to set for the z component.
		 */
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

		/**
		 * @brief Addition operator.
		 * @param r The vector to add.
		 * @return The result of the addition.
		 */
		[[nodiscard]] constexpr TVector3 operator+(const TVector3& r) const noexcept { return {x + r.x, y + r.y, z + r.z}; }

		/**
		 * @brief Subtraction operator.
		 * @param r The vector to subtract.
		 * @return The result of the subtraction.
		 */
		[[nodiscard]] constexpr TVector3 operator-(const TVector3& r) const noexcept { return {x - r.x, y - r.y, z - r.z}; }

		/**
		 * @brief Multiplication operator (scalar).
		 * @param s The scalar value to multiply with.
		 * @return The result of the multiplication.
		 */
		[[nodiscard]] constexpr TVector3 operator*(T s) const noexcept { return {x * s, y * s, z * s}; }

		/**
		 * @brief Division operator (scalar).
		 * @param s The scalar value to divide by.
		 * @return The result of the division.
		 */
		[[nodiscard]] constexpr TVector3 operator/(T s) const noexcept { return {x / s, y / s, z / s}; }

		/**
		 * @brief Equality operator.
		 * @param r The vector to compare with.
		 * @return True if the vectors are equal, false otherwise.
		 */
		[[nodiscard]] constexpr bool operator==(const TVector3& r) const noexcept { return x == r.x && y == r.y && z == r.z; }

		/**
		 * @brief Inequality operator.
		 * @param r The vector to compare with.
		 * @return True if the vectors are not equal, false otherwise.
		 */
		[[nodiscard]] constexpr bool operator!=(const TVector3& r) const noexcept { return !(*this == r); }

		/**
		 * @brief Negation operator.
		 * @return The negated vector.
		 */
		[[nodiscard]] constexpr TVector3 operator-() const noexcept { return TVector3{-x, -y, -z}; }

		/**
		 * @brief Addition assignment operator.
		 * @param r The vector to add.
		 * @return Reference to the updated vector.
		 */
		constexpr TVector3& operator+=(const TVector3& r) noexcept { x += r.x; y += r.y; z += r.z; return *this; }

		/**
		 * @brief Subtraction assignment operator.
		 * @param r The vector to subtract.
		 * @return Reference to the updated vector.
		 */
		constexpr TVector3& operator-=(const TVector3& r) noexcept { x -= r.x; y -= r.y; z -= r.z; return *this; }

		/**
		 * @brief Multiplication assignment operator (scalar).
		 * @param s The scalar value to multiply with.
		 * @return Reference to the updated vector.
		 */
		constexpr TVector3& operator*=(T s) noexcept { x *= s; y *= s; z *= s; return *this; }

		/**
		 * @brief Division assignment operator (scalar).
		 * @param s The scalar value to divide by.
		 * @return Reference to the updated vector.
		 */
		constexpr TVector3& operator/=(T s) noexcept { x /= s; y /= s; z /= s; return *this; }

		//TVector3& operator*(float scalar) const { return TVector3(x * scalar, y * scalar, z * scalar); }

		/**
		 * @brief Subscript operator.
		 * @param i The index of the component (0 for x, 1 for y, 2 for z).
		 * @return Reference to the component at the specified index.
		 */
		[[nodiscard]] constexpr T& operator[](int i) noexcept { return (&x)[i]; }

		/**
		 * @brief Subscript operator (const).
		 * @param i The index of the component (0 for x, 1 for y, 2 for z).
		 * @return Const reference to the component at the specified index.
		 */
		[[nodiscard]] constexpr const T& operator[](int i) const noexcept { return (&x)[i]; }

		/**
		 * @brief Zero vector.
		 * @tparam T The type of the vector components.
		 */
		template<typename T>
		static inline constexpr TVector3<T> ZERO = TVector3<T>(T(0), T(0), T(0));

		/**
		 * @brief One vector.
		 * @tparam T The type of the vector components.
		 */
		template<typename T>
		static inline constexpr TVector3<T> ONE = TVector3(T(1), T(1), T(1));

		/**
		 * @brief Left vector.
		 * @tparam T The type of the vector components.
		 */
		template<typename T>
		static inline constexpr TVector3<T> LEFT = TVector3(T(-1), T(0), T(0));

		/**
		 * @brief Right vector.
		 * @tparam T The type of the vector components.
		 */
		template<typename T>
		static inline constexpr TVector3<T> RIGHT = TVector3(T(1), T(0), T(0));

		/**
		 * @brief Up vector.
		 * @tparam T The type of the vector components.
		 */
		template<typename T>
		static inline constexpr TVector3<T> UP = TVector3(T(0), T(1), T(0));

		/**
		 * @brief Down vector.
		 * @tparam T The type of the vector components.
		 */
		template<typename T>
		static inline constexpr TVector3<T> DOWN = TVector3(T(0), T(-1), T(0));

		/**
		 * @brief Forward vector.
		 * @tparam T The type of the vector components.
		 */
		template<typename T>
		static inline constexpr TVector3<T> FORWARD = TVector3(T(0), T(0), T(1));

		/**
		 * @brief Backward vector.
		 * @tparam T The type of the vector components.
		 */
		template<typename T>
		static inline constexpr TVector3<T> BACKWARD = TVector3(T(0), T(0), T(-1));

		/**
		 * @brief Vector with all components set to positive infinity.
		 * @tparam T The type of the vector components.
		 */
		template<typename T>
		static inline constexpr TVector3<T> VEC3_INFINITY = TVector3(std::numeric_limits<T>::infinity(),  std::numeric_limits<T>::infinity(),  std::numeric_limits<T>::infinity());

		/**
		 * @brief Vector with all components set to negative infinity.
		 * @tparam T The type of the vector components.
		 */
		template<typename T>
		static inline constexpr TVector3<T> INFINITY_NEG = TVector3(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity());

		/**
		 * @brief Checks if any component of the vector is NaN (Not a Number).
		 * @return True if any component is NaN, false otherwise.
		 */
		[[nodiscard]] constexpr bool IsNaN() const noexcept { return x != x || y != y || z != z; }

		/**
		 * @brief Returns a vector with the absolute values of each component.
		 * @return A vector with the absolute values of each component.
		 */
		[[nodiscard]] TVector3 Abs() const { return TVector3(abs(x), abs(y), abs(z)); }
	};

	/**
	 * @brief Multiplies a scalar with a vector.
	 * @tparam T The type of the vector components.
	 * @param s The scalar value to multiply with the vector.
	 * @param v The vector to be multiplied.
	 * @return A new vector resulting from the multiplication of the scalar and the vector.
	 */
	template<typename T>
	[[nodiscard]] constexpr TVector3<T> operator*(T s, const TVector3<T>& v) noexcept
	{
		return TVector3<T>(v.x * s, v.y * s, v.z * s);
	}

}

// -----------------------------------------------------
