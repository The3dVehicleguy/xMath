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
* gradients.cpp
* -------------------------------------------------------
* Created: 14/7/2025
* -------------------------------------------------------
*/
#include <algorithm>
#include <initializer_list>
#include <xMath/includes/gradients.h>

/// -----------------------------------------------------

namespace xMath
{
	Gradient::Gradient() = default;
	Gradient::Gradient(const std::initializer_list<Key> list, const float degrees) : keys(list), degrees(degrees) {}
	Gradient::Gradient(const std::vector<Key>& list, const float degrees) : keys(list), degrees(degrees) {}

    float Gradient::GetDegrees() const
    {
        return degrees;
    }

    void Gradient::SetDegrees(const float d)
    {
        this->degrees = d;
    }

    uint32_t Gradient::GetNumKeys() const
    {
        return static_cast<uint32_t>(keys.size());
    }

    const std::vector<Gradient::Key> & Gradient::GetKeys() const
    {
        return keys;
    }

    const Gradient::Key & Gradient::GetKeyAt(const uint32_t index) const
    {
        return keys[index];
    }

    Gradient::Key & Gradient::GetKeyAt(const uint32_t index)
    {
        return keys[index];
    }

	Color Gradient::Evaluate(const float position) const
    {
        /// Handle empty gradient
        if (keys.empty())
            return {};

        /// Handle single key gradient
        if (keys.size() == 1)
            return keys[0].value;

        /// Find the appropriate key pair for interpolation
        for (auto i = 0; std::cmp_less(i, keys.size()); i++)
        {
            if (i > 0 && keys[i - 1].position <= position && position < keys[i].position)
            {
                /// Interpolate between keys[i-1] and keys[i]
                const float left = keys[i - 1].position;
                const float right = keys[i].position;
                float t = (position - left) / (right - left);

                /// Clamp interpolation parameter to [0, 1] range for safety
                t = std::max(0.0f, std::min(1.0f, t));
                return Color::Lerp(keys[i - 1].value, keys[i].value, t);
            }
        }

        /// Position is outside the range of defined keys
		/// Return the appropriate edge color
        return position < 0 ? keys[0].value : keys.back().value;
    }

	void Gradient::Clear()
    {
        keys.clear();
    }

	void Gradient::AddKey(const Key& key)
    {
        keys.push_back(key);
    }
	void Gradient::AddKey(const float position, const Color& color)
    {
        keys.push_back({.value = color, .position = position });
    }

	void Gradient::RemoveKeyAt(const uint32_t index)
    {
        if (index < keys.size())
            keys.erase(keys.begin() + index);
    }

	size_t Gradient::GetHash(const float d) const
    {
        if (keys.empty())
            return std::hash<float>{}(d);

        size_t hash = std::hash<float>{}(d);

        /*
		for (const auto& key : keys)
		{
			hash ^= key.GetHash() + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		}
		*/

        return hash;
    }

    size_t Gradient::GetHash() const
    {
        if (keys.empty())
            return 0;

        size_t hash = std::hash<float>{}(degrees);

        /*
		for (const auto& key : keys)
		{
			hash ^= key.GetHash() + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		}
		*/

        return hash;
    }

    bool Gradient::operator==(const Gradient &rhs) const
    {
        return GetHash() == rhs.GetHash();
    }

    bool Gradient::operator!=(const Gradient &rhs) const
    {
        return !operator==(rhs);
    }

}

/// -----------------------------------------------------
