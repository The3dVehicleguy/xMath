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

// -----------------------------------------------------

namespace xMath
{

	Mat4::Mat4() noexcept
	{
		// initialize all elements to zero
		float* d = Data();
		for (int i = 0; i < 16; ++i) d[i] = 0.0f;
	}

	Mat4::Mat4(float diagonal) noexcept
	{
		float* d = Data();
		for (int i = 0; i < 16; ++i) d[i] = 0.0f;
		// logical diagonal positions: (0,0),(1,1),(2,2),(3,3)
		// assign via element accessor to maintain logical layout
		// m00..m33 names exist, so set directly
		m00 = diagonal; m11 = diagonal; m22 = diagonal; m33 = diagonal;
	}

	Mat4::Mat4(const Vec4(&inRows)[4]) noexcept
	{
		// assign by logical rows
		for (int r = 0; r < 4; ++r)
		{
			for (int c = 0; c < 4; ++c)
			{
				// assign logical element mRC
				switch (r*4 + c)
				{
				case 0: m00 = inRows[r][c]; break; case 1: m01 = inRows[r][c]; break; case 2: m02 = inRows[r][c]; break; case 3: m03 = inRows[r][c]; break;
				case 4: m10 = inRows[r][c]; break; case 5: m11 = inRows[r][c]; break; case 6: m12 = inRows[r][c]; break; case 7: m13 = inRows[r][c]; break;
				case 8: m20 = inRows[r][c]; break; case 9: m21 = inRows[r][c]; break; case 10: m22 = inRows[r][c]; break; case 11: m23 = inRows[r][c]; break;
				case 12: m30 = inRows[r][c]; break; case 13: m31 = inRows[r][c]; break; case 14: m32 = inRows[r][c]; break; case 15: m33 = inRows[r][c]; break;
				}
			}
		}
	}

	Mat4::Mat4(const std::initializer_list<Vec4> inRows) noexcept
	{
		int i = 0;
		for (auto it = inRows.begin(); it != inRows.end() && i < 4; ++it, ++i)
		{
			const Vec4 &v = *it;
			switch (i)
			{
			case 0: m00 = v.x; m01 = v.y; m02 = v.z; m03 = v.w; break;
			case 1: m10 = v.x; m11 = v.y; m12 = v.z; m13 = v.w; break;
			case 2: m20 = v.x; m21 = v.y; m22 = v.z; m23 = v.w; break;
			case 3: m30 = v.x; m31 = v.y; m32 = v.z; m33 = v.w; break;
			}
		}
		for (; i < 4; ++i)
		{
			switch (i)
			{
			case 0: m00 = m01 = m02 = m03 = 0.0f; break;
			case 1: m10 = m11 = m12 = m13 = 0.0f; break;
			case 2: m20 = m21 = m22 = m23 = 0.0f; break;
			case 3: m30 = m31 = m32 = m33 = 0.0f; break;
			}
		}
	}

	Mat4::Mat4(const std::initializer_list<float> cells) noexcept
	{
		// initialize all to zero first
		for (int r = 0; r < 4; ++r)
			for (int c = 0; c < 4; ++c)
			{
				switch (r*4 + c)
				{
				case 0: m00 = 0.0f; break; case 1: m01 = 0.0f; break; case 2: m02 = 0.0f; break; case 3: m03 = 0.0f; break;
				case 4: m10 = 0.0f; break; case 5: m11 = 0.0f; break; case 6: m12 = 0.0f; break; case 7: m13 = 0.0f; break;
				case 8: m20 = 0.0f; break; case 9: m21 = 0.0f; break; case 10: m22 = 0.0f; break; case 11: m23 = 0.0f; break;
				case 12: m30 = 0.0f; break; case 13: m31 = 0.0f; break; case 14: m32 = 0.0f; break; case 15: m33 = 0.0f; break;
				}
			}

		int i = 0;
		for (auto it = cells.begin(); it != cells.end() && i < 16; ++it, ++i)
		{
			const int rowIdx = i / 4;
			const int colIdx = i % 4;
			// assign logical element [rowIdx][colIdx]
			switch (rowIdx*4 + colIdx)
			{
			case 0: m00 = *it; break; case 1: m01 = *it; break; case 2: m02 = *it; break; case 3: m03 = *it; break;
			case 4: m10 = *it; break; case 5: m11 = *it; break; case 6: m12 = *it; break; case 7: m13 = *it; break;
			case 8: m20 = *it; break; case 9: m21 = *it; break; case 10: m22 = *it; break; case 11: m23 = *it; break;
			case 12: m30 = *it; break; case 13: m31 = *it; break; case 14: m32 = *it; break; case 15: m33 = *it; break;
			}
		}
	}

	Mat4::Mat4(const Mat4 &copy) noexcept
	{
		// copy all elements
		const float* s = copy.Data();
		float* d = Data();
		for (int i = 0; i < 16; ++i) d[i] = s[i];
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
		return &m00;
	}

	const float * Mat4::Data() const noexcept
	{
		return &m00;
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

	Mat4::RowProxy Mat4::operator[](int index) noexcept
	{
		return {this, index};
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
		const float* a = Data();
		const float* b = rhs.Data();
		for (int i = 0; i < 16; ++i) if (a[i] != b[i]) return false;
		return true;
	}

	bool Mat4::operator!=(const Mat4 &rhs) const noexcept
	{
		return !(*this == rhs);
	}

	bool Mat4::NearlyEqual(const Mat4 &a, const Mat4 &b, float epsilon) noexcept
	{
		// Compare logical elements (row-major order of indices)
		auto elem = [](const Mat4 &m, int r, int c) -> float {
			switch (r*4 + c)
			{
			case 0: return m.m00; case 1: return m.m01; case 2: return m.m02; case 3: return m.m03;
			case 4: return m.m10; case 5: return m.m11; case 6: return m.m12; case 7: return m.m13;
			case 8: return m.m20; case 9: return m.m21; case 10: return m.m22; case 11: return m.m23;
			default: return (r*4 + c) == 12 ? m.m30 : ((r*4 + c) == 13 ? m.m31 : ((r*4 + c) == 14 ? m.m32 : m.m33));
			}
		};

		for (int r = 0; r < 4; ++r)
		{
			for (int c = 0; c < 4; ++c)
			{
				if (std::fabs(elem(a, r, c) - elem(b, r, c)) > epsilon)
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
						   m00, m01, m02, m03,
						   m10, m11, m12, m13,
						   m20, m21, m22, m23,
						   m30, m31, m32, m33);
#else
		std::ostringstream oss;
		oss << '[' << m00 << ' ' << m01 << ' ' << m02 << ' ' << m03 << "]\n";
		oss << '[' << m10 << ' ' << m11 << ' ' << m12 << ' ' << m13 << "]\n";
		oss << '[' << m20 << ' ' << m21 << ' ' << m22 << ' ' << m23 << "]\n";
		oss << '[' << m30 << ' ' << m31 << ' ' << m32 << ' ' << m33 << ']';
		return oss.str();
#endif
	}

	// const operator[] returns a Vec4 value
	Vec4 Mat4::operator[](int index) const noexcept
	{
		switch (index)
		{
		case 0: return Vec4{m00, m01, m02, m03};
		case 1: return Vec4{m10, m11, m12, m13};
		case 2: return Vec4{m20, m21, m22, m23};
		default: return Vec4{m30, m31, m32, m33};
		}
	}


}

/// -----------------------------------------------------
