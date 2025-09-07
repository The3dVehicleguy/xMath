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

/// -------------------------------------------------------

namespace xMath
{

    class XMATH_API Matrix
    {
    public:
        Matrix();
        Matrix(const Matrix &rhs) = default;

        Matrix(float m00, float m01, float m02, float m03,
               float m10, float m11, float m12, float m13,
               float m20, float m21, float m22, float m23,
               float m30, float m31, float m32, float m33);

        Matrix(const Vec3& translation, const Quat& rotation, const Vec3& scale);

        explicit Matrix(const float m[16]);
        ~Matrix();


        [[nodiscard]] Vec3 GetTranslation() const;
        Matrix CreateTranslation(const Vec3 &translation);

        Matrix CreateRotation(const Quat &rotation);
        [[nodiscard]] Quat GetRotation() const;
        static Quat RotationMatrixToQuaternion(const Matrix &mRot);

        [[nodiscard]] Vec3 GetScale() const;
        Matrix CreateScale(float scale);
        Matrix CreateScale(const Vec3& scale);
        Matrix CreateScale(float scaleX, float scaleY, float ScaleZ);

        Matrix CreateLookAtLH(const Vec3& position, const Vec3& target, const Vec3& up);
        Matrix CreateOrthographicLH(float width, float height, float zNearPlane, float zFarPlane);
        Matrix CreateOrthoOffCenterLH(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);
        Matrix CreatePerspectiveFieldOfViewLH(float fov_y_radians, float aspect_ratio, float near_plane, float far_plane);

        [[nodiscard]] Matrix Transposed() const;
        void Transpose();
        static Matrix Transpose(const Matrix &matrix);
        [[nodiscard]] Matrix Inverted() const;
        [[nodiscard]] static Matrix Invert(const Matrix &matrix);

        void Decompose(Vec3& scale, Quat& rotation, Vec3& translation) const;
        void SetIdentity();

        Matrix operator*(const Matrix& rhs) const;
        void operator*=(const Matrix& rhs);
        Vec3 operator*(const Vec3& rhs) const;
        Vec4 operator*(const Vec4& rhs) const;
        bool operator==(const Matrix& rhs) const;
        bool operator!=(const Matrix& rhs) const;

        [[nodiscard]] bool Equals(const Matrix& rhs) const;
        [[nodiscard]] const float* Data() const;
        [[nodiscard]] std::string ToString() const;

        float m00 = 0.0f, m10 = 0.0f, m20 = 0.0f, m30 = 0.0f;
        float m01 = 0.0f, m11 = 0.0f, m21 = 0.0f, m31 = 0.0f;
        float m02 = 0.0f, m12 = 0.0f, m22 = 0.0f, m32 = 0.0f;
        float m03 = 0.0f, m13 = 0.0f, m23 = 0.0f, m33 = 0.0f;

        static const Matrix Identity;
    };

}


/// -------------------------------------------------------
