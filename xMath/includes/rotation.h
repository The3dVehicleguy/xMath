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
* rotation.h
* -------------------------------------------------------
* Created: 13/8/2025
* -------------------------------------------------------
*/
#pragma once
#include <xMath/config/math_config.h>
#include <xMath/includes/vector.h>

/// -------------------------------------------------------

namespace xMath
{

	/**
	 * @brief Rotate around the Z-axis by a given angle in radians.
	 *
	 * @param degrees Angle in degrees to rotate around the Z-axis.
	 * @return Mat4 Rotation matrix for the Z-axis rotation.
	 *
	 * @note - This function creates a rotation matrix that rotates points around the Z-axis by the specified angle in degrees.
	 * @note - The rotation is right-handed, meaning positive angles rotate counter-clockwise when looking from the positive Z-axis towards the origin.
	 *
	 * @code
	 * Mat4 rotationMatrix = RotateZDegrees(45.0f); // Rotate 45 degrees around the X-axis
	 * @endcode
	 */
    XMATH_API Mat4 RotateZDegrees(float degrees);

    /**
     * @brief Rotate around the Z-axis by a given angle in radians, applied to a matrix.
     *
     * @param m The matrix to which the rotation will be applied.
     * @param degrees Angle in degrees to rotate around the Z-axis.
     * @return Mat4 The resulting matrix after applying the Z-axis rotation.
     *
     * @note - This function multiplies the input matrix by a rotation matrix that rotates points around the Z-axis by the specified angle in degrees.
     * @note - The rotation is right-handed, meaning positive angles rotate counter-clockwise when looking from the positive Z-axis towards the origin.
     *
     * @code
     * Mat4 originalMatrix = ...; // Some existing matrix
     * Mat4 rotatedMatrix = RotateZDegrees(originalMatrix, 45.0f); // Rotate the matrix 45 degrees around the Z-axis
     * @endcode
     */
    XMATH_API Mat4 RotateZDegrees(const Mat4 &m, float degrees);

    ///////////////////////////////////////////////////////////
    //			Euler rotations (YXZ order) in radians	     //
    ///////////////////////////////////////////////////////////

    /**
     * @brief Create a rotation matrix from Euler angles in radians.
     *
     * This function constructs a rotation matrix based on the provided Euler angles in radians.
     * The rotation is applied in the Y-X-Z order (YXZ), which is a common convention for 3D rotations.
     *
     * @param euler The Euler angles in radians, represented as a Vec3 where:
     *             - euler.x is the rotation around the X-axis,
     *             - euler.y is the rotation around the Y-axis,
     *             - euler.z is the rotation around the Z-axis.
     * @return Mat4 A 4x4 rotation matrix representing the combined rotation.
     *
     * @note - The resulting matrix can be used to transform points or vectors in 3D space by applying the rotation defined by the Euler angles.
     * @note - The angles are assumed to be in radians, so if you have angles in degrees, you should convert them to radians before calling this function.
     *
     * @code
     * Vec3 eulerRadians(0.0f, 1.57f, 0.0f); // Example Euler angles in radians
     * Mat4 rotationMatrix = RotateEulerRadians(eulerRadians); // Create rotation matrix
     * @endcode
     */
    XMATH_API Mat4 RotateEulerRadians(const Vec3 &euler);

    /**
     * @brief Create a rotation matrix from Euler angles in radians, applied to a matrix.
     *
     * This function constructs a rotation matrix based on the provided Euler angles in radians and applies it to an existing matrix.
     *
     * @param eulerDeg The Euler angles in radians, represented as a Vec3 where:
     *            - euler.x is the rotation around the X-axis,
     *            - euler.y is the rotation around the Y-axis,
     *            - euler.z is the rotation around the Z-axis.
     * @return Mat4 A 4x4 rotation matrix representing the combined rotation applied to the input matrix.
     *
     * @note - The resulting matrix can be used to transform points or vectors in 3D space by applying the rotation defined by the Euler angles.
     * @note - The angles are assumed to be in radians, so if you have angles in degrees, you should convert them to radians before calling this function.
     *
     * @code
     * Vec3 eulerRadians(0.0f, 1.57f, 0.0f); // Example Euler angles in radians
     * Mat4 originalMatrix = ...; // Some existing matrix
     * Mat4 rotatedMatrix = RotateEulerRadians(originalMatrix, eulerRadians); // Create rotation matrix and apply it to the original matrix
     * @endcode
     */
    XMATH_API Mat4 RotateEulerDegrees(const Vec3 &eulerDeg);

    /**
     * @brief Create a rotation matrix from Euler angles in radians, applied to an existing matrix.
     *
     * This function constructs a rotation matrix based on the provided Euler angles in radians and applies it to an existing matrix.
     *
     * @param m The existing matrix to which the rotation will be applied.
     * @param euler The Euler angles in radians, represented as a Vec3 where:
     *            - euler.x is the rotation around the X-axis,
     *            - euler.y is the rotation around the Y-axis,
     *            - euler.z is the rotation around the Z-axis.
     * @return Mat4 A 4x4 rotation matrix representing the combined rotation applied to the input matrix.
     *
     * @note - The resulting matrix can be used to transform points or vectors in 3D space by applying the rotation defined by the Euler angles.
     * @note - The angles are assumed to be in radians, so if you have angles in degrees, you should convert them to radians before calling this function.
     *
     * @code
     * Vec3 eulerRadians(0.0f, 1.57f, 0.0f); // Example Euler angles in radians
     * Mat4 originalMatrix = ...; // Some existing matrix
     * Mat4 rotatedMatrix = RotateEulerRadians(originalMatrix, eulerRadians); // Create rotation matrix and apply it to the original matrix
     * @endcode
     */
    XMATH_API Mat4 RotateEulerRadians(const Mat4 &m, const Vec3 &euler);

    /**
     * @brief Create a rotation matrix from Euler angles in degrees, applied to an existing matrix.
     *
     * This function constructs a rotation matrix based on the provided Euler angles in degrees and applies it to an existing matrix.
     *
     * @param m The existing matrix to which the rotation will be applied.
     * @param eulerDeg The Euler angles in degrees, represented as a Vec3 where:
     *           - euler.x is the rotation around the X-axis,
     *           - euler.y is the rotation around the Y-axis,
     *           - euler.z is the rotation around the Z-axis.
     * @return Mat4 A 4x4 rotation matrix representing the combined rotation applied to the input matrix.
     *
     * @note - The resulting matrix can be used to transform points or vectors in 3D space by applying the rotation defined by the Euler angles.
     * @note - The angles are assumed to be in degrees, so if you have angles in radians, you should convert them to degrees before calling this function.
     *
     * @code
     * Vec3 eulerDegrees(0.0f, 90.0f, 0.0f); // Example Euler angles in degrees
     * Mat4 originalMatrix = ...; // Some existing matrix
     * Mat4 rotatedMatrix = RotateEulerDegrees(originalMatrix, eulerDegrees); // Create rotation matrix and apply it to the original matrix
     * @endcode
     */
    XMATH_API Mat4 RotateEulerDegrees(const Mat4 &m, const Vec3 &eulerDeg);

    ///////////////////////////////////////////////////////////
	//		 Axis-angle rotation (right-handed), radians	 //
    ///////////////////////////////////////////////////////////

    /**
     * @brief Create a rotation matrix that rotates around a specified axis by a given angle in radians.
     *
     * This function constructs a rotation matrix that rotates points around a specified axis by the given angle in radians.
     *
     * @param axis The axis of rotation, represented as a Vec3. This vector should be normalized (unit length) for correct rotation.
     * @param angle The angle in radians by which to rotate around the specified axis.
     * @return Mat4 A 4x4 rotation matrix representing the rotation around the specified axis.
     *
     * @note - The axis of rotation should be a normalized vector (unit length) for the rotation to be correct.
     * @note - The rotation is right-handed, meaning positive angles rotate counter-clockwise when looking along the axis of rotation towards the origin.
     * @note - If the axis is not normalized, the resulting rotation may not behave as expected.
     *
     * @code
     * Vec3 rotationAxis(0.0f, 1.0f, 0.0f); // Example axis (Y-axis)
     * float rotationAngle = 1.57f; // Example angle in radians (90 degrees)
     * Mat4 rotationMatrix = RotateAxisAngleRadians(rotationAxis, rotationAngle); // Create rotation matrix
     * @endcode
     */
    XMATH_API Mat4 RotateAxisAngleRadians(const Vec3 &axis, float angle);

    /**
     * @brief Create a rotation matrix that rotates around a specified axis by a given angle in radians, applied to an existing matrix.
     *
     * This function constructs a rotation matrix that rotates points around a specified axis by the given angle in radians and applies it to an existing matrix.
     *
     * @param m The existing matrix to which the rotation will be applied.
     * @param axis The axis of rotation, represented as a Vec3. This vector should be normalized (unit length) for correct rotation.
     * @param angle The angle in radians by which to rotate around the specified axis.
     * @return Mat4 A 4x4 rotation matrix representing the combined rotation applied to the input matrix.
     *
     * @note - The axis of rotation should be a normalized vector (unit length) for the rotation to be correct.
     * @note - The rotation is right-handed, meaning positive angles rotate counter-clockwise when looking along the axis of rotation towards the origin.
     * @note - If the axis is not normalized, the resulting rotation may not behave as expected.
     *
     * @code
     * Vec3 rotationAxis(0.0f, 1.0f, 0.0f); // Example axis (Y-axis)
     * float rotationAngle = 1.57f; // Example angle in radians (90 degrees)
     * Mat4 originalMatrix = ...; // Some existing matrix
     * Mat4 rotatedMatrix = RotateAxisAngleRadians(originalMatrix, rotationAxis, rotationAngle); // Create rotation matrix and apply it to the original matrix
     * @endcode
     */
    XMATH_API Mat4 RotateAxisAngleRadians(const Mat4 &m, const Vec3 &axis, float angle);

    /**
     * @brief Create a rotation matrix that rotates around a specified axis by a given angle in degrees.
     *
     * This function constructs a rotation matrix that rotates points around a specified axis by the given angle in degrees.
     *
     * @param axis The axis of rotation, represented as a Vec3. This vector should be normalized (unit length) for correct rotation.
     * @param degrees The angle in degrees by which to rotate around the specified axis.
     * @return Mat4 A 4x4 rotation matrix representing the rotation around the specified axis.
     *
     * @note - The axis of rotation should be a normalized vector (unit length) for the rotation to be correct.
     * @note - The rotation is right-handed, meaning positive angles rotate counter-clockwise when looking along the axis of rotation towards the origin.
     *
     * @code
     * Vec3 rotationAxis(0.0f, 1.0f, 0.0f); // Example axis (Y-axis)
     * float rotationDegrees = 90.0f; // Example angle in degrees
     * Mat4 rotationMatrix = RotateAxisAngleDegrees(rotationAxis, rotationDegrees); // Create rotation matrix
     * @endcode
     */
    XMATH_API Mat4 RotateAxisAngleDegrees(const Vec3 &axis, float degrees);

    XMATH_API Mat4 AxisAngleRadians(const Vec3 &axis, float angle);

    /**
     * @brief Create a rotation matrix that rotates around a specified axis by a given angle in degrees, applied to an existing matrix.
     *
     * This function constructs a rotation matrix that rotates points around a specified axis by the given angle in degrees and applies it to an existing matrix.
     *
     * @param m The existing matrix to which the rotation will be applied.
     * @param axis The axis of rotation, represented as a Vec3. This vector should be normalized (unit length) for correct rotation.
     * @param degrees The angle in degrees by which to rotate around the specified axis.
     * @return Mat4 A 4x4 rotation matrix representing the combined rotation applied to the input matrix.
     *
     * @note - The axis of rotation should be a normalized vector (unit length) for the rotation to be correct.
     * @note - The rotation is right-handed, meaning positive angles rotate counter-clockwise when looking along the axis of rotation towards the origin.
     *
     * @code
     * Vec3 rotationAxis(0.0f, 1.0f, 0.0f); // Example axis (Y-axis)
     * float rotationDegrees = 90.0f; // Example angle in degrees
     * Mat4 originalMatrix = ...; // Some existing matrix
     * Mat4 rotatedMatrix = RotateAxisAngleDegrees(originalMatrix, rotationAxis, rotationDegrees); // Create rotation matrix and apply it to the original matrix
     * @endcode
     */
    XMATH_API Mat4 RotateAxisAngleDegrees(const Mat4 &m, const Vec3 &axis, float degrees);


    ///////////////////////////////////////////////////////////
	//			  2D rotation (Mat3 homogeneous)			 //
    ///////////////////////////////////////////////////////////

    /**
     * @brief Create a 2D rotation matrix that rotates points around the origin by a given angle in radians.
     *
     * This function constructs a 2D rotation matrix that rotates points around the origin by the specified angle in radians.
     *
     * @param radians The angle in radians by which to rotate points around the origin.
     * @return Mat3 A 3x3 rotation matrix representing the rotation in 2D space.
     *
     * @note - The rotation is right-handed, meaning positive angles rotate counter-clockwise when looking from above the 2D plane.
     * @note - The resulting matrix can be used to transform 2D points or vectors in homogeneous coordinates (x, y, 1).
     *
     * @code
     * float rotationAngle = 1.57f; // Example angle in radians (90 degrees)
     * Mat3 rotationMatrix = Rotate2D(rotationAngle); // Create 2D rotation matrix
     * @endcode
     */
    XMATH_API Mat3 Rotate2D(float radians);

    /**
     * @brief Create a 2D rotation matrix that rotates points around the origin by a given angle in radians, applied to an existing matrix.
     *
     * This function constructs a 2D rotation matrix that rotates points around the origin by the specified angle in radians and applies it to an existing matrix.
     *
     * @param m The existing matrix to which the rotation will be applied.
     * @param radians The angle in radians by which to rotate points around the origin.
     * @return Mat3 A 3x3 rotation matrix representing the combined rotation applied to the input matrix.
     *
     * @note - The rotation is right-handed, meaning positive angles rotate counter-clockwise when looking from above the 2D plane.
     * @note - The resulting matrix can be used to transform 2D points or vectors in homogeneous coordinates (x, y, 1).
     * @note - If the input matrix is not a 2D transformation matrix, the result may not behave as expected.
     *
     * @code
     * Mat3 originalMatrix = ...; // Some existing 2D transformation matrix
     * float rotationAngle = 1.57f; // Example angle in radians (90 degrees)
     * Mat3 rotatedMatrix = Rotate2D(originalMatrix, rotationAngle); // Create 2D rotation matrix and apply it to the original matrix
     * @endcode
     */
    XMATH_API Mat3 Rotate2D(const Mat3 &m, float radians);

}

/// -------------------------------------------------------

// -------------------------------------------------------
// GLM compatibility shims for rotate (axis-angle), using radians
// Signatures match glm::rotate(m, angle, axis) and glm::rotate(angle, axis)
// -------------------------------------------------------

/*
namespace glm
{
	inline ::xMath::Mat4 rotate(const ::xMath::Mat4& m, float angleRadians, const ::xMath::Vec3& axis)
	{
		return ::xMath::RotateAxisAngleRadians(m, axis, angleRadians);
	}

	inline ::xMath::Mat4 rotate(float angleRadians, const ::xMath::Vec3& axis)
	{
		return ::xMath::RotateAxisAngleRadians(axis, angleRadians);
	}
}
*/

/// -------------------------------------------------------
