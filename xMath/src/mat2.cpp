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
* mat2.cpp
* -------------------------------------------------------
* Created: 6/9/2025
* -------------------------------------------------------
*/
#include <epsilon.h>
#include <xMath/includes/mat2.h>

/// -----------------------------------------------------

namespace xMath
{

    constexpr Mat2::Mat2() noexcept: m00(1), m01(0), m10(0), m11(1)
    {}

    constexpr Mat2::Mat2(float s) noexcept: m00(s), m01(0), m10(0), m11(s)
    {}

    constexpr Mat2::Mat2(float _m00, float _m01, float _m10, float _m11) noexcept: m00(_m00), m01(_m01), m10(_m10), m11(_m11)
    {}

    constexpr Mat2 Mat2::FromRows(const TVector2<float> &r0, const TVector2<float> &r1) noexcept
    {
        return {r0.x, r0.y, r1.x, r1.y};
    }

    constexpr Mat2 Mat2::FromColumns(const TVector2<float> &c0, const TVector2<float> &c1) noexcept
    {
        return {c0.x, c1.x, c0.y, c1.y};
    }

    constexpr Mat2 Mat2::Identity() noexcept
    {
        return {};
    }

    constexpr Mat2 Mat2::Zero() noexcept
    {
        return {0, 0, 0, 0};
    }

    constexpr Mat2 Mat2::Scale(float sx, float sy) noexcept
    {
        return {sx, 0, 0, sy};
    }

    constexpr Mat2 Mat2::Scale(const TVector2<float> &s) noexcept
    {
        return Scale(s.x, s.y);
    }

    constexpr float & Mat2::operator()(int r, int c) noexcept
    {
        return r == 0 ? (c == 0 ? m00 : m01) : (c == 0 ? m10 : m11);
    }

    constexpr const float & Mat2::operator()(int r, int c) const noexcept
    {
        return r == 0 ? (c == 0 ? m00 : m01) : (c == 0 ? m10 : m11);
    }

    constexpr Mat2 Mat2::operator+(const Mat2 &rhs) const noexcept
    {
        return {m00 + rhs.m00, m01 + rhs.m01, m10 + rhs.m10, m11 + rhs.m11};
    }

    constexpr Mat2 Mat2::operator-(const Mat2 &rhs) const noexcept
    {
        return {m00 - rhs.m00, m01 - rhs.m01, m10 - rhs.m10, m11 - rhs.m11};
    }

    constexpr Mat2 Mat2::operator*(float s) const noexcept
    {
        return {m00 * s, m01 * s, m10 * s, m11 * s};
    }

    constexpr Mat2 & Mat2::operator+=(const Mat2 &r) noexcept
    {
        m00 += r.m00; m01 += r.m01; m10 += r.m10; m11 += r.m11; return *this;
    }

    constexpr Mat2 & Mat2::operator-=(const Mat2 &r) noexcept
    {
        m00 -= r.m00; m01 -= r.m01; m10 -= r.m10; m11 -= r.m11; return *this;
    }

    constexpr Mat2 & Mat2::operator*=(float s) noexcept
    {
        m00 *= s; m01 *= s; m10 *= s; m11 *= s; return *this;
    }

    constexpr Mat2 Mat2::operator*(const Mat2 &r) const noexcept
    {
        return {
            m00 * r.m00 + m01 * r.m10,
            m00 * r.m01 + m01 * r.m11,
            m10 * r.m00 + m11 * r.m10,
            m10 * r.m01 + m11 * r.m11
        };
    }

    constexpr Mat2 & Mat2::operator*=(const Mat2 &r) noexcept
    {
        *this = (*this) * r; return *this;
    }

    constexpr float Mat2::Trace() const noexcept
    {
        return m00 + m11;
    }

    constexpr float Mat2::Determinant() const noexcept
    {
        return m00 * m11 - m01 * m10;
    }

    constexpr Mat2 Mat2::Transposed() const noexcept
    {
        return {m00, m10, m01, m11};
    }

    constexpr bool Mat2::operator==(const Mat2 &r) const noexcept
    {
        return m00 == r.m00 && m01 == r.m01 && m10 == r.m10 && m11 == r.m11;
    }

    constexpr bool Mat2::operator!=(const Mat2 &r) const noexcept
    {
        return !(*this == r);
    }

    Mat2 Mat2::Rotation(float radians) noexcept
    {
        const float c = std::cos(radians);
        const float s = std::sin(radians);
        return {c, -s, s, c};
    }

    TVector2<float> Mat2::Row(int r) const noexcept
    {
        return r == 0 ? TVector2<float>{m00, m01} : TVector2<float>{m10, m11};
    }

    TVector2<float> Mat2::Column(int c) const noexcept
    {
        return c == 0 ? TVector2<float>{m00, m10} : TVector2<float>{m01, m11};
    }

    TVector2<float> Mat2::operator*(const TVector2<float> &v) const noexcept
    {
        return TVector2<float>{ m00 * v.x + m01 * v.y, m10 * v.x + m11 * v.y };
    }

    Mat2 Mat2::Inversed(float eps) const noexcept
    {
        const float det = Determinant();
        if (std::fabs(det) <= eps) return Mat2::Zero();
        const float invDet = 1.0f / det;
        /// adjudicate: [ m11 -m01; -m10 m00 ]
        return {
            m11 * invDet, -m01 * invDet,
            -m10 * invDet,  m00 * invDet
        };
    }

    bool Mat2::TryInverse(Mat2 &out, float eps) const noexcept
    {
        const float det = Determinant();
        if (std::fabs(det) <= eps) { out = Mat2::Zero(); return false; }
        const float invDet = 1.0f / det;
        out = Mat2( m11 * invDet, -m01 * invDet,
                    -m10 * invDet,  m00 * invDet);
        return true;
    }

    bool Mat2::ApproxEqual(const Mat2 &a, const Mat2 &b, float eps) noexcept
    {
        return epsilonEqual(a.m00, b.m00, eps) && epsilonEqual(a.m01, b.m01, eps) &&
               epsilonEqual(a.m10, b.m10, eps) && epsilonEqual(a.m11, b.m11, eps);
    }

    std::ostream & operator<<(std::ostream &os, const Mat2 &m)
    {
        os << "[" << m.m00 << ", " << m.m01 << "; " << m.m10 << ", " << m.m11 << "]";
        return os;
    }

}

/// -----------------------------------------------------
