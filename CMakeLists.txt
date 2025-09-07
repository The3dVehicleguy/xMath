CMAKE_MINIMUM_REQUIRED(VERSION 3.8...4.0)

# --------------------------------
# Global Setup
# --------------------------------
SET(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/dependency/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")
SET(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE)
SET(CMAKE_SYSTEM_NAME "Windows" CACHE STRING "")
SET(CMAKE_SYSTEM_PROCESSOR "x64" CACHE STRING "")
SET(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "")
SET(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION "10.0" CACHE STRING "")
SET(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
SET(VCPKG_INSTALL_OPTIONS --no-print-usage)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
SET_PROPERTY(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT xMath)
#SET_PROPERTY(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "_CMakePredefinedTargets")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

SET(BIN_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_CFG_INTDIR})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/")

# --------------------------------
# Tracy Profiler Setup
# --------------------------------
OPTION(TRACY_ENABLE "Enable Tracy profiler" ON)
OPTION(TRACY_ON_DEMAND "Enable Tracy on-demand profiling" OFF)
OPTION(TRACY_NO_EXIT "Enable Tracy profiler even without exit" OFF)
OPTION(TRACY_NO_BROADCAST "Disable Tracy broadcast" OFF)

# Add Tracy-specific compile definitions
IF(TRACY_ENABLE)
    ADD_COMPILE_DEFINITIONS(TRACY_ENABLE)
    IF(TRACY_ON_DEMAND)
        ADD_COMPILE_DEFINITIONS(TRACY_ON_DEMAND)
    ENDIF()
    IF(TRACY_NO_EXIT)
        ADD_COMPILE_DEFINITIONS(TRACY_NO_EXIT)
    ENDIF()
    IF(TRACY_NO_BROADCAST)
        ADD_COMPILE_DEFINITIONS(TRACY_NO_BROADCAST)
    ENDIF()
ENDIF()

# --------------------------------
# BUILD SYSTEM
# --------------------------------
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS}
    /EHsc
	/Zc:preprocessor
    -DNOMINMAX
    -D_USE_MATH_DEFINES "
)
ADD_DEFINITIONS(
    -D_CRT_SECURE_NO_WARNINGS
    -DCMAKE_GENERATOR_PLATFORM=x64
)
MESSAGE(VCPKG_ROOT = " ${CMAKE_TOOLCHAIN_FILE} ")

# --------------------------------

IF(CMAKE_GENERATOR MATCHES "Visual Studio")
    ADD_COMPILE_OPTIONS(${COMMON_COMPILE_OPTIONS})
    SET(COMPILE_FLAGS ${COMMON_COMPILE_FLAGS})
    SET(CMAKE_CXX_SCAN_FOR_MODULES OFF)
    SET(CMAKE_INCREMENTAL_LINKING ON)
    SET(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    ADD_COMPILE_DEFINITIONS(${COMMON_COMPILE_DEF})
    MESSAGE("Added Compile Definitions: ${COMMON_COMPILE_DEF}")
ENDIF()

# --------------------------------
# REQUIRE BUILDS TO BE OUTSIDE OF SOURCE TREE.
# --------------------------------
FILE(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)

IF(EXISTS "${LOC_PATH}")
    MESSAGE(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please use a build directory instead.")
ENDIF()

# SET DEFAULT BUILD TYPES
IF(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
ENDIF()

# --------------------------------
# xMath Project Setup
# --------------------------------
PROJECT(xMath
    VERSION 1.0.0
    DESCRIPTION "A custom math library."
    LANGUAGES CXX C
    HOMEPAGE_URL "https://github.com/The3dVehicleguy/xMath"
)

# Enable CTest/CTest integration at the top-level so tests added in subdirectories
# are discoverable from the build root via `ctest`.
INCLUDE(CTest)
IF(BUILD_TESTING)
    ENABLE_TESTING()
ENDIF()

MESSAGE(STATUS "=================================================")
MESSAGE(STATUS "Beginning project generation for xMath")
MESSAGE(STATUS "=================================================")

# --------------------------------
# PACKAGES VCPKG
# --------------------------------
FIND_PACKAGE(tracy				    CONFIG REQUIRED)
FIND_PACKAGE(Stb                           REQUIRED)
FIND_PACKAGE(Doxygen                          QUIET)

# --------------------------------
# PROJECT OPTIONS
# --------------------------------

OPTION(BUILD_DOXYGEN "Build Doxygen documentation" OFF)
IF(BUILD_DOXYGEN)
    INCLUDE(cmake/doxygen.cmake)
ENDIF()

# --------------------------------
# Catch2
# --------------------------------
ADD_SUBDIRECTORY(dependency/Catch2)

# --------------------------------
# TESTS
# --------------------------------
ADD_SUBDIRECTORY(tests)

# --------------------------------
# ADD xMATH LIBRARY
# --------------------------------
INCLUDE(cmake/math.cmake)

# --------------------------------

IF(TARGET WIN32)
	FOREACH(TARGET IN ITEMS xMath
	        PUBLIC
	            $<$<CONFIG:Debug>:XMATH_WIN_DEBUG>
	            $<$<CONFIG:Release>:XMATH_WIN_RELEASE>
	            UNICODE
	            _UNICODE
	            _CRT_SECURE_NO_WARNINGS
	    )
	ENDFOREACH()
ELSEIF (TARGET UNIX)
	FOREACH(TARGET IN ITEMS xMath
			PUBLIC
				$<$<CONFIG:Debug>:XMATH_UINX_DEBUG>
				$<$<CONFIG:Release>:XMATH_UINX_RELEASE>
				UNICODE
				_UNICODE
				_CRT_SECURE_NO_WARNINGS
		)
	ENDFOREACH()
ELSEIF (TARGET APPLE)
	FOREACH(TARGET IN ITEMS xMath
			PUBLIC
				$<$<CONFIG:Debug>:XMATH_MAC_DEBUG>
				$<$<CONFIG:Release>:XMATH_MAC_RELEASE>
				UNICODE
				_UNICODE
				_CRT_SECURE_NO_WARNINGS
		)
	ENDFOREACH()
ENDIF()

SET_PROPERTY(TARGET Catch2 Catch2WithMain PROPERTY FOLDER "Dependency/Catch2")

FOREACH(TARGET IN ITEMS MathTests Catch2 Catch2WithMain xMath)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    )
ENDFOREACH()

# --------------------------------
FOREACH(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin/${OUTPUTCONFIG})
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin/${OUTPUTCONFIG})
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin/${OUTPUTCONFIG})
ENDFOREACH(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
