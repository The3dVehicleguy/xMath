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
* mat4.cpp
* -------------------------------------------------------
* Created: 6/9/2025
* -------------------------------------------------------
*/
#include <sstream>
#include <xMath/includes/mat4.h>

/// -----------------------------------------------------

namespace xMath
{

	Mat4::Mat4() noexcept: rows{
	    Vec4{0.0f,0.0f,0.0f,0.0f},
	    Vec4{0.0f,0.0f,0.0f,0.0f},
	    Vec4{0.0f,0.0f,0.0f,0.0f},
	    Vec4{0.0f,0.0f,0.0f,0.0f}}
	{}

    Mat4::Mat4(float diagonal) noexcept: rows{
        Vec4{diagonal,0.0f,0.0f,0.0f},
        Vec4{0.0f,diagonal,0.0f,0.0f},
        Vec4{0.0f,0.0f,diagonal,0.0f},
        Vec4{0.0f,0.0f,0.0f,diagonal}}
    {}

    Mat4::Mat4(const Vec4(&inRows)[4]) noexcept: rows{inRows[0],inRows[1],inRows[2],inRows[3]} {}

    Mat4::Mat4(const std::initializer_list<Vec4> inRows) noexcept
    {
        int i = 0;
        for (auto it = inRows.begin(); it != inRows.end() && i < 4; ++it, ++i)
        {
            rows[i] = *it;
        }
        for (; i < 4; ++i)
        {
            rows[i] = Vec4{0.0f,0.0f,0.0f,0.0f};
        }
    }

    Mat4::Mat4(const std::initializer_list<float> cells) noexcept
    {
        for (auto &r : rows)
        {
            r = Vec4{0.0f,0.0f,0.0f,0.0f};
        }

        int i = 0;
        for (auto it = cells.begin(); it != cells.end() && i < 16; ++it, ++i)
        {
            const int rowIdx = i / 4;
            const int colIdx = i % 4;
            rows[rowIdx][colIdx] = *it;
        }
    }

    Mat4::Mat4(const Mat4 &copy) noexcept
    {
    }

    Mat4 Mat4::OrthographicProjection(const float aspect, const float nearPlane, const float farPlane) noexcept
    {
        return OrthographicProjection(-aspect, aspect, -1.0f, 1.0f, nearPlane, farPlane);
    }

    Mat4 Mat4::Translate(const Vec3 &translation) noexcept
    {
        return Mat4({
			{1.0f, 0.0f, 0.0f, translation.x},
            {0.0f, 1.0f, 0.0f, translation.y},
            {0.0f, 0.0f, 1.0f, translation.z},
            {0.0f, 0.0f, 0.0f, 1.0f}});
    }

    float * Mat4::Data() noexcept
	{
	    return &rows[0][0];
	}

    const float * Mat4::Data() const noexcept
	{
	    return &rows[0][0];
	}

    Mat4 Mat4::Scale(const Vec2 &scale) noexcept
    {
        return Mat4({
			{scale.x, 0.0f, 0.0f, 0.0f},
            {0.0f, scale.y, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}});
    }

    Mat4 Mat4::Scale(const Vec3 &scale) noexcept
    {
        return Mat4({
			{scale.x, 0.0f, 0.0f, 0.0f},
            {0.0f, scale.y, 0.0f, 0.0f},
            {0.0f, 0.0f, scale.z, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        });
    }

    Mat4 Mat4::Zero() noexcept
	{
	    return {};
	}

    Mat4 Mat4::Identity() noexcept
	{
	    return Mat4(1.0f);
	}

    Vec4 & Mat4::operator[](const int index) noexcept
    {
        return rows[index];
    }

    Mat4 Mat4::operator+=(const Mat4 &rhs) noexcept
    {
        *this = *this + rhs;
        return *this;
    }

    Mat4 Mat4::operator-=(const Mat4 &rhs) noexcept
    {
        *this = *this - rhs;
        return *this;
    }

    Mat4 Mat4::operator*=(const float rhs) noexcept
    {
        *this = *this * rhs;
        return *this;
    }

    Mat4 Mat4::operator/=(const float rhs) noexcept
    {
        *this = *this / rhs;
        return *this;
    }

    Mat4 Mat4::operator*(const Mat4 &rhs) const noexcept
    {
        return Multiply(*this, rhs);
    }

    Vec4 Mat4::operator*(const Vec4 &rhs) const noexcept
    {
        return Multiply(*this, rhs);
    }

    Vec4 Mat4::operator*(const Vec3 &rhs) const noexcept
    {
        return Multiply(*this, Vec4(rhs, 1.0f));
    }

    Mat4 Mat4::operator*=(const Mat4 &rhs) noexcept
    {
        *this = *this * rhs;
        return *this;
    }

    bool Mat4::operator==(const Mat4 &rhs) const noexcept
    {
        // Exact comparison (legacy semantics). For tolerant comparison use Mat4::NearlyEqual.
        return rows[0] == rhs.rows[0] && rows[1] == rhs.rows[1] && rows[2] == rhs.rows[2] && rows[3] == rhs.rows[3];
    }

    bool Mat4::operator!=(const Mat4 &rhs) const noexcept
	{
	    return !(*this == rhs);
	}

    bool Mat4::NearlyEqual(const Mat4 &a, const Mat4 &b, float epsilon) noexcept
    {
        for (int r = 0; r < 4; ++r)
        {
            for (int c = 0; c < 4; ++c)
            {
                if (std::fabs(a.rows[r][c] - b.rows[r][c]) > epsilon)
					return false;
            }
        }
        return true;
    }

    void Mat4::Transpose() noexcept
    {
        *this = GetTranspose(*this);
    }

    Mat4 Mat4::GetTranspose() const noexcept
    {
        return GetTranspose(*this);
    }

    Mat4 Mat4::GetInverse() const noexcept
    {
        return GetInverse(*this);
    }

    void Mat4::Invert() noexcept
    {
        *this = GetInverse(*this);
    }

    std::string Mat4::ToString() const
    {
#if XMATH_HAS_FMT
        return fmt::format("[{} {} {} {}]\n[{} {} {} {}]\n[{} {} {} {}]\n[{} {} {} {}]",
                           rows[0][0], rows[0][1], rows[0][2], rows[0][3],
                           rows[1][0], rows[1][1], rows[1][2], rows[1][3],
                           rows[2][0], rows[2][1], rows[2][2], rows[2][3],
                           rows[3][0], rows[3][1], rows[3][2], rows[3][3]);
#else
        std::ostringstream oss;
        oss << '[' << rows[0][0] << ' ' << rows[0][1] << ' ' << rows[0][2] << ' ' << rows[0][3] << "]\n";
        oss << '[' << rows[1][0] << ' ' << rows[1][1] << ' ' << rows[1][2] << ' ' << rows[1][3] << "]\n";
        oss << '[' << rows[2][0] << ' ' << rows[2][1] << ' ' << rows[2][2] << ' ' << rows[2][3] << "]\n";
        oss << '[' << rows[3][0] << ' ' << rows[3][1] << ' ' << rows[3][2] << ' ' << rows[3][3] << ']';
        return oss.str();
#endif
    }


}

/// -----------------------------------------------------
