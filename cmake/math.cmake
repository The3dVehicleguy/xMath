# --------------------------------
# Math Library
# --------------------------------
MESSAGE(STATUS "=================================================")
MESSAGE(STATUS "Generating Math Library (xMath)")

# Optionally enable Tracy profiling instrumentation for this library.
# Default OFF to keep the math DLL free of external profiling dependencies unless explicitly requested.
option(XMATH_WITH_TRACY "Enable Tracy profiling in xMath" OFF)

SET (PROJECT_CONFIG_FILES
	${CMAKE_SOURCE_DIR}/.clang-format
	${CMAKE_SOURCE_DIR}/.editorconfig
	${CMAKE_SOURCE_DIR}/xMath/config/resource.h
	${CMAKE_SOURCE_DIR}/xMath/config/math_config.h
)
FILE(GLOB MATH_HEADER_DIR
    ${CMAKE_SOURCE_DIR}/xMath/includes
)
FILE(GLOB MATH_HEADER_FILES
    ${CMAKE_SOURCE_DIR}/xMath/includes/*
)
FILE(GLOB MATH_SOURCE_DIR
    ${CMAKE_SOURCE_DIR}/xMath/src
)
FILE(GLOB MATH_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/xMath/src/*
)
FILE(GLOB MATH_DOCUMENTATION_FILES
	${CMAKE_SOURCE_DIR}/docs/*
)
ADD_LIBRARY(xMath
	SHARED
    ${MATH_SOURCE_FILES}
    ${MATH_HEADER_FILES}
	${PROJECT_CONFIG_FILES}
	${MATH_DOCUMENTATION_FILES}
    ${CMAKE_SOURCE_DIR}/xMath/config/xMath.rc
)

# Use project-wide C++20 standard (required for <format> etc.)
SET_TARGET_PROPERTIES(xMath PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES)

# Source groups for IDE organization
SOURCE_GROUP("Colors"
	FILES
	${MATH_SOURCE_DIR}/colors.cpp
	${MATH_HEADER_DIR}/colors.h
	${MATH_SOURCE_DIR}/gradients.cpp
	${MATH_HEADER_DIR}/gradients.h
)
SOURCE_GROUP("Core"
	FILES
	${MATH_SOURCE_DIR}/bounding_box.cpp
	${MATH_HEADER_DIR}/bounding_box.h
	${MATH_HEADER_DIR}/constants.h
	##${MATH_HEADER_DIR}/dot.h
	${MATH_HEADER_DIR}/epsilon.h
	${MATH_SOURCE_DIR}/quat.cpp
	${MATH_HEADER_DIR}/quat.h
	${MATH_HEADER_DIR}/xmath.hpp
)
SOURCE_GROUP("Documentation"
	FILES
	    ${MATH_DOCUMENTATION_FILES}
)
SOURCE_GROUP("Matrix"
	FILES
	${MATH_SOURCE_DIR}/mat2.cpp
	${MATH_HEADER_DIR}/mat2.h
	${MATH_SOURCE_DIR}/mat3.cpp
	${MATH_HEADER_DIR}/mat3.h
	${MATH_SOURCE_DIR}/mat4.cpp
	${MATH_HEADER_DIR}/mat4.h
	${MATH_SOURCE_DIR}/matrix.cpp
	${MATH_HEADER_DIR}/matrix.h
)
SOURCE_GROUP("Resource"
	FILES
	    ${CMAKE_SOURCE_DIR}/xMath/config/resource.h
		${CMAKE_SOURCE_DIR}/xMath/config/math_config.h
		${CMAKE_SOURCE_DIR}/xMath/config/version.h
		${CMAKE_SOURCE_DIR}/xMath/config/xMath.rc
)
SOURCE_GROUP("Transforms"
	FILES
	${MATH_SOURCE_DIR}/frustum.cpp
	${MATH_HEADER_DIR}/frustum.h
	${MATH_SOURCE_DIR}/projection.cpp
	${MATH_HEADER_DIR}/projection.h
	${MATH_SOURCE_DIR}/rotation.cpp
	${MATH_HEADER_DIR}/rotation.h
	${MATH_SOURCE_DIR}/scale.cpp
	${MATH_HEADER_DIR}/scale.h
	${MATH_SOURCE_DIR}/transforms.cpp
	${MATH_HEADER_DIR}/transforms.h
	${MATH_SOURCE_DIR}/translate.cpp
	${MATH_HEADER_DIR}/translate.h
)
SOURCE_GROUP("Shapes"
	FILES
	${MATH_SOURCE_DIR}/plane.cpp
	${MATH_HEADER_DIR}/plane.h
	${MATH_SOURCE_DIR}/rectangle.cpp
	${MATH_HEADER_DIR}/rectangle.h
	${MATH_SOURCE_DIR}/sphere.cpp
	${MATH_HEADER_DIR}/sphere.h
)
SOURCE_GROUP("Utilities"
	FILES
	${MATH_SOURCE_DIR}/math_utils.cpp
	${MATH_HEADER_DIR}/math_utils.h
)
SOURCE_GROUP("Vectors"
	FILES
	${MATH_HEADER_DIR}/vec2.h
	${MATH_HEADER_DIR}/vec3.h
	${MATH_HEADER_DIR}/vec4.h
	${MATH_HEADER_DIR}/vector.h
)

TARGET_COMPILE_DEFINITIONS(xMath
	PRIVATE
		UNICODE
		_UNICODE
		_CRT_SECURE_NO_WARNINGS
		$<$<CONFIG:Debug>:_CONSOLE>
		$<$<CONFIG:Debug>:_DEBUG>
		$<$<CONFIG:Debug>:XMATH_DEBUG>
		$<$<CONFIG:Release>:XMATH_RELEASE>
		XMATH_BUILD
		$<$<BOOL:${XMATH_WITH_TRACY}>:XMATH_ALLOW_TRACY>
)

TARGET_INCLUDE_DIRECTORIES(xMath
	PUBLIC
		${CMAKE_SOURCE_DIR}
		${CMAKE_SOURCE_DIR}/xMath/src
		${CMAKE_SOURCE_DIR}/xMath/includes
	PRIVATE
		${Stb_INCLUDE_DIR}
)

# Ensure consistent UTF-8 source decoding on MSVC (prevents fmt / Unicode warnings)
IF (MSVC)
	TARGET_COMPILE_OPTIONS(xMath PRIVATE /utf-8)
ENDIF()

# Set output directory
SET_TARGET_PROPERTIES(xMath PROPERTIES
    OUTPUT_NAME "xMath"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
