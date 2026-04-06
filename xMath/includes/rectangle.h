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
* rectangle.h
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
     * @class Rectangle
     * @brief Represents a rectangle defined by its top-left corner and size for 2D graphics and collision detection.
     */
    class XMATH_API Rectangle
    {
    public:
        Rectangle() = default;

        /**
         * @brief Constructs a rectangle with the specified position and size.
         * @param x The x-coordinate of the top-left corner.
         * @param y The y-coordinate of the top-left corner.
         * @param width The width of the rectangle.
         * @param height The height of the rectangle.
         */
        Rectangle(float x, float y, float width, float height);

        /**
         * @brief Constructs a rectangle by copying another rectangle.
         * @param rectangle The rectangle to copy.
         */
        Rectangle(const Rectangle& rectangle);

        /**
         * @brief Destroys the rectangle.
         */
        ~Rectangle();

        /**
         * @brief Checks if two rectangles are equal.
         * @param rhs The rectangle to compare with.
         * @return True if the rectangles are equal, false otherwise.
         */
        bool operator==(const Rectangle& rhs) const;

        /**
         * @brief Checks if two rectangles are not equal.
         * @param rhs The rectangle to compare with.
         * @return True if the rectangles are not equal, false otherwise.
         */
        bool operator!=(const Rectangle& rhs) const;

        /**
         * @brief Checks if the rectangle is defined (has positive width and height).
         * @return True if the rectangle is defined, false otherwise.
         */
        [[nodiscard]] bool IsDefined() const;

        /**
         * @brief Expands the rectangle to include the specified point.
         * @param point The point to include in the rectangle.
         */
        void Merge(const Vec2& point);

        /**
         * @brief Checks if the rectangle intersects with another rectangle.
         * @param other The rectangle to check for intersection.
         * @return True if the rectangles intersect, false otherwise.
         */
        [[nodiscard]] bool Intersects(const Rectangle& other) const;

        /**
         * @brief Checks if the rectangle contains another rectangle.
         * @param other The rectangle to check for containment.
         * @return True if the rectangle contains the other rectangle, false otherwise.
         */
        [[nodiscard]] bool Contains(const Rectangle& other) const;

        // top-left + size
        float x      = 0.0f;
        float y      = 0.0f;
        float width  = 0.0f;
        float height = 0.0f;

        /**
         * @brief A static constant representing a rectangle with zero position and size. Useful as a default value or for comparisons.
         */
        static const Rectangle ZERO;
    };

}

// -------------------------------------------------------
