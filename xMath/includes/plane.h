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
* plane.h
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
     * @class Plane
     * @brief Represents a plane in 3D space defined by a normal vector and a distance from the origin.
     */
    class XMATH_API Plane
    {
    public:
        /**
         * @brief Default constructor. Initializes the plane with a zero normal vector and zero distance.
         */
        Plane();

        /**
         * @brief Constructs a plane from a normal vector and a distance from the origin.
         * @param normal The normal vector of the plane.
         * @param d The distance of the plane from the origin.
         */
        Plane(const Vec3& normal, float d);

        /**
         * @brief Constructs a plane from a normal vector and a point on the plane.
         * @param normal The normal vector of the plane.
         * @param point A point on the plane.
         */
        Plane(const Vec3 &normal, const Vec3 &point); // Construct from a normal vector and a point on the plane

        /**
         * @brief Constructs a plane from three vertices.
         * @param a The first vertex.
         * @param b The second vertex.
         * @param c The third vertex.
         */
        Plane(const Vec3& a, const Vec3& b, const Vec3& c); // Construct from 3 vertices

        /* @brief Destroys the plane. */
        ~Plane();

        /* @brief Normalizes the plane. */
        void Normalize();

        /**
         * @brief Normalizes the given plane.
         * @param plane The plane to normalize.
         * @return The normalized plane.
         */
        static Plane Normalize(const Plane &plane);

        /**
         * @brief Calculates the dot product of the plane and a vector.
         * @param v The vector.
         * @return The dot product.
         */
        [[nodiscard]] float Dot(const Vec3& v) const;

        /**
         * @brief Calculates the dot product of the plane and a vector.
         * @param p The plane.
         * @param v The vector.
         * @return The dot product.
         */
        static float Dot(const Plane &p, const Vec3 &v);

        /* @brief The normal vector of the plane. */
        Vec3 normal = Vec3::ZERO<float>;

        /* @brief The distance of the plane from the origin. */
        float d = 0.0f; // distance from origin
    };

}

// -------------------------------------------------------
