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
* matrix.h
* -------------------------------------------------------
* Created: 15/7/2025
* -------------------------------------------------------
*/
#pragma once
#include <quat.h>
#include <string>
#include <vector.h>

// -------------------------------------------------------

namespace xMath
{

#if !defined(XMATH_MATRIX_IS_ROW_MAJOR) && !defined(XMATH_MATRIX_IS_COLUMN_MAJOR)
// Fallback: assume row-major storage
#define XMATH_MATRIX_IS_ROW_MAJOR 1
#define XMATH_MATRIX_IS_COLUMN_MAJOR 0
#endif

    /**
     * @class Matrix
     * @brief Represents a 4x4 transformation matrix for 3D graphics.
     * @note MatrixR is stored in row-major order, meaning elements are accessed as m[row][column].
     * @note MatrixC is stored in column-major order, meaning elements are accessed as m[column][row].
     */
    class XMATH_API Matrix
    {
    public:
        /* @brief Default constructor initializes to identity matrix. */
        Matrix();

        /**
         * @brief Copy constructor.
         * @param rhs The matrix to copy from.
         */
        Matrix(const Matrix &rhs);

        /**
         * @brief Constructor with individual matrix elements.
         *
         * @param m00 Element at row 0, column 0.
         * @param m01 Element at row 0, column 1.
         * @param m02 Element at row 0, column 2.
         * @param m03 Element at row 0, column 3.
         * @param m10 Element at row 1, column 0.
         * @param m11 Element at row 1, column 1.
         * @param m12 Element at row 1, column 2.
         * @param m13 Element at row 1, column 3.
         * @param m20 Element at row 2, column 0.
         * @param m21 Element at row 2, column 1.
         * @param m22 Element at row 2, column 2.
         * @param m23 Element at row 2, column 3.
         * @param m30 Element at row 3, column 0.
         * @param m31 Element at row 3, column 1.
         * @param m32 Element at row 3, column 2.
         * @param m33 Element at row 3, column 3.
         */
        Matrix(float m00, float m01, float m02, float m03,
               float m10, float m11, float m12, float m13,
               float m20, float m21, float m22, float m23,
               float m30, float m31, float m32, float m33);

        /**
         * @brief Constructor with translation, rotation, and scale components.
         *
         * @param translation The translation vector.
         * @param rotation The rotation quaternion.
         * @param scale The scale vector.
         */
        Matrix(const Vec3& translation, const Quat& rotation, const Vec3& scale);

        /**
         * @brief Constructor with an array of 16 floats representing the matrix elements.
         *
         * @param m Pointer to an array of 16 floats in row-major order.
         */
        explicit Matrix(const float m[16]);

        ~Matrix();

        /**
         * @brief Retrieves the translation component from the matrix. 
         *
         * @return A Vec3 representing the translation (x, y, z) extracted from the matrix. 
         */
        [[nodiscard]] Vec3 GetTranslation() const;

        /**
         * @brief Creates a translation matrix from a given translation vector.
         *
         * @param translation The translation vector.
         * @return A Matrix representing the translation transformation.
         */
        Matrix CreateTranslation(const Vec3 &translation);

        /**
         * @brief Creates a rotation matrix from a given quaternion.
         *
         * @param rotation The rotation quaternion.
         * @return A Matrix representing the rotation transformation.
         */
        Matrix CreateRotation(const Quat &rotation);

        /**
         * @brief Retrieves the rotation component from the matrix as a quaternion.
         *
         * @return A Quat representing the rotation extracted from the matrix.
         */
        [[nodiscard]] Quat GetRotation() const;

        /**
         * @brief Converts a rotation matrix to a quaternion.
         *
         * @param mRot The rotation matrix to convert.
         * @return A Quat representing the rotation extracted from the matrix.
         */
        static Quat RotationMatrixToQuaternion(const Matrix &mRot);

        /**
         * @brief Retrieves the scale component from the matrix.
         *
         * @return A Vec3 representing the scale (x, y, z) extracted from the matrix.
         */
        [[nodiscard]] Vec3 GetScale() const;

        /**
         * @brief Creates a uniform scale matrix.
         *
         * @param scale The uniform scale factor.
         * @return A Matrix representing the uniform scale transformation.
         */
        Matrix CreateScale(float scale);

        /**
         * @brief Creates a non-uniform scale matrix.
         *
         * @param scale The scale vector.
         * @return A Matrix representing the non-uniform scale transformation.
         */
        Matrix CreateScale(const Vec3& scale);

        /**
         * @brief Creates a non-uniform scale matrix with individual scale factors for each axis.
         *
         * @param scaleX The scale factor along the X-axis.
         * @param scaleY The scale factor along the Y-axis.
         * @param scaleZ The scale factor along the Z-axis.
         * @return A Matrix representing the non-uniform scale transformation.
         */
        Matrix CreateScale(float scaleX, float scaleY, float scaleZ);

        /**
         * @brief Creates a left-handed look-at matrix for camera transformations.
         *
         * @param position The position of the camera (eye point).
         * @param target The point in space the camera is looking at (target point).
         * @param up The up direction vector for the camera, defining its orientation.
         * @return A Matrix representing the look-at transformation.
         */
        Matrix CreateLookAtLH(const Vec3& position, const Vec3& target, const Vec3& up);

        /**
         * @brief Creates a left-handed orthographic projection matrix.
         *
         * @param width The width of the orthographic projection volume.
         * @param height The height of the orthographic projection volume.
         * @param zNearPlane The distance to the near clipping plane.
         * @param zFarPlane The distance to the far clipping plane.
         * @return A Matrix representing the orthographic projection transformation.
         */
        Matrix CreateOrthographicLH(float width, float height, float zNearPlane, float zFarPlane);

        /**
         * @brief Creates a left-handed off-center orthographic projection matrix.
         *
         * @param left The left edge of the projection volume (minimum X coordinate).
         * @param right The right edge of the projection volume (maximum X coordinate). Must be > left.
         * @param bottom The bottom edge of the projection volume (minimum Y coordinate).
         * @param top The top edge of the projection volume (maximum Y coordinate). Must be > bottom.
         * @param zNearPlane The distance to the near clipping plane.
         * @param zFarPlane The distance to the far clipping plane. Must be != nearPlane.
         * @return A Matrix representing the off-center orthographic projection transformation.
         */
        Matrix CreateOrthoOffCenterLH(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);

        /**
         * @brief Creates a left-handed perspective projection matrix based on a field of view.
         *
         * @param fovYRadians The vertical field of view angle in radians.
         * @param aspectRatio The aspect ratio of the viewport (width / height).
         * @param nearPlane The distance to the near clipping plane.
         * @param farPlane The distance to the far clipping plane.
         * @return A Matrix representing the perspective projection transformation.
         */
        Matrix CreatePerspectiveFieldOfViewLH(float fovYRadians, float aspectRatio, float nearPlane, float farPlane);

        /**
         * @brief Returns the transposed version of this matrix.
         *
         * @return A Matrix representing the transposed transformation.
         */
        [[nodiscard]] Matrix Transposed() const;

        /* @brief Transposes this matrix in place. */
        void Transpose();

        /**
         * @brief Returns the transposed version of the given matrix.
         *
         * @param matrix The matrix to be transposed.
         * @return A Matrix representing the transposed transformation.
         */
        static Matrix Transpose(const Matrix &matrix);

        /**
         * @brief Returns the inverted version of this matrix.
         *
         * @return A Matrix representing the inverted transformation.
         */
        [[nodiscard]] Matrix Inverted() const;

        /**
         * @brief Returns the inverted version of the given matrix.
         *
         * @param matrix The matrix to be inverted.
         * @return A Matrix representing the inverted transformation.
         */
        [[nodiscard]] static Matrix Invert(const Matrix &matrix);

        /**
         * @brief Decomposes this matrix into its scale, rotation, and translation components.
         *
         * @param scale The output scale component of the decomposition.
         * @param rotation The output rotation component of the decomposition.
         * @param translation The output translation component of the decomposition.
         */
        void Decompose(Vec3& scale, Quat& rotation, Vec3& translation) const;

        /* @brief Sets this matrix to the identity matrix. */
        void SetIdentity();

        /**
         * @brief Multiplies this matrix by another matrix.
         *
         * @param rhs The matrix to multiply with.
         * @return A Matrix representing the result of the multiplication.
         */
        Matrix operator*(const Matrix& rhs) const;

        /**
         * @brief Multiplies this matrix by another matrix in place.
         *
         * @param rhs The matrix to multiply with.
         */
        void operator*=(const Matrix& rhs);

        /**
         * @brief Multiplies this matrix by a 3D vector.
         *
         * @param rhs The 3D vector to multiply with.
         * @return A Vec3 representing the result of the multiplication.
         */
        Vec3 operator*(const Vec3& rhs) const;

        /**
         * @brief Multiplies this matrix by a 4D vector.
         *
         * @param rhs The 4D vector to multiply with.
         * @return A Vec4 representing the result of the multiplication.
         */
        Vec4 operator*(const Vec4& rhs) const;

        /**
         * @brief Checks if this matrix is equal to another matrix.
         *
         * @param rhs The matrix to compare with.
         * @return True if the matrices are equal, false otherwise.
         */
        bool operator==(const Matrix& rhs) const;

        /**
         * @brief Checks if this matrix is not equal to another matrix.
         *
         * @param rhs The matrix to compare with.
         * @return True if the matrices are not equal, false otherwise.
         */
        bool operator!=(const Matrix& rhs) const;

        /**
         * @brief Checks if this matrix is equal to another matrix.
         *
         * @param rhs The matrix to compare with.
         * @return True if the matrices are equal, false otherwise.
         */
        [[nodiscard]] bool Equals(const Matrix& rhs) const;

        /**
         * @brief Returns a pointer to the underlying data of the matrix.
         *
         * @return A pointer to the matrix data.
         */
        [[nodiscard]] const float* Data() const;

        /**
         * @brief Converts the matrix to a string representation.
         *
         * @return A string representing the matrix.
         */
        [[nodiscard]] std::string ToString() const;

        // Member declaration order changes the contiguous layout returned by Data()
        // Keep element names consistent (mRC = row R column C)
#if XMATH_MATRIX_IS_ROW_MAJOR
        // Row-major contiguous memory: row0, row1, row2, row3
        float m00 = 0.0f, m01 = 0.0f, m02 = 0.0f, m03 = 0.0f;
        float m10 = 0.0f, m11 = 0.0f, m12 = 0.0f, m13 = 0.0f;
        float m20 = 0.0f, m21 = 0.0f, m22 = 0.0f, m23 = 0.0f;
        float m30 = 0.0f, m31 = 0.0f, m32 = 0.0f, m33 = 0.0f;
#else
        // Column-major contiguous memory: column0, column1, column2, column3
        float m00 = 0.0f, m10 = 0.0f, m20 = 0.0f, m30 = 0.0f;
        float m01 = 0.0f, m11 = 0.0f, m21 = 0.0f, m31 = 0.0f;
        float m02 = 0.0f, m12 = 0.0f, m22 = 0.0f, m32 = 0.0f;
        float m03 = 0.0f, m13 = 0.0f, m23 = 0.0f, m33 = 0.0f;
#endif

        static const Matrix IDENTITY; // Identity matrix constant (1s on diagonal, 0s elsewhere)
    };

}


/// -------------------------------------------------------
