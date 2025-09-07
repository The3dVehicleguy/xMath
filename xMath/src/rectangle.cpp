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
* rectangle.cpp
* -------------------------------------------------------
* Created: 7/9/2025
* -------------------------------------------------------
*/
#include <algorithm>

#include <xMath/includes/rectangle.h>
/// -------------------------------------------------------

namespace xMath
{

    const Rectangle Rectangle::Zero(0.0f, 0.0f, 0.0f, 0.0f);


    Rectangle::Rectangle(const float x, const float y, const float width, const float height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    Rectangle::Rectangle(const Rectangle &rectangle)
    {
        x      = rectangle.x;
        y      = rectangle.y;
        width  = rectangle.width;
        height = rectangle.height;
    }

    Rectangle::~Rectangle() = default;

    bool Rectangle::operator==(const Rectangle &rhs) const
    {
        return x == rhs.x && y == rhs.y &&
               width == rhs.width && height == rhs.height;
    }

    bool Rectangle::operator!=(const Rectangle &rhs) const
    {
        return !(*this == rhs);
    }

    bool Rectangle::IsDefined() const
    {
        return width > 0.0f && height > 0.0f;
    }

    void Rectangle::Merge(const Vec2 &point)
    {
        float min_x = x;
        float min_y = y;
        float max_x = x + width;
        float max_y = y + height;

        min_x = std::min(min_x, point.x);
        min_y = std::min(min_y, point.y);
        max_x = std::max(max_x, point.x);
        max_y = std::max(max_y, point.y);

        x      = min_x;
        y      = min_y;
        width  = max_x - min_x;
        height = max_y - min_y;
    }

    bool Rectangle::Intersects(const Rectangle &other) const
    {
        return !(x + width  < other.x ||
                 other.x + other.width < x ||
                 y + height < other.y ||
                 other.y + other.height < y);
    }

    bool Rectangle::Contains(const Rectangle &other) const
    {
        return x <= other.x &&
               y <= other.y &&
               x + width  >= other.x + other.width &&
               y + height >= other.y + other.height;
    }
}

/// -------------------------------------------------------
