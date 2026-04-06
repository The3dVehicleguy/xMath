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
* sphere.h
* -------------------------------------------------------
* Created: 7/9/2025
* -------------------------------------------------------
*/
#pragma once
#include <xMath/includes/vector.h>

// -------------------------------------------------------

namespace xMath
{
    /**
     * @class Sphere
     * @brief Represents a sphere defined by a center and radius for collision detection and visibility testing in 3D graphics.
     */
    class Sphere
    {
    public:
        /**
         * @brief Default constructor for the Sphere class.
         */
        Sphere();

        /**
         * @brief Constructs a sphere with the given center and radius.
         * @param center The center of the sphere.
         * @param radius The radius of the sphere.
         */
        Sphere(const Vec3& center, const float radius);

        ~Sphere() = default;

        /**
         * @brief The center of the sphere.
         */
        Vec3 center;

        /**
         * @brief The radius of the sphere.
         */
        float radius;
    };
}

/// -------------------------------------------------------
