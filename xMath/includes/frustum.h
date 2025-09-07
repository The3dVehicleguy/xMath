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
* frustum.h
* -------------------------------------------------------
* Created: 6/9/2025
* -------------------------------------------------------
*/
#pragma once
#include <math_config.h>
#include <xMath/includes/math_utils.h>
#include <xMath/includes/matrix.h>
#include <xMath/includes/plane.h>
#include <xMath/includes/vector.h>

/// -------------------------------------------------------------

namespace xMath
{
    class XMATH_API Frustum
    {
    public:
		Frustum() = default;
        Frustum(const Matrix &view, const Matrix &projection);
        bool IsVisible(const Vec3 &center, const Vec3 &extent, bool ignore_depth) const;
		~Frustum() = default;

    private:
        [[nodiscard]] Intersection CheckCube(const Vec3 &center, const Vec3 &extent, float ignore_depth = false) const;
        [[nodiscard]] Intersection CheckSphere(const Vec3 &center, float radius, float ignore_depth = false) const;

        Plane m_planes[6];
    };

}

/// -------------------------------------------------------------
