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
#include <ostream>
#include <xMath/config/math_config.h>
#include <xMath/includes/vector.h>

// -----------------------------------------------------

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
	 // Element names are logical (mRC = row R, column C). The physical
		// declaration order below controls contiguous memory layout returned by
		// any potential Data() accessor. Choose row-major or column-major
		// by defining XMATH_MATRIX_IS_ROW_MAJOR (set by xmath.hpp).
#if XMATH_MATRIX_IS_ROW_MAJOR
		float m00, m01;
		float m10, m11;
#else
		// Column-major contiguous: m00, m10, m01, m11
		float m00, m10;
		float m01, m11;
#endif

		/* @brief Default constructor. 
		 *
		 * Initializes the matrix to the identity matrix.
		 */
		constexpr Mat2() noexcept;

		/**
		 * @brief Constructs a matrix with all elements set to the same value.
		 *
		 * @param s The value to set for all elements.
		 */
		constexpr explicit Mat2(float s) noexcept;

		/**
		 * @brief Constructs a matrix with the specified elements.
		 *
		 * @param _m00 The element at row 0, column 0.
		 * @param _m01 The element at row 0, column 1.
		 * @param _m10 The element at row 1, column 0.
		 * @param _m11 The element at row 1, column 1.
		 */
		constexpr Mat2(float _m00, float _m01, float _m10, float _m11) noexcept;

		/**
		 * @brief Creates a matrix from row vectors.
		 *
		 * This function constructs a 2x2 matrix using the provided row vectors. The first vector
		 * represents the first row of the matrix, and the second vector represents the second row.
		 * 
		 * @param r0 The first row vector.
		 * @param r1 The second row vector.
		 * @return The resulting matrix constructed from the given rows.
		 */
		constexpr static Mat2 FromRows(const TVector2<float>& r0, const TVector2<float>& r1) noexcept;

		/**
		 * @brief Creates a matrix from row vectors.
		 *
		 * @param c0 The first column vector.
		 * @param c1 The second column vector.
		 * @return The resulting matrix constructed from the given columns.
		 */
		constexpr static Mat2 FromColumns(const TVector2<float>& c0, const TVector2<float>& c1) noexcept;

		/**
		 * @brief Returns the identity matrix.
		 *
		 * @return The identity matrix.
		 */
		constexpr static Mat2 Identity() noexcept;

		/**
		 * @brief Returns a zero matrix.
		 *
		 * @return The zero matrix.
		 */
		constexpr static Mat2 Zero() noexcept;

		/**
		 * @brief Creates a rotation matrix.
		 *
		 * @param radians The rotation angle in radians.
		 * @return The resulting rotation matrix.
		 */
		static Mat2 Rotation(float radians) noexcept;

		/**
		 * @brief Creates a scale matrix.
		 *
		 * @param sx The scale factor along the x-axis.
		 * @param sy The scale factor along the y-axis.
		 * @return The resulting scale matrix.
		 */
		constexpr static Mat2 Scale(float sx, float sy) noexcept;

		/**
		 * @brief Creates a scale matrix.
		 *
		 * @param s The scale factors along the x and y axes.
		 * @return The resulting scale matrix.
		 */
		constexpr static Mat2 Scale(const TVector2<float>& s) noexcept;

		/**
		 * @brief Returns a specific row of the matrix.
		 *
		 * @param r The row index (0 or 1).
		 * @return The specified row as a 2D vector.
		 */
		[[nodiscard]] TVector2<float> Row(int r) const noexcept;

		/**
		 * @brief Returns a specific column of the matrix.
		 *
		 * @param c The column index (0 or 1).
		 * @return The specified column as a 2D vector.
		 */
		[[nodiscard]] TVector2<float> Column(int c) const noexcept;

		/**
		 * @brief Accesses a matrix element by row and column.
		 *
		 * @param r The row index (0 or 1).
		 * @param c The column index (0 or 1).
		 * @return A reference to the matrix element at the specified row and column.
		 */
		constexpr float& operator()(int r, int c) noexcept;

		/**
		 * @brief Accesses a matrix element by row and column.
		 *
		 * @param r The row index (0 or 1).
		 * @param c The column index (0 or 1).
		 * @return A reference to the matrix element at the specified row and column.
		 */
		constexpr const float& operator()(int r, int c) const noexcept;

		/**
		 * @brief Adds another matrix to this matrix.
		 *
		 * @param rhs The matrix to add.
		 * @return The resulting matrix after addition.
		 */
		constexpr Mat2 operator+(const Mat2& rhs) const noexcept;

		/**
		 * @brief Subtracts another matrix from this matrix.
		 *
		 * @param rhs The matrix to subtract.
		 * @return The resulting matrix after subtraction.
		 */
		constexpr Mat2 operator-(const Mat2& rhs) const noexcept;

		/**
		 * @brief Multiplies the matrix by a scalar.
		 *
		 * @param s The scalar value.
		 * @return The resulting matrix after multiplication.
		 */
		constexpr Mat2 operator*(float s) const noexcept;

		/**
		 * @brief Multiplies a scalar by a matrix.
		 *
		 * @param s The scalar value.
		 * @param m The matrix to multiply.
		 * @return The resulting matrix after multiplication.
		 */
		friend constexpr Mat2 operator*(float s, const Mat2& m) noexcept { return m * s; }

		/**
		 * @brief Adds another matrix to this matrix.
		 *
		 * @param r The matrix to add.
		 * @return A reference to this matrix after addition.
		 */
		constexpr Mat2& operator+=(const Mat2& r) noexcept;

		/**
		 * @brief Subtracts another matrix from this matrix.
		 *
		 * @param r The matrix to subtract.
		 * @return A reference to this matrix after subtraction.
		 */
		constexpr Mat2& operator-=(const Mat2& r) noexcept;

		/**
		 * @brief Multiplies the matrix by a scalar.
		 *
		 * @param s The scalar value.
		 * @return A reference to this matrix after multiplication.
		 */
		constexpr Mat2& operator*=(float s) noexcept;

		/**
		 * @brief Multiplies the matrix by another matrix.
		 *
		 * @param r The matrix to multiply with.
		 * @return The resulting matrix after multiplication.
		 */
		constexpr Mat2 operator*(const Mat2& r) const noexcept;

		/**
		 * @brief Multiplies the matrix by another matrix.
		 *
		 * @param r The matrix to multiply with.
		 * @return The resulting matrix after multiplication.
		 */
		constexpr Mat2& operator*=(const Mat2& r) noexcept;

		/**
		 * @brief Multiplies the matrix by a 2D vector.
		 *
		 * @param v The vector to multiply.
		 * @return The resulting vector after multiplication.
		 */
		TVector2<float> operator*(const TVector2<float>& v) const noexcept;

		/**
		 * @brief Calculates the trace of the matrix.
		 *
		 * @return The trace of the matrix.
		 */
		[[nodiscard]] constexpr float Trace() const noexcept;

		/**
		 * @brief Calculates the determinant of the matrix.
		 *
		 * @return The determinant of the matrix.
		 */
		[[nodiscard]] constexpr float Determinant() const noexcept;

		/**
		 * @brief Returns the transpose of the matrix.
		 *
		 * @return The transposed matrix.
		 */
		[[nodiscard]] constexpr Mat2 Transposed() const noexcept;

		/**
		 * @brief Inverts the matrix.
		 *
		 * @param eps The tolerance for determining if the matrix is invertible. Defaults to 1e-6f.
		 * @return The inverted matrix if invertible, otherwise a matrix with undefined values.
		 */
		[[nodiscard]] Mat2 Inversed(float eps = 1e-6f) const noexcept;

		/**
		 * @brief Attempts to invert the matrix.
		 *
		 * @param out The matrix to store the result if inversion is successful.
		 * @param eps The tolerance for determining if the matrix is invertible. Defaults to 1e-6f.
		 * @return true if the matrix was successfully inverted, false otherwise.
		 */
		bool TryInverse(Mat2& out, float eps = 1e-6f) const noexcept;

		/**
		 * @brief compares two matrices for equality
		 *
		 * @param r matrix to compare with
		 * @return true if the matrices are equal, false otherwise
		 */
		constexpr bool operator==(const Mat2& r) const noexcept;

		/**
		 * @brief compares two matrices for inequality
		 *
		 * @param r matrix to compare with
		 * @return true if the matrices are not equal, false otherwise
		 */
		constexpr bool operator!=(const Mat2& r) const noexcept;

		/**
		 * @brief compares two matrices for approximate equality using an element-wise epsilon comparison
		 *
		 * @param a The first matrix to compare.
		 * @param b The second matrix to compare.
		 * @param eps The tolerance for element-wise comparison. Defaults to 1e-6f.
		 * @return true if all corresponding elements of the matrices are approximately equal within the given epsilon, false otherwise.
		 */
		static bool ApproxEqual(const Mat2 &a, const Mat2 &b, float eps = 1e-6f) noexcept;
	};

	// Stream operator for debugging
	XMATH_API std::ostream &operator<<(std::ostream &os, const Mat2 &m);

}

// -----------------------------------------------------
