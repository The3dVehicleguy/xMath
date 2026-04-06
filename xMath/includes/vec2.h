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

// -----------------------------------------------------

namespace xMath
{

	/**
	 * @class TVector2
	 * @brief A 2D vector template class for various
	 *
	 * @tparam T The type of the vector components (e.g., float, double, int).
	 */
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

		/**
		 * @brief Default constructor. Initializes the vector to zero.
		 */
		constexpr TVector2() noexcept = default;

		/**
		 * @brief Constructor that initializes both components to the same value.
		 *
		 * @param s The value to set both components to.
	     */
		constexpr explicit TVector2(T s) noexcept : x(s), y(s) {
		}

		/**
		 * @brief Constructor that initializes the vector with specified components.
		 *
		 * @param _x The value to set the x component.
		 * @param _y The value to set the y component.
		 */
		constexpr TVector2(T _x, T _y) noexcept : x(_x), y(_y) {
		}

		/**
		 * @brief Copy constructor.
		 *
		 * @param vector The vector to copy from.
		 */
		TVector2(const TVector2 &vector) = default;

		~TVector2() = default;

		/**
		 * @brief Addition operator.
		 *
		 * @param r The vector to add.
		 * @return The result of the addition.
		 */
		[[nodiscard]] constexpr TVector2 operator+(const TVector2& r) const noexcept { return {x + r.x, y + r.y}; }

		/**
		 * @brief Subtraction operator.
		 *
		 * @param r The vector to subtract.
		 * @return The result of the subtraction.
		 */
		[[nodiscard]] constexpr TVector2 operator-(const TVector2& r) const noexcept { return {x - r.x, y - r.y}; }

		//[[nodiscard]] constexpr TVector2 operator*(T s) const noexcept { return {x * s, y * s}; }

		//[[nodiscard]] constexpr TVector2 operator/(T s) const noexcept { return {x / s, y / s}; }

		/**
		 * @brief Negation operator.
		 *
		 * @return The negated vector.
		 */
		TVector2 operator-() const { return TVector2(-x, -y); }

		/**
		 * @brief Division operator.
		 *
		 * @param rhs The vector to divide by.
		 * @return The result of the division.
		 */
		TVector2 operator/(const TVector2& rhs) const { return TVector2(x / rhs.x, y / rhs.y); }

		/**
		 * @brief Division operator.
		 *
		 * @param rhs The scalar value to divide by.
		 * @return The result of the division.
		 */
		TVector2 operator/(const float rhs) const { return TVector2(x / rhs, y / rhs); }

		/**
		 * @brief Multiplication operator.
		 *
		 * @param value The scalar value to multiply by.
		 * @return The result of the multiplication.
		 */
		TVector2 operator*(const float value) const { return TVector2(x * value, y * value); }

		/**
		 * @brief Component-wise multiplication operator.
		 *
		 * @param b The vector to multiply with.
		 * @return The result of the component-wise multiplication.
		 */
		TVector2 operator*(const TVector2 &b) const { return TVector2(x * b.x, y * b.y); }

		/**
		 * @brief Equality operator.
		 *
		 * @param r The vector to compare with.
		 * @return True if the vectors are equal, false otherwise.
		 */
		[[nodiscard]] constexpr bool operator==(const TVector2& r) const noexcept { return x == r.x && y == r.y; }

		/**
		 * @brief Inequality operator.
		 *
		 * @param r The vector to compare with.
		 * @return True if the vectors are not equal, false otherwise.
		 */
		[[nodiscard]] constexpr bool operator!=(const TVector2& r) const noexcept { return !(*this == r); }

		/**
		 * @brief Subtraction assignment operator.
		 *
		 * @param rhs The vector to subtract.
		 */
		void operator-=(const TVector2& rhs) { x -= rhs.x; y -= rhs.y; }

		/**
		 * @brief Component-wise multiplication assignment operator.
		 *
		 * @param b The vector to multiply with.
		 */
		void operator*=(const TVector2 &b) { x *= b.x; y *= b.y; }

		/**
		 * @brief Division assignment operator.
		 *
		 * @param rhs The vector to divide by.
		 */
		void operator/=(const TVector2& rhs) { x /= rhs.x; y /= rhs.y; }

		/* @brief Normalizes the vector. */
		void Normalize() { float length = Length(); if (length > 0.0001f) { x /= length; y /= length; } else { x = 0.0f; y = 0.0f; } }

		/**
		 * @brief Returns a normalized copy of the vector.
		 *
		 * @return The normalized vector.
		 */
		[[nodiscard]] TVector2 Normalized() const { TVector2 result = *this; result.Normalize(); return result; }

		/**
		 * @brief Addition assignment operator.
		 *
		 * @param r The vector to add.
		 * @return Reference to the updated vector.
		 */
		constexpr TVector2& operator+=(const TVector2& r) noexcept { x += r.x; y += r.y; return *this; }

		//constexpr TVector2& operator-=(const TVector2& r) noexcept { x -= r.x; y -= r.y; return *this; }

		/**
		 * @brief Multiplication assignment operator.
		 *
		 * @param s The scalar value to multiply by.
		 * @return Reference to the updated vector.
		 */
		constexpr TVector2& operator*=(T s) noexcept { x *= s; y *= s; return *this; }

		/**
		 * @brief Division assignment operator.
		 *
		 * @param s The scalar value to divide by.
		 * @return Reference to the updated vector.
		 */
		constexpr TVector2& operator/=(T s) noexcept { x /= s; y /= s; return *this; }

		static const TVector2 ZERO;			 // Zero vector (0, 0)
		static const TVector2 ONE;			 // One vector (1, 1)
		static const TVector2 LEFT;			 // Left unit vector (-1, 0)
		static const TVector2 RIGHT;		 // Right unit vector (1, 0)
		static const TVector2 UP;			 // Up unit vector (0, 1)
		static const TVector2 DOWN;			 // Down unit vector (0, -1)
		static const TVector2 FORWARD;		 // Forward unit vector (0, 0) - not meaningful in 2D but included for completeness
		static const TVector2 BACKWARD;		 // Backward unit vector (0, 0) - not meaningful in 2D but included for completeness
		static const TVector2 VEC2_INFINITY; // Vector with both components set to positive infinity
		static const TVector2 INFINITY_NEG;  // Vector with both components set to negative infinity

		/**
		 * @brief Checks if the vector contains NaN (Not a Number) values.
		 *
		 * @return True if any component is NaN, false otherwise.
		 */
		[[nodiscard]] constexpr bool IsNaN() const noexcept { return x != x || y != y; }

		/**
		 * @brief Returns a vector with the absolute values of the components.
		 *
		 * @return The vector with absolute values.
		 */
		[[nodiscard]] TVector2 Abs() const { return TVector2(abs(x), abs(y)); }

		/**
		 * @brief Returns a vector with the minimum components of two vectors.
		 *
		 * @param a The first vector.
		 * @param b The second vector.
		 * @return The vector with the minimum components.
		 */
		static TVector2 Min(const TVector2 &a, const TVector2 &b) { return TVector2(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y); }

		/**
		 * @brief Returns a vector with the maximum components of two vectors.
		 *
		 * @param a The first vector.
		 * @param b The second vector.
		 * @return The vector with the maximum components.
		 */
		static TVector2 Max(const TVector2 &a, const TVector2 &b) { return TVector2(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y); }

		/**
		 * @brief Subscript operator.
		 *
		 * @param i The index of the component (0 for x, 1 for y).
		 * @return Reference to the component.
		 */
		[[nodiscard]] constexpr T& operator[](int i) noexcept { return i == 0 ? x : y; }

		/**
		 * @brief Const subscript operator.
		 *
		 * @param i The index of the component (0 for x, 1 for y).
		 * @return Const reference to the component.
		 */
		[[nodiscard]] constexpr const T& operator[](int i) const noexcept { return i == 0 ? x : y; }

		/**
		 * @brief Returns a pointer to the underlying data array.
		 *
		 * @return Pointer to the data array.
		 */
		[[nodiscard]] const float* Data() const { return &x; }

		/**
		 * @brief Returns the length (magnitude) of the vector.
		 *
		 * @return The length of the vector.
		 */
		[[nodiscard]] float Length() const { return sqrt(x * x + y * y); }

		/**
		 * @brief Returns the squared length (magnitude) of the vector.
		 *
		 * @return The squared length of the vector.
		 */
		[[nodiscard]] constexpr T Length2() const noexcept { return x * x + y * y; }

		/**
		 * @brief Returns the distance between two vectors.
		 *
		 * @param a The first vector.
		 * @param b The second vector.
		 * @return The distance between the two vectors.
		 */
		static float Distance(const TVector2& a, const TVector2& b) { return (b - a).Length(); }

		/**
		 * @brief Returns the squared distance between two vectors.
		 *
		 * @param a The first vector.
		 * @param b The second vector.
		 * @return The squared distance between the two vectors.
		 */
		static float DistanceSquared(const TVector2& a, const TVector2& b) { return (b - a).Length2(); }
	};

	/* @brief Zero vector (0, 0) */
	template<typename T> 
	inline constexpr TVector2<T> TVector2<T>::ZERO{T(0), T(0)};

	/* @brief One vector (1, 1) */
	template<typename T> 
	inline constexpr TVector2<T> TVector2<T>::ONE{T(1), T(1)};

	/* @brief Left unit vector (-1, 0) */
	template<typename T> 
	inline constexpr TVector2<T> TVector2<T>::LEFT{T(-1), T(0)};

	/* @brief Right unit vector (1, 0) */
	template<typename T> 
	inline constexpr TVector2<T> TVector2<T>::RIGHT{T(1), T(0)};

	/* @brief Up unit vector (0, 1) */
	template<typename T> 
	inline constexpr TVector2<T> TVector2<T>::UP{T(0), T(1)};

	/* @brief Down unit vector (0, -1) */
	template<typename T> 
	inline constexpr TVector2<T> TVector2<T>::DOWN{T(0), T(-1)};

	/* @brief Forward unit vector (0, 0) - not meaningful in 2D but included for completeness */
	template<typename T> 
	inline constexpr TVector2<T> TVector2<T>::FORWARD{T(0), T(0)};

	/* @brief Backward unit vector (0, 0) - not meaningful in 2D but included for completeness */
	template<typename T> 
	inline constexpr TVector2<T> TVector2<T>::BACKWARD{T(0), T(0)};

	/* @brief Vector with both components set to positive infinity */
	template<typename T> 
	inline constexpr TVector2<T> TVector2<T>::VEC2_INFINITY{std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()};

	/* @brief Vector with both components set to negative infinity */
	template<typename T> 
	inline constexpr TVector2<T> TVector2<T>::INFINITY_NEG{-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()};

}

// -----------------------------------------------------
