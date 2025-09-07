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
* gradients.h
* -------------------------------------------------------
* Created: 14/7/2025
* -------------------------------------------------------
*/
#pragma once
#include <cstdint>
#include <initializer_list>
#include <math_config.h>
#include <vector>
#include <xMath/includes/colors.h>

/// -----------------------------------------------------

namespace xMath
{

	/**
	 * @brief Multicolor gradient system for smooth color transitions
	 *
	 * The Gradient class provides a flexible system for creating smooth color transitions
	 * between multiple color points (keys) along a normalized parameter space [0.0, 1.0].
	 * It supports both linear and angular gradients with customizable interpolation.
	 *
	 * Key features:
	 * - Multiple color stops with independent positioning
	 * - Linear interpolation between adjacent color keys
	 * - Angular gradient support with degree-based rotation
	 * - Efficient evaluation for real-time rendering
	 * - Hash-based comparison for caching and optimization
	 *
	 * Common use cases:
	 * - UI background gradients
	 * - Material property transitions
	 * - Terrain height-based coloring
	 * - Particle system color animation
	 * - Data visualization color mapping
	 *
	 * @note - Color keys should be ordered by position for optimal performance,
	 *       though the class will handle unordered keys correctly
	 */
	class XMATH_API Gradient
    {
    public:
    	/**
    	 * @brief A single color key within the gradient
    	 *
    	 * Represents a color value at a specific position along the gradient.
    	 * Multiple keys are interpolated to create smooth color transitions.
    	 */
        struct Key
        {
			Color value{};   ///< Color value at this key position
            float position{}; ///< Position along gradient [0.0, 1.0] (values outside range are valid)

			/**
			 * @brief Calculates hash value for this gradient key
			 *
			 * Combines the color hash and position to create a unique identifier
			 * for this key. Used for gradient comparison and caching.
			 *
			 * @return Hash value representing this key's state
			 */

            /*
            [[nodiscard]] size_t GetHash() const
			{
				size_t hash = value.GetHash();
                hash ^= std::hash<float>{}(position) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
				return hash;
			}
			*/
        };

		/**
		 * @brief Default constructor creating an empty gradient
		 *
		 * Creates a gradient with no color keys and 0-degree  rotation.
		 * An empty gradient will return a default color when evaluated.
		 */
        Gradient();

        /**
         * @brief Constructs a gradient from an initializer list of keys
         *
         * @param list Initializer list of gradient keys
         * @param degrees Rotation angle for angular gradients [0.0, 360.0) (default: 0)
         *
         * @example
         * Gradient redToBlue = {{Color::Red(), 0.0f}, {Color::Blue(), 1.0f}};
         * Gradient diagonal = {{Color::Red(), 0.0f}, {Color::Blue(), 1.0f}}, 45.0f};
         */
		Gradient(std::initializer_list<Key> list, float degrees = 0);

		/**
		 * @brief Constructs a gradient from a vector of keys
		 *
		 * @param list Vector of gradient keys
		 * @param degrees Rotation angle for angular gradients [0.0, 360.0) (default: 0)
		 */
        explicit Gradient(const std::vector<Key>& list, float degrees = 0);

		/**
		 * @brief Gets the current rotation angle of the gradient
		 *
		 * @return Rotation angle in degrees [0.0, 360.0)
		 */
		[[nodiscard]] float GetDegrees() const;

        /**
		 * @brief Sets the rotation angle for angular gradients
		 *
		 * @param d New rotation angle in degrees [0.0, 360.0)
		 *
		 * @note - Values outside [0, 360) are valid but may produce unexpected results
		 */
		void SetDegrees(float d);

        /**
		 * @brief Gets the number of color keys in the gradient
		 *
		 * @return Number of gradient keys
		 */
		[[nodiscard]] uint32_t GetNumKeys() const;

        /**
		 * @brief Gets read-only access to all gradient keys
		 *
		 * @return Const reference to the vector of gradient keys
		 */
		[[nodiscard]] const std::vector<Key>& GetKeys() const;

        /**
		 * @brief Gets read-only access to a specific gradient key
		 *
		 * @param index Index of the key to retrieve
		 * @return Const reference to the gradient key at the specified index
		 *
		 * @warning No bounds checking is performed. Index must be valid.
		 */
        [[nodiscard]] const Key& GetKeyAt(uint32_t index) const;

        /**
         * @brief Gets mutable access to a specific gradient key
         *
         * @param index Index of the key to retrieve
         * @return Mutable reference to the gradient key at the specified index
         *
         * @warning No bounds checking is performed. Index must be valid.
         */
		Key& GetKeyAt(uint32_t index);

        /**
		 * @brief Evaluates the gradient color at a specific position
		 *
		 * Performs linear interpolation between adjacent gradient keys to determine
		 * the color at the specified position. If the position falls outside the
		 * range of defined keys, returns the color of the nearest edge key.
		 *
		 * @param position Position along the gradient [0.0, 1.0]
		 * @return Interpolated color at the specified position
		 *
		 * @note - Positions outside [0.0, 1.0] are clamped to the nearest edge key
		 * @note - If no keys exist, returns a default-constructed Color
		 * @note - If only one key exists, returns that key's color regardless of position
		 */
        [[nodiscard]] Color Evaluate(float position) const;

		/**
		 * @brief Removes all color keys from the gradient
		 *
		 * After calling this method, the gradient will be empty and
		 * Evaluate() will return a default color.
		 */
		void Clear();

		/**
		 * @brief Adds a new color key to the gradient
		 *
		 * @param key The gradient key to add
		 *
		 * @note - Keys are not automatically sorted by position. For optimal
		 *       performance, add keys in order of increasing position.
		 */
		void AddKey(const Key& key);

		/**
		 * @brief Adds a new color key to the gradient with separate parameters
		 *
		 * @param position Position along the gradient [0.0, 1.0]
		 * @param color Color value at this position
		 *
		 * @note - Keys are not automatically sorted by position. For optimal
		 *       performance, add keys in order of increasing position.
		 */
		void AddKey(float position, const Color& color);

		/**
		 * @brief Removes a gradient key at the specified index
		 *
		 * @param index Index of the key to remove
		 *
		 * @note - If index is out of bounds, the operation is silently ignored
		 */
		void RemoveKeyAt(uint32_t index);

		/**
		 * @brief Calculates hash value with custom rotation angle
		 *
		 * @param d Custom rotation angle for hash calculation
		 * @return Hash value representing the gradient state with specified rotation
		 */
        [[nodiscard]] size_t GetHash(float d) const;

        /**
         * @brief Calculates hash value for the current gradient state
         *
         * @return Hash value representing the gradient's current state
         *
         * @note - Hash includes all keys and the current rotation angle
         */
        [[nodiscard]] size_t GetHash() const;

		/**
		 * @brief Equality comparison operator
		 *
		 * @param rhs Gradient to compare against
		 * @return true if gradients have identical hash values, false otherwise
		 *
		 * @note - Uses hash-based comparison for performance. Hash collisions
		 *       are theoretically possible but extremely unlikely.
		 */
		bool operator==(const Gradient& rhs) const;

        /**
		 * @brief Inequality comparison operator
		 *
		 * @param rhs Gradient to compare against
		 * @return true if gradients have different hash values, false otherwise
		 */
		bool operator!=(const Gradient& rhs) const;

    private:
        std::vector<Key> keys{}; ///< Collection of gradient color keys
		float degrees = 0.0f;    ///< Rotation angle for angular gradients in degrees
    };

}

/// -------------------------------------------------------
