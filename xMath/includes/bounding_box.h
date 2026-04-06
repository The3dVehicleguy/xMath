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
#include <xMath/config/math_config.h>
#include <xMath/includes/math_utils.h>
#include <xMath/includes/matrix.h>
#include <xMath/includes/vector.h>

// -----------------------------------------------------

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

		/**
		 * @brief Assigns the values of another bounding box to this bounding box
		 *
		 * @param rhs The bounding box to assign from
		 * @return Reference to this bounding box
		 */
		BoundingBox &operator=(const BoundingBox &rhs) = default;

		/**
		 * @brief Checks if two bounding boxes are equal
		 *
		 * @param other The bounding box to compare with
		 * @return True if the bounding boxes are equal, false otherwise
		 */
		bool operator==(const BoundingBox &other) const;

		/**
		 * @brief Transforms the bounding box by a given matrix
		 *
		 * @param transform The transformation matrix to apply
		 * @return A new BoundingBox representing the transformed bounding box
		 */
		BoundingBox operator*(const Matrix &transform) const;

		/**
		 * @brief Checks if the bounding box intersects with a point
		 *
		 * @param point The point to check for intersection
		 * @return Intersection result indicating the type of intersection
		 */
		[[nodiscard]] Intersection Intersects(const Vec3 &point) const;

		/**
		 * @brief Checks if the bounding box intersects with another bounding box
		 *
		 * @param box The bounding box to check for intersection
		 * @return Intersection result indicating the type of intersection
		 */
		[[nodiscard]] Intersection Intersects(const BoundingBox &box) const;

		/**
		 * @brief Checks if a point is contained within the bounding box
		 *
		 * @param point The point to check for containment
		 * @return True if the point is inside the bounding box, false otherwise
		 */
		[[nodiscard]] bool Contains(const Vec3 &point) const;

		/**
		 * @brief Merges the current bounding box with another bounding box
		 *
		 * @param box The bounding box to merge with
		 */
		void Merge(const BoundingBox &box);

		/**
		 * @brief Calculates the closest point on the bounding box to a given point
		 *
		 * @param point The point to find the closest point to
		 * @return Vec3 representing the closest point on the bounding box
		 */
		[[nodiscard]] Vec3 GetClosestPoint(const Vec3 &point) const;

		/**
		 * @brief Retrieves the eight corner points of the bounding box
		 *
		 * @param corners Pointer to an array of 8 Vec3 objects to store the corner points
		 */
		void GetCorners(std::array<Vec3, 8>* corners) const;

		/**
		 * @brief Calculates the center point of the bounding box
		 *
		 * @return Vec3 representing the center point of the bounding box
		 */
		[[nodiscard]] Vec3 GetCenter() const;

		/**
		 * @brief Calculates the size (dimensions) of the bounding box
		 *
		 * @return Vec3 representing the size (width, height, depth) of the bounding box
		 */
		[[nodiscard]] Vec3 GetSize() const;

		/**
		 * @brief Calculates the extents of the bounding box
		 *
		 * @return Vec3 representing the extents (half-size) of the bounding box
		 */
		[[nodiscard]] Vec3 GetExtents() const;

		/**
		 * @brief Calculates the volume of the bounding box
		 *
		 * @return The volume of the bounding box as a float
		 */
		[[nodiscard]] float GetVolume() const;

		/**
		 * @brief Gets the minimum corner point of the bounding box
		 *
		 * @return Const reference to the minimum corner point (Vec3) of the bounding box
		 */
		[[nodiscard]] const Vec3& GetMin() const;

		/**
		 * @brief Gets the maximum corner point of the bounding box
		 *
		 * @return Const reference to the maximum corner point (Vec3) of the bounding box
		 */
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

		static const BoundingBox ZERO;		// Bounding box with zero size at the origin (Min = Max = (0,0,0))
		static const BoundingBox UNIT;		// Bounding box with size 1 centered at the origin (Min = (-0.5,-0.5,-0.5), Max = (0.5,0.5,0.5))
		static const BoundingBox INFINITE;	// Bounding box that encompasses all space (Min = (-inf,-inf,-inf), Max = (inf,inf,inf))

		// TODO: For easy usability for future use add ability to get corners.
		/*
		[[nodiscard]] Vec3 Corner() const { return ; }
		*/

		// TODO: For easy usability for future use add ability to get the top, bottom, left, right, front, and back sides.
		/*
		[[nodiscard]] Vec3 Side() const { return ; }
		*/
	private:
		Vec3 m_Min; // Minimum corner point of the bounding box
		Vec3 m_Max; // Maximum corner point of the bounding box
	};

}

// -----------------------------------------------------
