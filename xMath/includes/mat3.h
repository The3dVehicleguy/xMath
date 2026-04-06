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
#include <ostream>
#include <xMath/config/math_config.h>
#include <xMath/includes/vector.h>

// -----------------------------------------------------

namespace xMath
{
	/**
	 * @brief Fast 3x3 single-precision matrix (row-major) for 3D linear transforms (rotation/scale/skew).
	 */
	class XMATH_API Mat3
	{
	public:
		// Element names are logical (mRC = row R, column C). Declaration order
		// controls contiguous memory layout for Data() compatibility.
#if XMATH_MATRIX_IS_ROW_MAJOR
		float m00, m01, m02,
			  m10, m11, m12,
			  m20, m21, m22;
#else
		// Column-major contiguous: column0 then column1 then column2
		float m00, m10, m20,
			  m01, m11, m21,
			  m02, m12, m22;
#endif

		/**
		 * @brief 3D vector type used for rows and columns of the matrix
		 */
		typedef TVector3<float> Vec3f;

		/**
		 * @brief creates a default matrix (identity matrix)
		 */
		constexpr Mat3() noexcept;

		/**
		 * @brief creates a matrix with all elements set to the same value
		 *
		 * @param s value to set all elements to
		 */
		constexpr explicit Mat3(float s) noexcept;

		/**
		 * @brief creates a matrix from individual elements
		 *
		 * @param _m00 element at row 0, column 0
		 * @param _m01 element at row 0, column 1
		 * @param _m02 element at row 0, column 2
		 * @param _m10 element at row 1, column 0
		 * @param _m11 element at row 1, column 1
		 * @param _m12 element at row 1, column 2
		 * @param _m20 element at row 2, column 0
		 * @param _m21 element at row 2, column 1
		 * @param _m22 element at row 2, column 2
		 */
		constexpr Mat3(float _m00, float _m01, float _m02, float _m10, float _m11, float _m12, float _m20, float _m21, float _m22) noexcept;

		/**
		 * @brief creates a matrix from row vectors
		 *
		 * @param r0 first row vector
		 * @param r1 second row vector
		 * @param r2 third row vector
		 * @return the resulting matrix
		 */
		constexpr static Mat3 FromRows(const Vec3f& r0, const Vec3f& r1, const Vec3f& r2) noexcept;

		/**
		 * @brief creates a matrix from column vectors
		 *
		 * @param c0 first column vector
		 * @param c1 second column vector
		 * @param c2 third column vector
		 * @return the resulting matrix
		 */
		constexpr static Mat3 FromColumns(const Vec3f& c0, const Vec3f& c1, const Vec3f& c2) noexcept;

		/**
		 * @brief creates an identity matrix
		 * @return the resulting identity matrix
		 */
		constexpr static Mat3 Identity() noexcept;

		/**
		 * @brief creates a zero matrix
		 *
		 * @return the resulting zero matrix
		 */
		constexpr static Mat3 Zero() noexcept;

		/**
		 * @brief creates a scale matrix from individual scale factors
		 *
		 * @param sx scale factor along the X axis
		 * @param sy scale factor along the Y axis
		 * @param sz scale factor along the Z axis
		 * @return the resulting scale matrix
		 */
		constexpr static Mat3 Scale(float sx, float sy, float sz) noexcept;

		/**
		 * @brief creates a scale matrix from a vector
		 *
		 * @param s scale vector
		 * @return the resulting scale matrix
		 */
		constexpr static Mat3 Scale(const Vec3f& s) noexcept;

		/**
		 * @brief creates a rotation matrix around the X axis
		 *
		 * @param r angle of rotation in radians
		 * @return the resulting rotation matrix
		 */
		static Mat3 RotationX(float r) noexcept;

		/**
		 * @brief creates a rotation matrix around the Y axis
		 *
		 * @param r angle of rotation in radians
		 * @return the resulting rotation matrix
		 */
		static Mat3 RotationY(float r) noexcept;

		/**
		 * @brief creates a rotation matrix around the X axis
		 *
		 * @param r angle of rotation in radians
		 * @return the resulting rotation matrix
		 */
		static Mat3 RotationZ(float r) noexcept;

		/**
		 * @brief creates a rotation matrix around an arbitrary axis
		 *
		 * @param axis axis of rotation
		 * @param angle angle of rotation in radians
		 * @return the resulting rotation matrix
		 */
		static Mat3 RotationAxisAngle(const Vec3f& axis, float angle) noexcept;

		/**
		 * @brief retrieves a row of the matrix
		 *
		 * @param r row index
		 * @return the specified row as a vector
		 */
		[[nodiscard]] constexpr Vec3f Row(int r) const noexcept;

		/**
		 * @brief retrieves a column of the matrix
		 *
		 * @param c column index
		 * @return the specified column as a vector
		 */
		[[nodiscard]] constexpr Vec3f Column(int c) const noexcept;

		/**
		 * @brief accesses an element of the matrix
		 *
		 * @param r row index
		 * @param c column index
		 * @return reference to the element at the specified row and column
		 */
		constexpr float& operator()(int r, int c) noexcept;

		/**
		 * @brief accesses an element of the matrix
		 *
		 * @param r row index
		 * @param c column index
		 * @return reference to the element at the specified row and column
		 */
		constexpr const float& operator()(int r, int c) const noexcept;

		/**
		 * @brief adds another matrix to this matrix
		 *
		 * @param r matrix to add
		 * @return the resulting matrix
		 */
		constexpr Mat3 operator+(const Mat3& r) const noexcept;

		/**
		 * @brief subtracts another matrix from this matrix
		 *
		 * @param r matrix to subtract
		 * @return the resulting matrix
		 */
		constexpr Mat3 operator-(const Mat3& r) const noexcept;

		/**
		 * @brief multiplies the matrix by a scalar
		 *
		 * @param s scalar to multiply with
		 * @return the resulting matrix
		 */
		constexpr Mat3 operator*(float s) const noexcept;

		/**
		 * @brief multiplies a scalar by a matrix
		 *
		 * @param s scalar to multiply with
		 * @param m matrix to multiply
		 * @return the resulting matrix
		 */
		friend constexpr Mat3 operator*(float s, const Mat3& m) noexcept { return m * s; }

		/**
		 * @brief adds another matrix to this matrix
		 *
		 * @param r matrix to add
		 * @return the resulting matrix
		 */
		constexpr Mat3& operator+=(const Mat3& r) noexcept;

		/**
		 * @brief subtracts another matrix from this matrix
		 *
		 * @param r matrix to subtract
		 * @return the resulting matrix
		 */
		constexpr Mat3& operator-=(const Mat3& r) noexcept;

		/**
		 * @brief multiplies the matrix by a scalar
		 *
		 * @param s scalar to multiply with
		 * @return the resulting matrix
		 */
		constexpr Mat3& operator*=(float s) noexcept;

		/**
		 * @brief multiplies the matrix by another matrix
		 *
		 * @param r matrix to multiply with
		 * @return the resulting matrix
		 */
		constexpr Mat3 operator*(const Mat3& r) const noexcept;

		/**
		 * @brief multiplies the matrix by another matrix
		 *
		 * @param r matrix to multiply with
		 * @return the resulting matrix
		 */
		constexpr Mat3& operator*=(const Mat3& r) noexcept;

		/**
		 * @brief multiplies the matrix by a vector
		 *
		 * @param v vector to multiply with
		 * @return the resulting vector
		 */
		constexpr Vec3f operator*(const Vec3f& v) const noexcept;

		/**
		 * @brief calculates the trace of the matrix (sum of diagonal elements)
		 *
		 * @return the trace of the matrix
		 */
		[[nodiscard]] constexpr float Trace() const noexcept;

		/**
		 * @brief calculates the determinant of the matrix
		 *
		 * @return the determinant of the matrix
		 */
		[[nodiscard]] constexpr float Determinant() const noexcept;

		/**
		 * @brief transposes the matrix (rows become columns and vice versa) 
		 *
		 * @return the transposed matrix
		 */
		[[nodiscard]] constexpr Mat3 Transposed() const noexcept;

		/**
		 * @brief attempts to invert the matrix
		 *
		 * @param eps tolerance for element-wise comparison (default: 1e-6)
		 * @return the inverted matrix if successful, undefined behavior otherwise
		 */
		[[nodiscard]] Mat3 Inversed(float eps = 1e-6f) const noexcept;

		/**
		 * @brief attempts to invert the matrix
		 *
		 * @param out matrix to store the result
		 * @param eps tolerance for element-wise comparison (default: 1e-6)
		 * @return true if the matrix was successfully inverted, false otherwise
		 */
		bool TryInverse(Mat3& out, float eps = 1e-6f) const noexcept;

		/**
		 * @brief Orthonormalizes the given matrix using the Gram-Schmidt process
		 *
		 * @param m matrix to orthonormalize
		 * @return the orthonormalized matrix
		 */
		static Mat3 Orthonormalize(const Mat3 &m) noexcept;

		/**
		 * @brief compares two matrices for equality
		 *
		 * @param r matrix to compare with
		 * @return true if the matrices are equal, false otherwise
		 */
		constexpr bool operator==(const Mat3& r) const noexcept;

		/**
		 * @brief compares two matrices for inequality
		 *
		 * @param r matrix to compare with
		 * @return true if the matrices are not equal, false otherwise
		 */
		constexpr bool operator!=(const Mat3& r) const noexcept;

		/**
		 * @brief compares two matrices for approximate equality within a specified tolerance. 
		 *
		 * @param a matrix a
		 * @param b matrix b
		 * @param eps tolerance for element-wise comparison (default: 1e-6)
		 * @return true if all corresponding elements of a and b are within eps of each other, false otherwise
		 */
		static bool ApproxEqual(const Mat3& a, const Mat3& b, float eps = 1e-6f) noexcept;
	};

	/**
	 * @brief Stream operator for debugging
	 *
	 * @param os output stream to write to 
	 * @param m matrix to output 
	 * @return the output stream with the matrix formatted as:
	 */
	XMATH_API std::ostream &operator<<(std::ostream &os, const Mat3 &m);

}

// -----------------------------------------------------
