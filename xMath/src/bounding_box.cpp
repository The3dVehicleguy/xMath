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
* bounding_box.cpp
* -------------------------------------------------------
* Created: 6/9/2025
* -------------------------------------------------------
*/
#include <xMath/includes/bounding_box.h>

// -----------------------------------------------------

namespace xMath
{

	const BoundingBox BoundingBox::ZERO(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	const BoundingBox BoundingBox::UNIT(Vec3(-0.5f, -0.5f, -0.5f), Vec3(0.5f, 0.5f, 0.5f));
	const BoundingBox BoundingBox::INFINITE(Vec3::INFINITY_NEG<float>, Vec3::VEC3_INFINITY<float>);

	/*
	BoundingBox::BoundingBox()
	{
		m_min = Vec3::Infinity;
		m_max = Vec3::InfinityNeg;
	}
	*/

	BoundingBox::BoundingBox(const Vec3 &min, const Vec3 &max) : Min(), Max()
	{
		this->m_Min = min;
		this->m_Max = max;
	}

	BoundingBox::BoundingBox(const Vec3 *vertices, const uint32_t point_count) : Min(), Max()
	{
		m_Min = Vec3::VEC3_INFINITY<float>;
		m_Max = Vec3::INFINITY_NEG<float>;

		for (uint32_t i = 0; i < point_count; i++)
		{
			m_Max.x = std::max(m_Max.x, vertices[i].x);
			m_Max.y = std::max(m_Max.y, vertices[i].y);
			m_Max.z = std::max(m_Max.z, vertices[i].z);

			m_Min.x = std::min(m_Min.x, vertices[i].x);
			m_Min.y = std::min(m_Min.y, vertices[i].y);
			m_Min.z = std::min(m_Min.z, vertices[i].z);
		}
	}

	/*
	BoundingBox::BoundingBox(const Vertex_PosTexNorTan *vertices, const uint32_t vertex_count)
	{
		m_min = Vec3::Infinity;
		m_max = Vec3::InfinityNeg;

		for (uint32_t i = 0; i < vertex_count; i++)
		{
			m_max.x = std::max(m_max.x, vertices[i].pos[0]);
			m_max.y = std::max(m_max.y, vertices[i].pos[1]);
			m_max.z = std::max(m_max.z, vertices[i].pos[2]);

			m_min.x = std::min(m_min.x, vertices[i].pos[0]);
			m_min.y = std::min(m_min.y, vertices[i].pos[1]);
			m_min.z = std::min(m_min.z, vertices[i].pos[2]);
		}
	}
	*/

	bool BoundingBox::operator==(const BoundingBox &other) const
	{
		return GetMin() == other.GetMin() && GetMax() == other.GetMax();
	}

	BoundingBox BoundingBox::operator*(const Matrix &transform) const
	{
		const Vec3 center_new = transform * GetCenter();
		const Vec3 extent_old = GetExtents();

		const Vec3 extent_new = Vec3(
			abs(transform.m00) * extent_old.x + abs(transform.m10) * extent_old.y + abs(transform.m20) * extent_old.z,
			abs(transform.m01) * extent_old.x + abs(transform.m11) * extent_old.y + abs(transform.m21) * extent_old.z,
			abs(transform.m02) * extent_old.x + abs(transform.m12) * extent_old.y + abs(transform.m22) * extent_old.z);

		return {center_new - extent_new, center_new + extent_new};
	}

	Intersection BoundingBox::Intersects(const Vec3 &point) const
	{
		if (point.x < m_Min.x || point.x > m_Max.x || point.y < m_Min.y || point.y > m_Max.y || point.z < m_Min.z || point.z > m_Max.z)
			return Intersection::Outside;

		return Intersection::Inside;
	}


	Intersection BoundingBox::Intersects(const BoundingBox &box) const
	{
		if (box.m_Max.x < m_Min.x || box.m_Min.x > m_Max.x || box.m_Max.y < m_Min.y || box.m_Min.y > m_Max.y || box.m_Max.z < m_Min.z || box.m_Min.z > m_Max.z)
			return Intersection::Outside;

		if (box.m_Min.x < m_Min.x || box.m_Max.x > m_Max.x || box.m_Min.y < m_Min.y || box.m_Max.y > m_Max.y || box.m_Min.z < m_Min.z || box.m_Max.z > m_Max.z)
			return Intersection::Intersects;

		return Intersection::Inside;
	}

	bool BoundingBox::Contains(const Vec3 &point) const
	{
		return (point.x >= m_Min.x && point.x <= m_Max.x) &&
			   (point.y >= m_Min.y && point.y <= m_Max.y) &&
			   (point.z >= m_Min.z && point.z <= m_Max.z);
	}

	void BoundingBox::Merge(const BoundingBox &box)
	{
		m_Min.x = std::min(m_Min.x, box.m_Min.x);
		m_Min.y = std::min(m_Min.y, box.m_Min.y);
		m_Min.z = std::min(m_Min.z, box.m_Min.z);

		m_Max.x = std::max(m_Max.x, box.m_Max.x);
		m_Max.y = std::max(m_Max.y, box.m_Max.y);
		m_Max.z = std::max(m_Max.z, box.m_Max.z);
	}

	Vec3 BoundingBox::GetClosestPoint(const Vec3 &point) const
	{
		return {std::max(m_Min.x, std::min(point.x, m_Max.x)), std::max(m_Min.y, std::min(point.y, m_Max.y)),std::max(m_Min.z, std::min(point.z, m_Max.z))};
	}

	void BoundingBox::GetCorners(std::array<Vec3, 8> *corners) const
	{
		*corners = {m_Min,
					Vec3(m_Max.x, m_Min.y, m_Min.z), Vec3(m_Min.x, m_Max.y, m_Min.z),
					Vec3(m_Min.x, m_Min.y, m_Max.z), Vec3(m_Min.x, m_Max.y, m_Max.z),
					Vec3(m_Max.x, m_Min.y, m_Max.z), Vec3(m_Max.x, m_Max.y, m_Min.z),
					m_Max };
	}

	Vec3 BoundingBox::GetCenter() const
	{
		return (m_Max + m_Min) * 0.5f;
	}

	Vec3 BoundingBox::GetSize() const
	{
		return m_Max - m_Min;
	}

	Vec3 BoundingBox::GetExtents() const
	{
		return (m_Max - m_Min) * 0.5f;
	}

	float BoundingBox::GetVolume() const
	{
		Vec3 size = GetSize(); return size.x * size.y * size.z;
	}

	const Vec3 & BoundingBox::GetMin() const
	{
		return m_Min;
	}

	const Vec3 & BoundingBox::GetMax() const
	{
		return m_Max;
	}

	Vec3 BoundingBox::Size() const
	{
		return Max - Min;
	}

	Vec3 BoundingBox::Center() const
	{
		return Min + Size() * 0.5f;
	}
}

/// -----------------------------------------------------
