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
* mat3.h
* -------------------------------------------------------
* Created: 12/8/2025
* -------------------------------------------------------
*/
#pragma once
#include <math_config.h>
#include <ostream>
#include <xMath/includes/vector.h>

/// -----------------------------------------------------

namespace xMath
{
	/**
	 * @brief Fast 3x3 single-precision matrix (row-major) for 3D linear transforms (rotation/scale/skew).
	 *
	 * Layout (row-major):
	 * [ m00 m01 m02 ]
	 * [ m10 m11 m12 ]
	 * [ m20 m21 m22 ]
	 */
	class XMATH_API Mat3
	{
	public:
		float m00, m01, m02,
			  m10, m11, m12,
			  m20, m21, m22;

		using Vec3f = TVector3<float>;

		// -------------------------------------------------
		// Constructors
		constexpr Mat3() noexcept;

		constexpr explicit Mat3(float s) noexcept;

		constexpr Mat3(float _m00, float _m01, float _m02, float _m10, float _m11, float _m12, float _m20, float _m21, float _m22) noexcept;

		// From rows / columns
		constexpr static Mat3 FromRows(const Vec3f& r0, const Vec3f& r1, const Vec3f& r2) noexcept;
        constexpr static Mat3 FromColumns(const Vec3f& c0, const Vec3f& c1, const Vec3f& c2) noexcept;

        // Identity / Zero
		constexpr static Mat3 Identity() noexcept;
        constexpr static Mat3 Zero() noexcept;

        // Scale
		constexpr static Mat3 Scale(float sx, float sy, float sz) noexcept;
        constexpr static Mat3 Scale(const Vec3f& s) noexcept;

        // Rotation about principal axes (radians)
		static Mat3 RotationX(float r) noexcept;
        static Mat3 RotationY(float r) noexcept;
        static Mat3 RotationZ(float r) noexcept;
        static Mat3 RotationAxisAngle(const Vec3f& axis, float angle) noexcept;

        // Accessors
		[[nodiscard]] constexpr Vec3f Row(int r) const noexcept;
        [[nodiscard]] constexpr Vec3f Column(int c) const noexcept;

        constexpr float& operator()(int r, int c) noexcept;
        constexpr const float& operator()(int r, int c) const noexcept;

        // -------------------------------------------------
		// Arithmetic
		constexpr Mat3 operator+(const Mat3& r) const noexcept;
        constexpr Mat3 operator-(const Mat3& r) const noexcept;
        constexpr Mat3 operator*(float s) const noexcept;
        friend constexpr Mat3 operator*(float s, const Mat3& m) noexcept { return m * s; }

		constexpr Mat3& operator+=(const Mat3& r) noexcept;
        constexpr Mat3& operator-=(const Mat3& r) noexcept;
        constexpr Mat3& operator*=(float s) noexcept;

        // Matrix multiply
		constexpr Mat3 operator*(const Mat3& r) const noexcept;
        constexpr Mat3& operator*=(const Mat3& r) noexcept;

        // Vector multiply (column-vector convention)
		constexpr Vec3f operator*(const Vec3f& v) const noexcept;

	    // Properties and helpers
		[[nodiscard]] constexpr float Trace() const noexcept;
        [[nodiscard]] constexpr float Determinant() const noexcept;
        [[nodiscard]] constexpr Mat3 Transposed() const noexcept;

        [[nodiscard]] Mat3 Inversed(float eps = 1e-6f) const noexcept;

        bool TryInverse(Mat3& out, float eps = 1e-6f) const noexcept;

        // Orthonormalize (Gram-Schmidt) to build a clean rotation matrix
        static Mat3 Orthonormalize(const Mat3 &m) noexcept;

        // Comparisons
		constexpr bool operator==(const Mat3& r) const noexcept;
        constexpr bool operator!=(const Mat3& r) const noexcept;

        static bool ApproxEqual(const Mat3& a, const Mat3& b, float eps = 1e-6f) noexcept;
    };

    // Stream operator for debugging
    XMATH_API std::ostream &operator<<(std::ostream &os, const Mat3 &m);

}

/// -----------------------------------------------------
