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
* plane.cpp
* -------------------------------------------------------
* Created: 7/9/2025
* -------------------------------------------------------
*/
#include <xmath.hpp>
#include <xMath/includes/plane.h>

/// -------------------------------------------------------

namespace xMath
{
	Plane::Plane() = default;

    Plane::Plane(const Vec3& normal, float d)
    {
        this->normal = normal;
        this->d = d;
    }

    Plane::Plane(const Vec3& normal, const Vec3& point)
    {
        this->normal = xMath::Normalize(normal);
        d = -xMath::Dot(this->normal, point);
    }

    Plane::Plane(const Vec3& a, const Vec3& b, const Vec3& c)
    {
        const Vec3 ab = b - a;
        const Vec3 ac = c - a;

        const Vec3 cross = Cross(ab, ac);
        this->normal = xMath::Normalize(cross);
        this->d = -xMath::Dot(normal, a);
    }

    Plane::~Plane() = default;

    void Plane::Normalize()
    {
        Plane result;

        result.normal = xMath::Normalize(this->normal);
        const float nominator = sqrtf(result.normal.x * result.normal.x + result.normal.y * result.normal.y + result.normal.z * result.normal.z);
        const float denominator = sqrtf(this->normal.x * this->normal.x + this->normal.y * this->normal.y + this->normal.z * this->normal.z);
        const float fentity = nominator / denominator;
        result.d = this->d * fentity;

        this->normal = result.normal;
        this->d = result.d;
    }

    Plane Plane::Normalize(const Plane& plane)
    {
        Plane newPlane = plane;
        newPlane.Normalize();
        return newPlane;
    }

    float Plane::Dot(const Vec3& v) const
    {
        return (this->normal.x * v.x) + (this->normal.y * v.y) + (this->normal.z * v.z) + this->d;
    }

    float Plane::Dot(const Plane& p, const Vec3& v)
    {
        const Plane& newPlane = p;
        return newPlane.Dot(v);
    }
}

/// -------------------------------------------------------
