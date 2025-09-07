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
* projection.h
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
     * @brief Creates a perspective projection matrix with field of view in radians.
     *
     * This function generates a perspective projection matrix that transforms 3D coordinates
     * from view space (camera space) to clip space. The matrix implements a standard
     * perspective projection with a symmetric frustum defined by field of view and aspect ratio.
     *
     *
     * @param fovyRadians The vertical field of view angle in radians.
     * @param width The width of the viewport or frustum.
     * @param height The height of the viewport or frustum.
     * @param zNear The distance to the near clipping plane. Must be positive.
     * @param zFar The distance to the far clipping plane. Must be positive and greater than zNear.
     * @return Mat4 A 4x4 perspective projection matrix suitable for use in graphics pipelines.
     *
     * @note - The Y-axis is inverted (negative scale) to match common graphics coordinate systems.
     * @note - Objects closer than the near plane or farther than the far plane will be clipped.
     *
     * @warning Ensure zNear and zFar are positive and zNear < zFar to avoid degenerate matrices.
     * @warning If height is zero, aspect ratio defaults to 1.0 to avoid division by zero.
     * @code
     * float fovy = Utils::ToRadians(60.0f); // 60 degrees in radians
     * Mat4 projection = Math::PerspectiveFov(fovy, 800.0f, 600.0f, 0.1f, 1000.0f);
     * @endcode
     */
    XMATH_API Mat4 PerspectiveFov(float fovyRadians, float width, float height, float zNear, float zFar);

    /**
     * @brief Creates a perspective projection matrix with field of view in radians.
     *
     * This function generates a perspective projection matrix that transforms 3D coordinates
     * from view space (camera space) to clip space. The matrix implements a standard
     * perspective projection with a symmetric frustum defined by field of view and aspect ratio.
     *
     * @param fovyRadians The vertical field of view angle in radians.
     * @param aspect The aspect ratio of the viewport (width / height). Must be positive.
     * @param zNear The distance to the near clipping plane. Must be positive.
     * @param zFar The distance to the far clipping plane. Must be positive and greater than zNear.
     * @return Mat4 A 4x4 perspective projection matrix suitable for use in graphics pipelines.
     *
     * @note - The Y-axis is inverted (negative scale) to match common graphics coordinate systems.
     * @note - Objects closer than the near plane or farther than the far plane will be clipped.
     *
     * @warning Ensure zNear and zFar are positive and zNear < zFar to avoid degenerate matrices.
     * @warning If aspect is zero, it defaults to 1.0 to avoid division by zero.
     *
     * @code
     * float fovy = Utils::ToRadians(60.0f); // 60 degrees in radians
     * Mat4 projection = Math::Perspective(fovy, 1.777f, 0.1f, 1000.0f);
     * @endcode
     */
    XMATH_API Mat4 Perspective(float fovyRadians, float aspect, float zNear, float zFar);

    /**
     * @brief Creates an orthographic projection matrix.
     *
     * This function generates an orthographic projection matrix that transforms 3D coordinates
     * from view space (camera space) to clip space. The matrix implements a standard
     * orthographic projection with a symmetric frustum defined by left, right, bottom, top, near, and far planes.
     *
     * @param left
     * @param right
     * @param bottom
     * @param top
     * @param zNear
     * @param zFar
     * @return Mat4 A 4x4 orthographic projection matrix suitable for 2D rendering or technical drawing.
     *
     * @note - The coordinate system is right-handed with Y pointing up.
     * @note - Unlike perspective projection, parallel lines remain parallel after transformation.
     *
     * @warning Ensure right > left, top > bottom, and zFar != zNear to avoid degenerate matrices.
     * @warning If any of the dimensions (left, right, bottom, top) are zero, the resulting matrix will be degenerate.
     *
     * @code
     * Mat4 ortho = Math::Ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
     * @endcode
     */
    XMATH_API Mat4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);

    /**
     * @brief Creates a look-at matrix for camera transformations.
     *
     * This function generates a view matrix that transforms world coordinates
     * into camera space, effectively positioning and orienting the camera in 3D space.
     *
     * @param eye
     * @param center
     * @param up
     * @return Mat4 A 4x4 look-at matrix that can be used to transform world coordinates to camera space.
     *
     * @note - The camera is positioned at 'eye', looking towards 'center', with 'up' defining the camera's up direction.
     * @note - The resulting matrix is right-handed, meaning the camera's forward direction is negative Z.
     *
     * @warning Ensure 'up' is not parallel to the forward direction (eye to center) to avoid singularities.
     * @code
     * Vec3 eye(0.0f, 0.0f, 5.0f);		// Camera position
     * Vec3 center(0.0f, 0.0f, 0.0f);	// Point the camera is looking at
     * Vec3 up(0.0f, 1.0f, 0.0f);		// Camera's up direction
     * Mat4 viewMatrix = Math::LookAt(eye, center, up);
     * @endcode
     */
    XMATH_API Mat4 LookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up);

}

/// -------------------------------------------------------
