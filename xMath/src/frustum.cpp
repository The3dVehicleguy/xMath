﻿/**
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
* frustum.cpp
* -------------------------------------------------------
* Created: 6/9/2025
* -------------------------------------------------------
*/
#include <cassert>
#include <vector.h>
#include <xmath.hpp>
#include <xMath/includes/frustum.h>

/// -------------------------------------------------------------

namespace xMath
{
	Frustum::Frustum(const Matrix &view, const Matrix &projection)
	{
	    const Matrix view_projection = view * projection;

	    // Near Plane
	    m_planes[0].normal.x = view_projection.m03 + view_projection.m02;
	    m_planes[0].normal.y = view_projection.m13 + view_projection.m12;
	    m_planes[0].normal.z = view_projection.m23 + view_projection.m22;
	    m_planes[0].d = view_projection.m33 + view_projection.m32;
	    m_planes[0].Normalize();

	    // Far Plane
	    m_planes[1].normal.x = view_projection.m03 - view_projection.m02;
	    m_planes[1].normal.y = view_projection.m13 - view_projection.m12;
	    m_planes[1].normal.z = view_projection.m23 - view_projection.m22;
	    m_planes[1].d = view_projection.m33 - view_projection.m32;
	    m_planes[1].Normalize();

	    // Left Plane
	    m_planes[2].normal.x = view_projection.m03 + view_projection.m00;
	    m_planes[2].normal.y = view_projection.m13 + view_projection.m10;
	    m_planes[2].normal.z = view_projection.m23 + view_projection.m20;
	    m_planes[2].d = view_projection.m33 + view_projection.m30;
	    m_planes[2].Normalize();

	    // Right Plane
	    m_planes[3].normal.x = view_projection.m03 - view_projection.m00;
	    m_planes[3].normal.y = view_projection.m13 - view_projection.m10;
	    m_planes[3].normal.z = view_projection.m23 - view_projection.m20;
	    m_planes[3].d = view_projection.m33 - view_projection.m30;
	    m_planes[3].Normalize();

	    // Top Plane
	    m_planes[4].normal.x = view_projection.m03 - view_projection.m01;
	    m_planes[4].normal.y = view_projection.m13 - view_projection.m11;
	    m_planes[4].normal.z = view_projection.m23 - view_projection.m21;
	    m_planes[4].d = view_projection.m33 - view_projection.m31;
	    m_planes[4].Normalize();

	    // Bottom Plane
	    m_planes[5].normal.x = view_projection.m03 + view_projection.m01;
	    m_planes[5].normal.y = view_projection.m13 + view_projection.m11;
	    m_planes[5].normal.z = view_projection.m23 + view_projection.m21;
	    m_planes[5].d = view_projection.m33 + view_projection.m31;
	    m_planes[5].Normalize();
	}

	bool Frustum::IsVisible(const Vec3 &center, const Vec3 &extent, bool ignore_depth /*= false*/) const
	{
	    return CheckCube(center, extent, ignore_depth) != Intersection::Outside;
	}

	Intersection Frustum::CheckCube(const Vec3 &center, const Vec3 &extent, float ignore_depth) const
	{
	    assert(!center.IsNaN() && !extent.IsNaN());

	    bool intersects = false;

	    for (size_t i = 0; i < 6; i++)
	    {
	        if (ignore_depth && (i == 0 || i == 1))
	            continue;

	        const Plane &plane = m_planes[i];
	        const Vec3 normal_abs = plane.normal.Abs();

	        float d = Dot(plane.normal, center) + plane.d;
	        float r = Dot(normal_abs, extent);

	        if (d + r < 0.0f)
	            return Intersection::Outside;

	        if (d - r < 0.0f)
	            intersects = true;
	    }

	    return intersects ? Intersection::Intersects : Intersection::Inside;
	}

	Intersection Frustum::CheckSphere(const Vec3 &center, float radius, float ignore_depth) const
	{
	    assert(!center.IsNaN() && radius > 0.0f);

	    // calculate our distances to each of the planes
	    for (size_t i = 0; i < 6; i++)
	    {
	        // skip near and far plane checks if depth is to be ignored
	        if (ignore_depth && (i == 0 || i == 1))
	            continue;

	        const auto &plane = m_planes[i];

	        // find the distance to this plane
	        float distance = xMath::Dot(plane.normal, center) + plane.d;

	        // if this distance is < -sphere.radius, we are outside
	        if (distance < -radius)
	            return Intersection::Outside;

	        // else if the distance is between +- radius, then we intersect
	        if (static_cast<float>(abs(distance)) < radius)
	            return Intersection::Intersects;
	    }

	    // otherwise we are fully in view
	    return Intersection::Inside;
	}
}

/// -------------------------------------------------------------
