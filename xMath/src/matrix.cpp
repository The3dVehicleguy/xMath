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
* matrix.cpp
* -------------------------------------------------------
* Created: 15/7/2025
* -------------------
*/
#include <cmath>
#include <xmath.hpp> // umbrella ensures ordering (renamed)
#include <xMath/includes/math_utils.h>
#include <xMath/includes/matrix.h>
#include <xMath/includes/quat.h>

// Profiling (Tracy) optional: only active if both XMATH_ALLOW_TRACY and TRACY_ENABLE provided by build.
#if defined(XMATH_ALLOW_TRACY) && defined(TRACY_ENABLE)
	#include <tracy/Tracy.hpp>
#else
	#ifndef ZoneScoped
		#define ZoneScoped (void)0
	#endif
#endif

/// -------------------------------------------------------

namespace xMath
{

    // Definition of static identity matrix
    const Matrix Matrix::Identity = Matrix();

    /**
     * @brief Creates a perspective projection matrix for 3D rendering.
     *
     * This function generates a perspective projection matrix that transforms 3D coordinates
     * from view space (camera space) to clip space. The matrix implements a standard
     * perspective projection with a symmetric frustum defined by field of view and aspect ratio.
     *
     * @param aspect The aspect ratio of the viewport (width / height). Must be positive.
     * @param fieldOfView The vertical field of view angle in degrees. Typical values range from 45-90 degrees.
     * @param n The distance to the near clipping plane. Must be positive and less than far plane.
     * @param f The distance to the far clipping plane. Must be positive and greater than near plane.
     *
     * @return Matrix4x4 A 4x4 perspective projection matrix suitable for use in graphics pipelines.
     *
     * @note - The Y-axis is inverted (negative scale) to match common graphics coordinate systems.
     * @note - Objects closer than the near plane or farther than the far plane will be clipped.
     * @warning Ensure near and far planes are positive and near < far to avoid degenerate matrices.
     *
     * @code
     * float aspectRatio = screenWidth / screenHeight;
     * Matrix4x4 projection = Matrix4x4::PerspectiveProjection(aspectRatio, 60.0f, 0.1f, 1000.0f);
     * @endcode
     */
	Mat4 Mat4::PerspectiveProjection(const float aspect, const float fieldOfView, const float n, const float f) noexcept
    {
		const float tanHalfFOV = std::tan(ToRadians(fieldOfView / 2.0f));

        return Mat4({
			{ 1 / (aspect * tanHalfFOV), 0, 0, 0 },
			{ 0, -1 / tanHalfFOV, 0, 0 },
			{ 0, 0, f / (f - n), -f * n / (f - n) },
			{ 0, 0, 1, 0 }
		});
    }

	/**
	 * @brief Creates an orthographic projection matrix for 2D rendering or technical drawing.
	 *
	 * This function generates an orthographic projection matrix that transforms 3D coordinates
	 * from view space to clip space without perspective distortion. Objects maintain their
	 * relative sizes regardless of distance from the camera, making it ideal for 2D rendering,
	 * UI elements, and technical/engineering drawings.
	 *
	 * @param l The left edge of the projection volume (minimum X coordinate).
	 * @param r The right edge of the projection volume (maximum X coordinate). Must be > left.
	 * @param t The top edge of the projection volume (maximum Y coordinate).
	 * @param b The bottom edge of the projection volume (minimum Y coordinate). Must be < top.
	 * @param nearPlane The distance to the near clipping plane. Can be negative.
	 * @param farPlane The distance to the far clipping plane. Must be != nearPlane.
	 *
	 * @return Matrix4x4 A 4x4 orthographic projection matrix suitable for 2D and isometric rendering.
	 *
	 * @note - The coordinate system is right-handed with Y pointing up.
	 * @note - Unlike perspective projection, parallel lines remain parallel after transformation.
	 * @warning Ensure right > left, top > bottom, and farPlane != nearPlane to avoid degenerate matrices.
	 *
	 * @code
	 * // Create orthographic projection for 2D rendering
	 * Matrix4x4 ortho = Matrix4x4::OrthographicProjection(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	 * @endcode
	 */
	Mat4 Mat4::OrthographicProjection(float l, float r, float t, float b, float nearPlane, float farPlane) noexcept
	{
		return Mat4({
			{ 2 / (r - l), 0, 0, -(r + l) / (r - l) },
			{ 0, 2 / (b - t), 0, -(b + t) / (b - t) },
			{ 0, 0, 1 / (farPlane - nearPlane), -nearPlane / (farPlane - nearPlane) },
			{ 0, 0, 0, 1 }
		});
	}

    /**
     * @brief Creates a look-at matrix for camera transformations.
     *
     * This function generates a view matrix that transforms world coordinates
     * into camera space, effectively positioning and orienting the camera in 3D space.
     *
     * @param eye The position of the camera (eye point).
     * @param center The point in space the camera is looking at (target point).
     * @param up The up direction vector for the camera, defining its orientation.
     * @return Matrix4x4 A 4x4 look-at matrix that can be used to transform world coordinates to camera space.
     */
	Mat4 Mat4::LookAt(const Vec3& eye, const Vec3& center, const Vec3& up) noexcept
	{
		/// Right-handed look-at using row-major layout and column-vector math basis
		const Vec3 f = Normalize(center - eye);				/// forward
		const Vec3 s = Normalize(Cross(f, up));	/// right
		const Vec3 u = Cross(s, f);								/// true up

		/// Translate components
        const float tx = -Dot(s, eye); /// Negative dot product for translation
        const float ty = -Dot(u, eye); /// Negative dot product for translation
        const float tz = Dot(f, eye);  /// Positive dot product for translation

		return Mat4({
			{ s.x,  u.x, -f.x, tx },		/// Right vector
			{ s.y,  u.y, -f.y, ty },		/// Up vector
			{ s.z,  u.z, -f.z, tz },		/// Forward vector
			{ 0.0f, 0.0f, 0.0f, 1.0f }	/// Homogeneous coordinate (no translation)
		});
	}

	/**
	 * @brief Creates a 2D rotation matrix around the Z-axis.
	 *
	 * This convenience function creates a 4x4 transformation matrix that represents
	 * a rotation around the Z-axis (out of the screen in a right-handed coordinate system).
	 * This is commonly used for 2D rotations in UI elements, sprites, or 2D games.
	 *
	 * @param degrees The rotation angle in degrees. Positive values rotate counter-clockwise.
	 *
	 * @return Matrix4x4 A 4x4 transformation matrix representing rotation around the Z-axis.
	 *
	 * @note - This function internally creates a quaternion and converts it to a matrix.
	 * @note - For multiple rotations, consider using glm::quat directly for better performance.
	 *
	 * @code
	 * Matrix4x4 rotation = Matrix4x4::Angle(45.0f); // 45° degree rotation
	 * @endcode
	 */
	Mat4 Mat4::Angle(const float degrees) noexcept
    {
        return Quat::EulerDegrees(0, 0, degrees).ToMatrix();
    }

	/**
	 * @brief Creates a 3D rotation matrix from Euler angles in degrees.
	 *
	 * This function creates a 4x4 transformation matrix representing a 3D rotation
	 * defined by Euler angles. The rotation order is YXZ (yaw-pitch-roll), which
	 * is commonly used in games and 3D applications.
	 *
	 * @param eulerDegrees A Vec3 containing the rotation angles in degrees:
	 *                     - x: Pitch (rotation around X-axis)
	 *                     - y: Yaw (rotation around Y-axis)
	 *                     - z: Roll (rotation around Z-axis)
	 *
	 * @return Matrix4x4 A 4x4 transformation matrix representing the combined rotation.
	 *
	 * @note - Rotation order matters. This function uses YXZ order to avoid gimbal lock in common cases.
	 * @note - For smooth interpolation between rotations, use quaternions directly.
	 *
	 * @code
	 * Vec3 rotation(15.0f, 45.0f, 0.0f); // 15° pitch, 45° yaw, 0° roll
	 * Matrix4x4 rotMatrix = Matrix4x4::RotationDegrees(rotation);
	 * @endcode
	 */
	Mat4 Mat4::RotationDegrees(const Vec3& eulerDegrees) noexcept
    {
        return Quat::EulerDegrees(eulerDegrees).ToMatrix();
    }

	/**
	 * @brief Creates a 3D rotation matrix from Euler angles in radians.
	 *
	 * This function creates a 4x4 transformation matrix representing a 3D rotation
	 * defined by Euler angles in radians. This is the radian equivalent of RotationDegrees().
	 *
	 * @param eulerRadians A Vec3 containing the rotation angles in radians:
	 *                     - x: Pitch (rotation around X-axis)
	 *                     - y: Yaw (rotation around Y-axis)
	 *                     - z: Roll (rotation around Z-axis)
	 *
	 * @return Matrix4x4 A 4x4 transformation matrix representing the combined rotation.
	 *
	 * @note - Rotation order is YXZ (yaw-pitch-roll).
	 * @note - Using radians directly can be more efficient when working with mathematical calculations.
	 *
	 * @code
	 * Vec3 rotation(0.262f, 0.785f, 0.0f); // ~15° pitch, ~45° yaw, 0° roll
	 * Matrix4x4 rotMatrix = Matrix4x4::RotationRadians(rotation);
	 * @endcode
	 */
	Mat4 Mat4::RotationRadians(const Vec3 &eulerRadians) noexcept
    {
        return Quat::EulerRadians(eulerRadians).ToMatrix();
    }

	/**
	 * @brief Matrix addition operator.
	 *
	 * Performs element-wise addition of two 4x4 matrices. Each corresponding element
	 * in the matrices is added together to produce the result matrix.
	 *
	 * @param rhs The right-hand side matrix to add to this matrix.
	 *
	 * @return Matrix4x4 A new matrix containing the sum of both matrices.
	 *
	 * @note - This operation is commutative: A + B = B + A.
	 * @note - The original matrices are not modified.
	 *
	 * @example
	 * @code
	 * Matrix4x4 result = matrixA + matrixB;
	 * @endcode
	 */
	Mat4 Mat4::operator+(const Mat4& rhs) const noexcept
	{
		Mat4 result{};

		for (int i = 0; i < 4; i++)
            result.rows[i] = rows[i] + rhs.rows[i];

        return result;
	}

	/**
	 * @brief Matrix subtraction operator.
	 *
	 * Performs element-wise subtraction of two 4x4 matrices. Each element in the
	 * right-hand side matrix is subtracted from the corresponding element in this matrix.
	 *
	 * @param rhs The right-hand side matrix to subtract from this matrix.
	 *
	 * @return Matrix4x4 A new matrix containing the difference (this - rhs).
	 *
	 * @note - This operation is not commutative: A - B ≠ B - A.
	 * @note - The original matrices are not modified.
	 *
	 * @example
	 * @code
	 * Matrix4x4 result = matrixA - matrixB;
	 * @endcode
	 */
	Mat4 Mat4::operator-(const Mat4& rhs) const noexcept
	{
		Mat4 result{};

		for (int i = 0; i < 4; i++)
            result.rows[i] = rows[i] - rhs.rows[i];

        return result;
	}

	/**
	 * @brief Scalar multiplication operator.
	 *
	 * Multiplies every element in the matrix by the given scalar value. This operation
	 * scales the transformation represented by the matrix uniformly.
	 *
	 * @param rhs The scalar value to multiply each matrix element by.
	 *
	 * @return Matrix4x4 A new matrix with all elements scaled by the scalar value.
	 *
	 * @note - This operation preserves the matrix structure while scaling the transformation.
	 * @note - The original matrix is not modified.
	 *
	 * @code
	 * Matrix4x4 scaled = originalMatrix * 2.0f; // Double all transformation components
	 * @endcode
	 */
	Mat4 Mat4::operator*(float rhs) const noexcept
	{
		ZoneScoped;
		Mat4 result{};

		for (int i = 0; i < 4; ++i)
            result.rows[i] = rows[i] * rhs;

        return result;
	}

	/**
	 * @brief Scalar division operator.
	 *
	 * Divides every element in the matrix by the given scalar value. This operation
	 * scales the transformation represented by the matrix by the reciprocal of the divisor.
	 *
	 * @param rhs The scalar value to divide each matrix element by. Must be non-zero.
	 *
	 * @return Matrix4x4 A new matrix with all elements divided by the scalar value.
	 *
	 * @note - This operation is equivalent to multiplying by 1/rhs.
	 * @note - The original matrix is not modified.
	 * @warning Division by zero will result in undefined behavior (infinity/NaN values).
	 *
	 * @code
	 * Matrix4x4 scaled = originalMatrix / 2.0f; // Halve all transformation components
	 * @endcode
	 */
	Mat4 Mat4::operator/(const float rhs) const noexcept
	{
		ZoneScoped;
		Mat4 result{};

		for (int i = 0; i < 4; ++i)
            result.rows[i] = rows[i] / rhs;

        return result;
	}

	/**
	 * @brief Matrix multiplication (Matrix × Matrix).
	 *
	 * Performs standard mathematical matrix multiplication between two 4x4 matrices.
	 * This operation combines two transformations, where the result represents applying
	 * the right-hand side transformation first, then the left-hand side transformation.
	 *
	 * The multiplication follows the standard formula:
	 * result[i][j] = Σ(k=0 to 3) lhs[i][k] * rhs[k][j]
	 *
	 * @param lhs The left-hand side matrix (applied second in transformation order).
	 * @param rhs The right-hand side matrix (applied first in transformation order).
	 *
	 * @return Matrix4x4 The resulting matrix from the multiplication lhs × rhs.
	 *
	 * @note - Matrix multiplication is NOT commutative: A × B ≠ B × A in general.
	 * @note - This function is static and can be called without a matrix instance.
	 * @note - Time complexity: O(64) - constant time for 4x4 matrices.
	 *
	 * @code
	 * Matrix4x4 transform = Matrix4x4::Multiply(projection, view);
	 * // Equivalent to: transform = projection * view (if operator* were defined)
	 * @endcode
	 */
	Mat4 Mat4::Multiply(const Mat4& lhs, const Mat4& rhs) noexcept
	{
		ZoneScoped;
		Mat4 result{};

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.rows[i][j] = 0;

				for (int k = 0; k < 4; k++)
				{
					result.rows[i][j] += lhs.rows[i][k] * rhs.rows[k][j];
				}
			}
		}

		return result;
	}

	/**
	 * @brief Matrix-vector multiplication (Matrix × Vector).
	 *
	 * Transforms a 4D vector by multiplying it with a 4x4 matrix. This operation
	 * applies the transformation represented by the matrix to the vector, which
	 * is fundamental for transforming vertices, points, and directions in 3D space.
	 *
	 * The multiplication follows the standard formula:
	 * result[i] = Σ(j=0 to 3) lhs[i][j] * rhs[j]
	 *
	 * @param lhs The 4x4 transformation matrix.
	 * @param rhs The 4D vector to transform (x, y, z, w components).
	 *
	 * @return Vec4 The transformed vector after applying the matrix transformation.
	 *
	 * @note - For 3D points, use w=1.0f to include translation effects.
	 * @note - For 3D directions/normals, use w=0.0f to exclude translation effects.
	 * @note - This function is static and can be called without a matrix instance.
	 *
	 * @code
	 * Vec4 worldPos = Matrix4x4::Multiply(worldTransform, localPos);
	 * Vec4 clipPos = Matrix4x4::Multiply(projectionMatrix, viewPos);
	 * @endcode
	 */
	Vec4 Mat4::Multiply(const Mat4& lhs, const Vec4& rhs) noexcept
    {
		ZoneScoped;
        Vec4 result{};

        for (int i = 0; i < 4; i++)
        {
            float value = 0;
            for (int j = 0; j < 4; j++)
            {
                value += lhs.rows[i][j] * rhs[j];
            }

            result[i] = value;
        }

        return result;
    }

	/**
	 * @brief Computes the transpose of a 4x4 matrix.
	 *
	 * The transpose of a matrix is obtained by swapping rows and columns, such that
	 * element at position [i][j] becomes element at position [j][i]. For transformation
	 * matrices, the transpose is useful for inverse rotation calculations and converting
	 * between row-major and column-major representations.
	 *
	 * Mathematical definition: transpose(A)[i][j] = A[j][i]
	 *
	 * @param mat The source matrix to transpose.
	 *
	 * @return Matrix4x4 A new matrix that is the transpose of the input matrix.
	 *
	 * @note - For orthogonal matrices (pure rotations), the transpose equals the inverse.
	 * @note - This operation does not modify the input matrix.
	 * @note - Transposing twice returns the original matrix: transpose(transpose(A)) = A.
	 *
	 * @code
	 * Matrix4x4 rotation = Matrix4x4::RotationDegrees(45.0f, Vec3(0, 1, 0));
	 * Matrix4x4 inverse = Matrix4x4::GetTranspose(rotation); // For pure rotations
	 * @endcode
	 */
	Mat4 Mat4::GetTranspose(const Mat4& mat) noexcept
	{
		ZoneScoped;
		Mat4 result{};

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.rows[i][j] = mat.rows[j][i];
			}
		}

		return result;
	}

	/**
	 * @brief Helper function to extract cofactor matrix for determinant calculation.
	 *
	 * This function extracts a (n-1)×(n-1) submatrix from the input matrix by excluding
	 * the specified row and column. This cofactor matrix is used in determinant calculations
	 * and matrix inversion algorithms using cofactor expansion.
	 *
	 * @param mat The source matrix to extract the cofactor from.
	 * @param cofactor Output matrix to store the extracted cofactor (modified by this function).
	 * @param p The row index to exclude from the source matrix (0-based).
	 * @param q The column index to exclude from the source matrix (0-based).
	 * @param n The size of the matrix (should be 4 for Matrix4x4).
	 *
	 * @note - This is a helper function for determinant and inverse calculations.
	 * @note - The output cofactor matrix will be one dimension smaller than the input.
	 */
	void Mat4::GetCofactor(const Mat4 &mat, Mat4 &cofactor, const int32_t p, const int32_t q, const int32_t n) noexcept
	{
		ZoneScoped;
		int32_t i = 0, j = 0;

		for (int row = 0; row < n; row++)
		{
			for (int col = 0; col < n; col++)
			{
				if (row != p && col != q)
				{
					cofactor[i][j++] = mat[row][col];

					/// Row is filled, so increase row index and
					/// reset col index
					if (j == n - 1)
					{
						j = 0;
						i++;
					}
				}
			}
		}
	}

	/**
	 * @brief Recursively calculates the determinant of a matrix using cofactor expansion.
	 *
	 * This function computes the determinant using the recursive cofactor expansion method.
	 * The determinant is a scalar value that indicates if the matrix is invertible (non-zero
	 * determinant) and is fundamental for calculating matrix inverses.
	 *
	 * For a 4×4 matrix, the determinant is calculated as:
	 * det(A) = Σ(i=0 to 3) (-1)^i * A[0][i] * det(Minor[0][i])
	 *
	 * @param mat The matrix to calculate the determinant for.
	 * @param n The size of the matrix (4 for Matrix4x4, decreases in recursive calls).
	 *
	 * @return int The determinant of the matrix.
	 *
	 * @note - Base case: for 1×1 matrix, returns the single element.
	 * @note - A determinant of 0 indicates the matrix is singular (non-invertible).
	 * @note - This function uses recursive calls and may be slower for large matrices.
	 */
	float Mat4::GetDeterminant(const Mat4& mat, const int32_t n) noexcept
	{
		ZoneScoped;
		float determinant = 0.0f;

		if (n == 1)
			return mat[0][0];

		Mat4 temp{};
		int sign = 1;

		/// Iterate for each element of first row
		for (int32_t f = 0; f < n; f++)
		{
			/// Getting Cofactor of A[0][f]
			GetCofactor(mat, temp, 0, f, n);
			determinant += static_cast<float>(sign) * mat[0][f] * GetDeterminant(temp, n - 1);

			/// terms are to be added with alternate sign
			sign = -sign;
		}

		return determinant;
	}

	/**
	 * @brief Calculates the adjoint (adjudicate) matrix.
	 *
	 * The adjoint matrix is the transpose of the cofactor matrix. Each element of the
	 * adjoint matrix is calculated as: adj[j][i] = (-1)^(i+j) * Minor[i][j], where
	 * Minor[i][j] is the determinant of the matrix obtained by deleting row i and column j.
	 *
	 * The adjoint matrix is used in matrix inversion: A^(-1) = adj(A) / det(A)
	 *
	 * @param mat The matrix to calculate the adjoint for.
	 *
	 * @return Matrix4x4 The adjoint matrix.
	 *
	 * @note - The adjoint matrix is also known as the adjudicate matrix.
	 * @note - For a 4×4 matrix, this involves calculating 16 determinants of 3×3 submatrices.
	 */
	Mat4 Mat4::GetAdjoint(const Mat4& mat) noexcept
	{
		ZoneScoped;
		Mat4 adj{};

		/// temp is used to store cofactors of mat[][]
		Mat4 temp{};

        for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				/// Get cofactor of A[i][j]
				GetCofactor(mat, temp, i, j, 4);

				/// sign of adj[j][i] positive if sum of row
				/// and column indexes is even.
				int sign = ((i + j) % 2 == 0) ? 1 : -1;

				/// Interchanging rows and columns to get the
				/// transpose of the cofactor matrix
				adj[j][i] = sign * (GetDeterminant(temp, 4 - 1));
			}
		}

		return adj;
	}

	/**
	 * @brief Calculates the inverse of a 4×4 matrix using an optimized analytical method.
	 *
	 * This function computes the matrix inverse using a direct analytical approach that
	 * is more efficient than the adjoint/determinant method for 4×4 matrices. The inverse
	 * satisfies the property: A × A^(-1) = I (identity matrix).
	 *
	 * The implementation uses an optimized algorithm that directly calculates all elements
	 * of the inverse matrix using determinant ratios and cofactor relationships.
	 *
	 * @param matrix The matrix to invert.
	 *
	 * @return Matrix4x4 The inverse of the input matrix.
	 *
	 * @warning If the input matrix is singular (determinant = 0), the result is undefined
	 *          and may contain infinity or NaN values.
	 * @note - This method is significantly faster than the cofactor expansion method.
	 * @note - The input matrix must be non-singular for a valid result.
	 *
	 * @code
	 * Matrix4x4 original = Matrix4x4::Translation(Vec3(1, 2, 3));
	 * Matrix4x4 inverse = Matrix4x4::GetInverse(original);
	 * Matrix4x4 identity = Matrix4x4::Multiply(original, inverse); // Should be identity
	 * @endcode
	 */
	Mat4 Mat4::GetInverse(const Mat4& matrix) noexcept
	{
        ZoneScoped; /// Enable Tracy profiling for this function

		/// Rows - Extract the elements of the matrix for easier access
		const float n11 = matrix[0][0], n12 = matrix[1][0], n13 = matrix[2][0], n14 = matrix[3][0]; /// First row
        const float n21 = matrix[0][1], n22 = matrix[1][1], n23 = matrix[2][1], n24 = matrix[3][1]; /// Second row
        const float n31 = matrix[0][2], n32 = matrix[1][2], n33 = matrix[2][2], n34 = matrix[3][2]; /// Third row
        const float n41 = matrix[0][3], n42 = matrix[1][3], n43 = matrix[2][3], n44 = matrix[3][3]; /// Fourth row

		/// Columns - Calculate the determinant using the first row and cofactors
		const float t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44; /// First column
		const float t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44; /// Second column
		const float t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44; /// Third column
		const float t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34; /// Fourth column

		/// Calculate the determinant using the first row and cofactors
		const float det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14; /// Determinant calculation
        const float idet = 1.0f / det;                                   /// Inverse of the determinant

		Mat4 ret; /// Result matrix to store the inverse

		/// Calculate the inverse matrix using the cofactors and the determinant
		ret[0][0] = t11 * idet;																												/// First row, first column
		ret[0][1] = (n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44) * idet; /// First row, second column
		ret[0][2] = (n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44) * idet; /// First row, third column
		ret[0][3] = (n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43) * idet; /// First row, fourth column

		/// Calculate the second row
        ret[1][0] = t12 * idet;																												/// Second row, first column
		ret[1][1] = (n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44) * idet; /// Second row, second column
		ret[1][2] = (n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44) * idet; /// Second row, third column
		ret[1][3] = (n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43) * idet; /// Second row, fourth column

		/// Calculate the third row
        ret[2][0] = t13 * idet;																												/// Third row, first column
		ret[2][1] = (n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44) * idet; /// Third row, second column
		ret[2][2] = (n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44) * idet; /// Third row, third column
		ret[2][3] = (n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43) * idet; /// Third row, fourth column

		/// Calculate the fourth row
        ret[3][0] = t14 * idet;																												/// Fourth row, first column
		ret[3][1] = (n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34) * idet; /// Fourth row, second column
		ret[3][2] = (n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34) * idet; /// Fourth row, third column
		ret[3][3] = (n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33) * idet; /// Fourth row, fourth column

		return ret; /// Return the calculated inverse matrix
	}

    Matrix::Matrix()
    {
	    m00 = 1; m01 = 0; m02 = 0; m03 = 0;
	    m10 = 0; m11 = 1; m12 = 0; m13 = 0;
	    m20 = 0; m21 = 0; m22 = 1; m23 = 0;
	    m30 = 0; m31 = 0; m32 = 0; m33 = 1;
    }

    Matrix::Matrix(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
    {
        this->m00 = m00; this->m01 = m01; this->m02 = m02; this->m03 = m03;
        this->m10 = m10; this->m11 = m11; this->m12 = m12; this->m13 = m13;
        this->m20 = m20; this->m21 = m21; this->m22 = m22; this->m23 = m23;
        this->m30 = m30; this->m31 = m31; this->m32 = m32; this->m33 = m33;
    }

    Matrix::Matrix(const Vec3 &translation, const Quat &rotation, const Vec3 &scale)
    {
        const Matrix mRotation = CreateRotation(rotation);

        m00 = scale.x * mRotation.m00;  m01 = scale.x * mRotation.m01;  m02 = scale.x * mRotation.m02;  m03 = 0.0f;
        m10 = scale.y * mRotation.m10;  m11 = scale.y * mRotation.m11;  m12 = scale.y * mRotation.m12;  m13 = 0.0f;
        m20 = scale.z * mRotation.m20;  m21 = scale.z * mRotation.m21;  m22 = scale.z * mRotation.m22;  m23 = 0.0f;
        m30 = translation.x;            m31 = translation.y;            m32 = translation.z;            m33 = 1.0f;
    }

    Matrix::Matrix(const float m[16])
    {
        // row-major to column-major
        m00 = m[0];  m01 = m[1];  m02 = m[2];  m03 = m[3];
        m10 = m[4];  m11 = m[5];  m12 = m[6];  m13 = m[7];
        m20 = m[8];  m21 = m[9];  m22 = m[10]; m23 = m[11];
        m30 = m[12]; m31 = m[13]; m32 = m[14]; m33 = m[15];
    }

    Matrix::~Matrix() = default;

    Vec3 Matrix::GetTranslation() const
	{
	    return {m30, m31, m32};
	}

    Matrix Matrix::CreateTranslation(const Vec3 &translation)
    {
        return {1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                translation.x, translation.y, translation.z, 1.0f};
    }

    Matrix Matrix::CreateRotation(const Quat &rotation)
    {
        const float num9 = rotation.x * rotation.x;
        const float num8 = rotation.y * rotation.y;
        const float num7 = rotation.z * rotation.z;
        const float num6 = rotation.x * rotation.y;
        const float num5 = rotation.z * rotation.w;
        const float num4 = rotation.z * rotation.x;
        const float num3 = rotation.y * rotation.w;
        const float num2 = rotation.y * rotation.z;
        const float num  = rotation.x * rotation.w;

        return {1.0f - (2.0f * (num8 + num7)),
                2.0f * (num6 + num5),
                2.0f * (num4 - num3),
                0.0f,
                2.0f * (num6 - num5),
                1.0f - (2.0f * (num7 + num9)),
                2.0f * (num2 + num),
                0.0f,
                2.0f * (num4 + num3),
                2.0f * (num2 - num),
                1.0f - (2.0f * (num8 + num9)),
                0.0f,
                0.0f,
                0.0f,
                0.0f,
                1.0f};
    }

    Quat Matrix::GetRotation() const
    {
        const Vec3 scale = GetScale();
        if (scale.x == 0.0f || scale.y == 0.0f || scale.z == 0.0f)
            return Quat::Identity();

        Matrix normalized;
        normalized.m00 = m00 / scale.x;
        normalized.m01 = m01 / scale.x;
        normalized.m02 = m02 / scale.x;
        normalized.m03 = 0.0f;
        normalized.m10 = m10 / scale.y;
        normalized.m11 = m11 / scale.y;
        normalized.m12 = m12 / scale.y;
        normalized.m13 = 0.0f;
        normalized.m20 = m20 / scale.z;
        normalized.m21 = m21 / scale.z;
        normalized.m22 = m22 / scale.z;
        normalized.m23 = 0.0f;
        normalized.m30 = 0;
        normalized.m31 = 0;
        normalized.m32 = 0;
        normalized.m33 = 1.0f;

        return RotationMatrixToQuaternion(normalized);
    }

    Quat Matrix::RotationMatrixToQuaternion(const Matrix &mRot)
    {
        Quat quaternion;
        float sqrt_;
        float half;
        const float scale = mRot.m00 + mRot.m11 + mRot.m22;

        if (scale > 0.0f)
        {
            sqrt_ = sqrt(scale + 1.0f);
            quaternion.w = sqrt_ * 0.5f;
            sqrt_ = 0.5f / sqrt_;

            quaternion.x = (mRot.m12 - mRot.m21) * sqrt_;
            quaternion.y = (mRot.m20 - mRot.m02) * sqrt_;
            quaternion.z = (mRot.m01 - mRot.m10) * sqrt_;

            return quaternion;
        }
        if ((mRot.m00 >= mRot.m11) && (mRot.m00 >= mRot.m22))
        {
            sqrt_ = sqrt(1.0f + mRot.m00 - mRot.m11 - mRot.m22);
            half = 0.5f / sqrt_;

            quaternion.x = 0.5f * sqrt_;
            quaternion.y = (mRot.m01 + mRot.m10) * half;
            quaternion.z = (mRot.m02 + mRot.m20) * half;
            quaternion.w = (mRot.m12 - mRot.m21) * half;

            return quaternion;
        }
        if (mRot.m11 > mRot.m22)
        {
            sqrt_ = sqrt(1.0f + mRot.m11 - mRot.m00 - mRot.m22);
            half = 0.5f / sqrt_;

            quaternion.x = (mRot.m10 + mRot.m01) * half;
            quaternion.y = 0.5f * sqrt_;
            quaternion.z = (mRot.m21 + mRot.m12) * half;
            quaternion.w = (mRot.m20 - mRot.m02) * half;

            return quaternion;
        }
        sqrt_ = sqrt(1.0f + mRot.m22 - mRot.m00 - mRot.m11);
        half  = 0.5f / sqrt_;

        quaternion.x = (mRot.m20 + mRot.m02) * half;
        quaternion.y = (mRot.m21 + mRot.m12) * half;
        quaternion.z = 0.5f * sqrt_;
        quaternion.w = (mRot.m01 - mRot.m10) * half;

        return quaternion;
    }

    Vec3 Matrix::GetScale() const
    {
        const int xs = (sign(m00 * m01 * m02 * m03) < 0) ? -1 : 1;
        const int ys = (sign(m10 * m11 * m12 * m13) < 0) ? -1 : 1;
        const int zs = (sign(m20 * m21 * m22 * m23) < 0) ? -1 : 1;
        return {static_cast<float>(xs) * sqrt(m00 * m00 + m01 * m01 + m02 * m02),
                static_cast<float>(ys) * sqrt(m10 * m10 + m11 * m11 + m12 * m12),
                static_cast<float>(zs) * sqrt(m20 * m20 + m21 * m21 + m22 * m22)};
    }

    Matrix Matrix::CreateScale(float scale)
    {
        return CreateScale(scale, scale, scale);
    }

    Matrix Matrix::CreateScale(const Vec3 &scale)
    {
        return CreateScale(scale.x, scale.y, scale.z);
    }

    Matrix Matrix::CreateScale(float scaleX, float scaleY, float ScaleZ)
    {
        return {scaleX, 0, 0, 0,
                0, scaleY, 0, 0,
                0, 0, ScaleZ, 0,
                0, 0, 0, 1};
    }

    Matrix Matrix::CreateLookAtLH(const Vec3 &position, const Vec3 &target, const Vec3 &up)
    {
        const Vec3 zAxis = Normalize(target - position);
        const Vec3 xAxis = Normalize(Cross(up, zAxis));
        const Vec3 yAxis = Cross(zAxis, xAxis);

        return {xAxis.x, yAxis.x, zAxis.x, 0,
                xAxis.y, yAxis.y, zAxis.y, 0,
                xAxis.z, yAxis.z, zAxis.z, 0,
                -Dot(xAxis, position), -Dot(yAxis, position), -Dot(zAxis, position), 1.0f};
    }

    Matrix Matrix::CreateOrthographicLH(float width, float height, float zNearPlane, float zFarPlane)
    {
        return {2 / width, 0, 0, 0,
                0, 2 / height, 0, 0,
                0, 0, 1 / (zFarPlane - zNearPlane), 0,
                0, 0, zNearPlane / (zNearPlane - zFarPlane), 1};
    }

    Matrix Matrix::CreateOrthoOffCenterLH(float left,
        float right,
        float bottom,
        float top,
        float zNearPlane,
        float zFarPlane)
    {
        return {2 / (right - left), 0, 0, 0,
                0, 2 / (top - bottom), 0, 0,
                0, 0, 1 / (zFarPlane - zNearPlane), 0,
                (left + right) / (left - right), (top + bottom) / (bottom - top), zNearPlane / (zNearPlane - zFarPlane), 1};
    }

    Matrix Matrix::CreatePerspectiveFieldOfViewLH(float fov_y_radians,
        float aspect_ratio,
        float near_plane,
        float far_plane)
    {
        const float tan_half_fovy = tan(fov_y_radians / 2);
        const float f             = 1.0f / tan_half_fovy;
        const float range_inv     = 1.0f / (far_plane - near_plane);

        return {f / aspect_ratio, 0, 0, 0,
                0, f, 0, 0,
                0, 0, far_plane * range_inv, 1,
                0, 0, -near_plane * far_plane * range_inv, 0};
    }

    Matrix Matrix::Transposed() const
    {
        return Matrix::Transpose(*this);
    }

    void Matrix::Transpose()
    {
        *this = Transpose(*this);
    }

    Matrix Matrix::Transpose(const Matrix &matrix)
    {
        return {matrix.m00, matrix.m10, matrix.m20, matrix.m30,
                matrix.m01, matrix.m11, matrix.m21, matrix.m31,
                matrix.m02, matrix.m12, matrix.m22, matrix.m32,
                matrix.m03, matrix.m13, matrix.m23, matrix.m33};
    }


    Matrix Matrix::Invert(const Matrix &matrix)
    {
        float v0 = matrix.m20 * matrix.m31 - matrix.m21 * matrix.m30;
        float v1 = matrix.m20 * matrix.m32 - matrix.m22 * matrix.m30;
        float v2 = matrix.m20 * matrix.m33 - matrix.m23 * matrix.m30;
        float v3 = matrix.m21 * matrix.m32 - matrix.m22 * matrix.m31;
        float v4 = matrix.m21 * matrix.m33 - matrix.m23 * matrix.m31;
        float v5 = matrix.m22 * matrix.m33 - matrix.m23 * matrix.m32;

        float i00 =  (v5 * matrix.m11 - v4 * matrix.m12 + v3 * matrix.m13);
        float i10 = -(v5 * matrix.m10 - v2 * matrix.m12 + v1 * matrix.m13);
        float i20 =  (v4 * matrix.m10 - v2 * matrix.m11 + v0 * matrix.m13);
        float i30 = -(v3 * matrix.m10 - v1 * matrix.m11 + v0 * matrix.m12);

        float det = i00 * matrix.m00 + i10 * matrix.m01 + i20 * matrix.m02 + i30 * matrix.m03;
        if (std::isnan(det))
            return Matrix::Identity;

        const float inv_det = 1.0f / det;

        i00 *= inv_det;
        i10 *= inv_det;
        i20 *= inv_det;
        i30 *= inv_det;

        const float i01 = -(v5 * matrix.m01 - v4 * matrix.m02 + v3 * matrix.m03) * inv_det;
        const float i11 =  (v5 * matrix.m00 - v2 * matrix.m02 + v1 * matrix.m03) * inv_det;
        const float i21 = -(v4 * matrix.m00 - v2 * matrix.m01 + v0 * matrix.m03) * inv_det;
        const float i31 =  (v3 * matrix.m00 - v1 * matrix.m01 + v0 * matrix.m02) * inv_det;

        v0 = matrix.m10 * matrix.m31 - matrix.m11 * matrix.m30;
        v1 = matrix.m10 * matrix.m32 - matrix.m12 * matrix.m30;
        v2 = matrix.m10 * matrix.m33 - matrix.m13 * matrix.m30;
        v3 = matrix.m11 * matrix.m32 - matrix.m12 * matrix.m31;
        v4 = matrix.m11 * matrix.m33 - matrix.m13 * matrix.m31;
        v5 = matrix.m12 * matrix.m33 - matrix.m13 * matrix.m32;

        const float i02 =  (v5 * matrix.m01 - v4 * matrix.m02 + v3 * matrix.m03) * inv_det;
        const float i12 = -(v5 * matrix.m00 - v2 * matrix.m02 + v1 * matrix.m03) * inv_det;
        const float i22 =  (v4 * matrix.m00 - v2 * matrix.m01 + v0 * matrix.m03) * inv_det;
        const float i32 = -(v3 * matrix.m00 - v1 * matrix.m01 + v0 * matrix.m02) * inv_det;

        v0 = matrix.m21 * matrix.m10 - matrix.m20 * matrix.m11;
        v1 = matrix.m22 * matrix.m10 - matrix.m20 * matrix.m12;
        v2 = matrix.m23 * matrix.m10 - matrix.m20 * matrix.m13;
        v3 = matrix.m22 * matrix.m11 - matrix.m21 * matrix.m12;
        v4 = matrix.m23 * matrix.m11 - matrix.m21 * matrix.m13;
        v5 = matrix.m23 * matrix.m12 - matrix.m22 * matrix.m13;

        const float i03 = -(v5 * matrix.m01 - v4 * matrix.m02 + v3 * matrix.m03) * inv_det;
        const float i13 =  (v5 * matrix.m00 - v2 * matrix.m02 + v1 * matrix.m03) * inv_det;
        const float i23 = -(v4 * matrix.m00 - v2 * matrix.m01 + v0 * matrix.m03) * inv_det;
        const float i33 =  (v3 * matrix.m00 - v1 * matrix.m01 + v0 * matrix.m02) * inv_det;

        return {i00, i01, i02, i03,
                i10, i11, i12, i13,
                i20, i21, i22, i23,
                i30, i31, i32, i33};
    }

    Matrix Matrix::Inverted() const
    {
        return Invert(*this);
    }

    void Matrix::Decompose(Vec3& scale, Quat& rotation, Vec3& translation) const
    {
        translation = GetTranslation();
        scale       = GetScale();
        rotation    = GetRotation();
    }

    void Matrix::SetIdentity()
    {
        m00 = 1; m01 = 0; m02 = 0; m03 = 0;
        m10 = 0; m11 = 1; m12 = 0; m13 = 0;
        m20 = 0; m21 = 0; m22 = 1; m23 = 0;
        m30 = 0; m31 = 0; m32 = 0; m33 = 1;
    }

    Matrix Matrix::operator*(const Matrix &rhs) const
    {
        return {m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20 + m03 * rhs.m30,
                m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21 + m03 * rhs.m31,
                m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22 + m03 * rhs.m32,
                m00 * rhs.m03 + m01 * rhs.m13 + m02 * rhs.m23 + m03 * rhs.m33,
                m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20 + m13 * rhs.m30,
                m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31,
                m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32,
                m10 * rhs.m03 + m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33,
                m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20 + m23 * rhs.m30,
                m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31,
                m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32,
                m20 * rhs.m03 + m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33,
                m30 * rhs.m00 + m31 * rhs.m10 + m32 * rhs.m20 + m33 * rhs.m30,
                m30 * rhs.m01 + m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31,
                m30 * rhs.m02 + m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32,
                m30 * rhs.m03 + m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33};
    }

    void Matrix::operator*=(const Matrix &rhs)
    {
        (*this) = (*this) * rhs;
    }

    Vec3 Matrix::operator*(const Vec3 &rhs) const
    {
        float x = (rhs.x * m00) + (rhs.y * m10) + (rhs.z * m20) + m30;
        float y = (rhs.x * m01) + (rhs.y * m11) + (rhs.z * m21) + m31;
        float z = (rhs.x * m02) + (rhs.y * m12) + (rhs.z * m22) + m32;
        float w = (rhs.x * m03) + (rhs.y * m13) + (rhs.z * m23) + m33;

        // to ensure the perspective divide, divide each component by w
        if (w != 1.0f)
        {
            x /= w;
            y /= w;
            z /= w;
        }

        return {x, y, z};
    }

    Vec4 Matrix::operator*(const Vec4 &rhs) const
    {
        return {(rhs.x * m00) + (rhs.y * m10) + (rhs.z * m20) + (rhs.w * m30),
                (rhs.x * m01) + (rhs.y * m11) + (rhs.z * m21) + (rhs.w * m31),
                (rhs.x * m02) + (rhs.y * m12) + (rhs.z * m22) + (rhs.w * m32),
                (rhs.x * m03) + (rhs.y * m13) + (rhs.z * m23) + (rhs.w * m33)};
    }

    bool Matrix::operator==(const Matrix &rhs) const
    {
        const float* data_left    = Data();
        const float* data_right    = rhs.Data();

        for (unsigned i = 0; i < 16; ++i)
        {
            if (data_left[i] != data_right[i])
                return false;
        }

        return true;
    }

    bool Matrix::operator!=(const Matrix &rhs) const
    {
        return !(*this == rhs);
    }

    bool Matrix::Equals(const Matrix &rhs) const
    {
        const float* data_left  = Data();
        const float* data_right = rhs.Data();

        for (unsigned i = 0; i < 16; ++i)
        {
            if (!approximate_equals(data_left[i], data_right[i]))
                return false;
        }

        return true;
    }

    const float * Matrix::Data() const
    {
        return &m00;
    }

}

/// -------------------------------------------------------
