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
* mat2.h
* -------------------------------------------------------
* Created: 12/8/2025
* -------------------------------------------------------
*/
#pragma once
#include <cmath>
#include <math_config.h>
#include <ostream>
#include <xMath/includes/vector.h>

/// -----------------------------------------------------

namespace xMath
{
	/**
	 * @brief Fast 2x2 single-precision matrix (row-major) for 2D transforms and linear algebra.
	 *
	 * Storage layout (row-major):
	 * [ m00 m01 ]
	 * [ m10 m11 ]
	 */
	class XMATH_API Mat2
	{
	public:
        float m00, m01;
        float m10, m11;

		/// -------------------------------------------------

	    // Constructors
		constexpr Mat2() noexcept;
		constexpr explicit Mat2(float s) noexcept;
		constexpr Mat2(float _m00, float _m01, float _m10, float _m11) noexcept;

		// From rows / columns
		constexpr static Mat2 FromRows(const TVector2<float>& r0, const TVector2<float>& r1) noexcept;
        constexpr static Mat2 FromColumns(const TVector2<float>& c0, const TVector2<float>& c1) noexcept;

        // Identity / Zero
		constexpr static Mat2 Identity() noexcept;
        constexpr static Mat2 Zero() noexcept;

        // Rotation (radians)
        static Mat2 Rotation(float radians) noexcept;

        // Scaling
		constexpr static Mat2 Scale(float sx, float sy) noexcept;
        constexpr static Mat2 Scale(const TVector2<float>& s) noexcept;

        // Accessors
        [[nodiscard]] TVector2<float> Row(int r) const noexcept;
        [[nodiscard]] TVector2<float> Column(int c) const noexcept;

        // Indexing helpers
		constexpr float& operator()(int r, int c) noexcept;
        constexpr const float& operator()(int r, int c) const noexcept;

        /// -------------------------------------------------

	    // Arithmetic
		constexpr Mat2 operator+(const Mat2& rhs) const noexcept;
        constexpr Mat2 operator-(const Mat2& rhs) const noexcept;
        constexpr Mat2 operator*(float s) const noexcept;
        friend constexpr Mat2 operator*(float s, const Mat2& m) noexcept { return m * s; }

		constexpr Mat2& operator+=(const Mat2& r) noexcept;
        constexpr Mat2& operator-=(const Mat2& r) noexcept;
        constexpr Mat2& operator*=(float s) noexcept;

        // Matrix multiply
		constexpr Mat2 operator*(const Mat2& r) const noexcept;
        constexpr Mat2& operator*=(const Mat2& r) noexcept;

        // Vector multiply (column-vector convention)
		TVector2<float> operator*(const TVector2<float>& v) const noexcept;

        /// -------------------------------------------------

		// Properties and helpers
        [[nodiscard]] constexpr float Trace() const noexcept;
        [[nodiscard]] constexpr float Determinant() const noexcept;
        [[nodiscard]] constexpr Mat2 Transposed() const noexcept;

        [[nodiscard]] Mat2 Inversed(float eps = 1e-6f) const noexcept;

        bool TryInverse(Mat2& out, float eps = 1e-6f) const noexcept;

        // Comparisons
		constexpr bool operator==(const Mat2& r) const noexcept;
        constexpr bool operator!=(const Mat2& r) const noexcept;

        static bool ApproxEqual(const Mat2 &a, const Mat2 &b, float eps = 1e-6f) noexcept;
    };

    // Stream operator for debugging
    XMATH_API std::ostream &operator<<(std::ostream &os, const Mat2 &m);

}

/// -----------------------------------------------------
