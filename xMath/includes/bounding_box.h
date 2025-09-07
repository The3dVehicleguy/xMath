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
* bounding_box.h
* -------------------------------------------------------
* Created: 14/7/2025
* -------------------------------------------------------
*/
#pragma once
#include <array>
#include <cstdint>
#include <math_config.h>
#include <xMath/includes/math_utils.h>
#include <xMath/includes/matrix.h>
#include <xMath/includes/vector.h>

/// -----------------------------------------------------

namespace xMath
{

    struct Vertex_PosTexNorTan;

	/**
	 * @brief Axis-Aligned Bounding Box (AABB) for efficient collision detection and spatial queries
	 *
	 * An BoundingBox represents a rectangular box aligned with the coordinate axes, defined by
	 * minimum and maximum corner points. This is the most efficient bounding volume for
	 * broad-phase collision detection and spatial partitioning algorithms.
	 *
	 * The BoundingBox is defined such that all points (x,y,z) within the box satisfy:
	 * Min.x <= x <= Max.x, Min.y <= y <= Max.y, Min.z <= z <= Max.z
	 *
	 * @note - For a valid AABB, Min should be component-wise less than or equal to Max
	 * @warning Empty or invalid AABBs (where Min > Max in any component) may cause
	 *          undefined behavior in some operations
	 */
    class XMATH_API BoundingBox
	{
	public:

        /**
         * @enum Side
         * @brief Enumeration for the six sides of the AABB
         *
         * Represents the six sides of the axis-aligned bounding box.
         *
         * Each side corresponds to one of the coordinate axes, allowing easy
         * identification of which side a point or another BoundingBox is relative to.
         */
        enum class Side : uint8_t
		{
            Left = 0, // Left side of the BoundingBox
            Right,    // Right side of the BoundingBox
            Top,      // Top side of the BoundingBox
            Bottom,   // Bottom side of the BoundingBox
            Front,    // Front side of the BoundingBox
            Back      // Back side of the BoundingBox
		};

		Vec3 Min; // Minimum corner point of the bounding box
		Vec3 Max; // Maximum corner point of the bounding box

		/**
		 * @brief Default constructor creating an empty AABB at origin
		 *
		 * Creates an BoundingBox with both Min and Max set to (0,0,0), representing
		 * an empty bounding box with zero volume.
		 */

        BoundingBox() : Min(0.0f), Max(0.0f) {}

        /**
		 * @brief Constructs an AABB from minimum and maximum corner points
		 *
		 * @param min The minimum corner point (should be component-wise <= max)
		 * @param max The maximum corner point (should be component-wise >= min)
		 *
		 * @note - No validation is performed to ensure min <= max. Users should
		 *       ensure proper ordering for correct behavior.
		 */
        BoundingBox(const Vec3 &min, const Vec3 &max);

        /**
         * @brief Constructs an AABB that encompasses a set of vertices
         *
         * @param vertices Pointer to an array of 3D points (Vec3)
         * @param point_count Number of points in the vertices array
         */
        BoundingBox(const Vec3 *vertices, uint32_t point_count);

        /**
         * @brief Constructs an AABB that encompasses a set of vertices with position, texture, normal, and tangent data
         *
         * @param vertices Pointer to an array of Vertex_PosTexNorTan structures
         * @param vertex_count Number of vertices in the array
         */
        BoundingBox(const Vertex_PosTexNorTan *vertices, uint32_t vertex_count);

	    ~BoundingBox() = default;

        /// -----------------------------------------------------

	    BoundingBox &operator=(const BoundingBox &rhs) = default;
        bool operator==(const BoundingBox &other) const;
        BoundingBox operator*(const Matrix &transform) const;

        // Intersection
        [[nodiscard]] Intersection Intersects(const Vec3 &point) const;
        [[nodiscard]] Intersection Intersects(const BoundingBox &box) const;
        [[nodiscard]] bool Contains(const Vec3 &point) const;

        // Modulation
        void Merge(const BoundingBox &box);

        // Edges and points on them
        [[nodiscard]] Vec3 GetClosestPoint(const Vec3 &point) const;

        void GetCorners(std::array<Vec3, 8>* corners) const;

        // Dimensions
        [[nodiscard]] Vec3 GetCenter() const;
        [[nodiscard]] Vec3 GetSize() const;
        [[nodiscard]] Vec3 GetExtents() const;
        [[nodiscard]] float GetVolume() const;
        [[nodiscard]] const Vec3& GetMin() const;
        [[nodiscard]] const Vec3& GetMax() const;


        /**
		 * @brief Calculates the size (dimensions) of the bounding box
		 *
		 * Returns the extent of the BoundingBox in each dimension as a vector.
		 * For a valid BoundingBox, all components should be non-negative.
		 *
		 * @return Vec3 containing the width, height, and depth of the bounding box
		 *
		 * @note - If Min > Max in any component, the corresponding size component will be negative
		 */
        [[nodiscard]] Vec3 Size() const;

        /**
         * @brief Calculates the center point of the bounding box
         *
         * Returns the geometric center of the BoundingBox, which is the midpoint between
         * the minimum and maximum corners.
         *
         * @return Vec3 representing the center point of the bounding box
         *
         * @note - The center is calculated as Min + (Max - Min) * 0.5, which is
         *       equivalent to (Min + Max) * 0.5 but more numerically stable
         */
        [[nodiscard]] Vec3 Center() const;

        static const BoundingBox Zero;
        static const BoundingBox Unit;
        static const BoundingBox Infinite;

        /// -----------------------------------------------------

		/// TODO: For easy usability for future use add ability to get corners.
		/*
		[[nodiscard]] Vec3 Corner() const { return ; }
		*/

		/// TODO: For easy usability for future use add ability to get the top, bottom, left, right, front, and back sides.
        /*
		[[nodiscard]] Vec3 Side() const { return ; }
		*/
    private:
        Vec3 m_min;
        Vec3 m_max;
	};

}

/// -----------------------------------------------------
