CMAKE_MINIMUM_REQUIRED(VERSION 3.8...4.0)

# --------------------------------
# Global Setup
# --------------------------------
# Early top-level detection (works before project())
SET(XMATH_TOPLEVEL_EARLY OFF)
IF(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	SET(XMATH_TOPLEVEL_EARLY ON)
ENDIF()

# Only set a toolchain if none is provided (don’t override parent)
IF(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND XMATH_TOPLEVEL_EARLY)
	IF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependency/vcpkg/scripts/buildsystems/vcpkg.cmake")
		SET(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/dependency/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)
	ENDIF()
ENDIF()

SET(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE)
SET(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
SET(VCPKG_INSTALL_OPTIONS --no-print-usage)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

SET(BIN_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_CFG_INTDIR})

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
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS}
   /EHsc
   /Zc:preprocessor
   -DNOMINMAX
   -D_USE_MATH_DEFINES"
)
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -DCMAKE_GENERATOR_PLATFORM=x64)
MESSAGE(VCPKG_ROOT = " ${CMAKE_TOOLCHAIN_FILE} ")

# --------------------------------

IF(CMAKE_GENERATOR MATCHES "Visual Studio")
	ADD_COMPILE_OPTIONS(${COMMON_COMPILE_OPTIONS})
    SET(COMPILE_FLAGS ${COMMON_COMPILE_FLAGS})
    SET(CMAKE_CXX_SCAN_FOR_MODULES OFF)
    SET(CMAKE_INCREMENTAL_LINKING ON)
  	# Only set runtime library when top-level; let parent control this when embedded
  	# Note: you can make this configurable if needed.
  	# MultiThreadedDebugDLL is MSVC /MDd; ensure this matches your needs.
  	IF(XMATH_TOPLEVEL_EARLY)
  	  SET(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
  	ENDIF()
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

# Compute top-level status (fallback for older CMake)
IF(NOT DEFINED PROJECT_IS_TOP_LEVEL)
	SET(PROJECT_IS_TOP_LEVEL ${XMATH_TOPLEVEL_EARLY})
ENDIF()

# Only set platform-specific globals and VS startup when top-level
IF(PROJECT_IS_TOP_LEVEL)
	SET_PROPERTY(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT xMath)
	# --------------------------------
  	IF(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    	SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
  	ENDIF()
ENDIF()

# --------------------------------
# Testing and options
# --------------------------------
INCLUDE(CTest)

OPTION(XMATH_VENDOR_DEPS "Allow xMath to vendor/add_subdirectory 3rd-party deps" ${PROJECT_IS_TOP_LEVEL})
OPTION(XMATH_BUILD_TESTS "Build xMath tests" ${PROJECT_IS_TOP_LEVEL})
OPTION(XMATH_INSTALL "Generate install/export targets" ${PROJECT_IS_TOP_LEVEL})

# If parent enabled CTest globally, ensure tests are on here too.
IF(BUILD_TESTING)
	SET(XMATH_BUILD_TESTS ON CACHE BOOL "Build xMath tests" FORCE)
ENDIF()

MESSAGE(STATUS "=================================================")
MESSAGE(STATUS "Beginning project generation for xMath")
MESSAGE(STATUS "=================================================")

# --------------------------------
# Dependencies
# --------------------------------
# Tracy is optional; only check package if enabled. Don't hard-require it.
IF(TRACY_ENABLE)
	FIND_PACKAGE(tracy CONFIG QUIET)
	IF(NOT tracy_FOUND)
		MESSAGE(WARNING "Tracy requested but not found. Profiling will be disabled.")
    SET(TRACY_ENABLE OFF CACHE BOOL "Enable Tracy profiler" FORCE)
  ENDIF()
ENDIF()

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
# Catch2 (for tests only)
# --------------------------------
IF(XMATH_BUILD_TESTS)
	FIND_PACKAGE(Catch2 3 CONFIG QUIET)
	IF(NOT Catch2_FOUND AND XMATH_VENDOR_DEPS)
		IF(NOT TARGET Catch2::Catch2)
		ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/dependency/Catch2 EXCLUDE_FROM_ALL)
    	ENDIF()
  	ENDIF()
ENDIF()

# --------------------------------
# TESTS
# --------------------------------
IF(XMATH_BUILD_TESTS)
	ENABLE_TESTING()
	ADD_SUBDIRECTORY(tests)
ENDIF()

# --------------------------------
# ADD xMATH LIBRARY
# --------------------------------
INCLUDE(cmake/math.cmake)

# --------------------------------
# Platform compile definitions for xMath
# --------------------------------
## Public include dirs for build/install usage
IF(TARGET xMath)
	INCLUDE(GNUInstallDirs)
	TARGET_INCLUDE_DIRECTORIES(xMath
	  PUBLIC
	    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/xMath/includes;${CMAKE_CURRENT_SOURCE_DIR}>
	    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	)
	# Ensure no absolute source paths leak into INTERFACE includes
	SET_PROPERTY(TARGET xMath PROPERTY INTERFACE_INCLUDE_DIRECTORIES
	  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/xMath/includes;${CMAKE_CURRENT_SOURCE_DIR}>;$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
	# Provide a namespaced alias for consumers
	IF(NOT TARGET xMath::xMath)
		ADD_LIBRARY(xMath::xMath ALIAS xMath)
	ENDIF()
ENDIF()

IF(WIN32)
	FOREACH(TARGET IN ITEMS xMath)
		TARGET_COMPILE_DEFINITIONS(${TARGET} PUBLIC
		  $<$<CONFIG:Debug>:XMATH_WIN_DEBUG>
		  $<$<CONFIG:Release>:XMATH_WIN_RELEASE>
		  UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS
		)
	ENDFOREACH()
ELSEIF(UNIX)
	FOREACH(TARGET IN ITEMS xMath)
		TARGET_COMPILE_DEFINITIONS(${TARGET} PUBLIC
		  $<$<CONFIG:Debug>:XMATH_UNIX_DEBUG>
		  $<$<CONFIG:Release>:XMATH_UNIX_RELEASE>
		  UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS
		)
	ENDFOREACH()
ELSEIF(APPLE)
	FOREACH(TARGET IN ITEMS xMath)
		TARGET_COMPILE_DEFINITIONS(${TARGET} PUBLIC
		  $<$<CONFIG:Debug>:XMATH_MAC_DEBUG>
		  $<$<CONFIG:Release>:XMATH_MAC_RELEASE>
		  UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS
		)
	ENDFOREACH()
ENDIF()

# Group vendor targets only if they exist
IF(TARGET Catch2)
	SET_PROPERTY(TARGET Catch2 PROPERTY FOLDER "Dependency/Catch2")
ENDIF()

IF(TARGET Catch2WithMain)
	SET_PROPERTY(TARGET Catch2WithMain PROPERTY FOLDER "Dependency/Catch2")
ENDIF()

# --------------------------------
# Output directories (only when top-level; don’t override parent)
# --------------------------------
IF(PROJECT_IS_TOP_LEVEL)
	FOREACH(TARGET IN ITEMS MathTests Catch2 Catch2WithMain xMath)
		IF(TARGET ${TARGET})
			SET_TARGET_PROPERTIES(${TARGET} PROPERTIES
			  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
			  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
			  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
			)
		ENDIF()
	ENDFOREACH()

	FOREACH(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
		SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/bin/${OUTPUTCONFIG})
		SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/bin/${OUTPUTCONFIG})
		SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/bin/${OUTPUTCONFIG})
	ENDFOREACH()
ENDIF()

# --------------------------------
## Install/export for package consumption
# --------------------------------
IF(XMATH_INSTALL)
	INCLUDE(GNUInstallDirs)
	INCLUDE(CMakePackageConfigHelpers)

	SET(XMATH_INSTALL_CONFIG_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/xMath")

	# Install the library target and headers
	INSTALL(TARGETS xMath
	  EXPORT xMathTargets
	  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)

	INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/xMath/includes/
	        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xMath)

	# Also install configuration headers used by consumers (e.g., xMath/config/math_config.h)
	INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/xMath/config/
	        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xMath/config
	        FILES_MATCHING PATTERN "*.h")

	INSTALL(EXPORT xMathTargets
	        NAMESPACE xMath::
	        DESTINATION ${XMATH_INSTALL_CONFIG_DIR})

	# Generate Config and Version files
	SET(PACKAGE_INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}")
	# Determine if tracy should be re-exported
	SET(XMATH_WITH_TRACY OFF)
	IF(TRACY_ENABLE AND tracy_FOUND)
	  SET(XMATH_WITH_TRACY ON)
	ENDIF()

	SET(XMATH_CONFIG_IN "${CMAKE_CURRENT_BINARY_DIR}/_xmath_config.cmake.in")
	FILE(WRITE "${XMATH_CONFIG_IN}" "@PACKAGE_INIT@\n\ninclude(CMakeFindDependencyMacro)\n\n# Re-export public dependencies\nfind_dependency(Stb)\nif(@XMATH_WITH_TRACY@)\n  find_dependency(tracy)\nendif()\n\n# Imported targets\ninclude(\"${CMAKE_CURRENT_LIST_DIR}/xMathTargets.cmake\")\n\n# Convenience variables\nset(xMath_INCLUDE_DIR \"@PACKAGE_INCLUDE_INSTALL_DIR@/xMath\")\nset(xMath_NAMESPACE \"xMath::\")\n")

	CONFIGURE_PACKAGE_CONFIG_FILE(
	  "${XMATH_CONFIG_IN}"
	  ${CMAKE_CURRENT_BINARY_DIR}/xMathConfig.cmake
	  INSTALL_DESTINATION ${XMATH_INSTALL_CONFIG_DIR}
	  PATH_VARS PACKAGE_INCLUDE_INSTALL_DIR
	)

	WRITE_BASIC_PACKAGE_VERSION_FILE(
	  ${CMAKE_CURRENT_BINARY_DIR}/xMathConfigVersion.cmake
	  VERSION ${PROJECT_VERSION}
	  COMPATIBILITY SameMajorVersion
	)

  	INSTALL(FILES
  	    ${CMAKE_CURRENT_BINARY_DIR}/xMathConfig.cmake
  	    ${CMAKE_CURRENT_BINARY_DIR}/xMathConfigVersion.cmake
  	  DESTINATION ${XMATH_INSTALL_CONFIG_DIR}
  	)
ENDIF()

# --------------------------------
## Uninstall target (uses install manifest)
# --------------------------------
IF(NOT TARGET uninstall)
	SET(_XMATH_UNINSTALL_SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/xmath_uninstall.cmake")
	FILE(WRITE "${_XMATH_UNINSTALL_SCRIPT}" "if(NOT EXISTS \"${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt\")\n  message(FATAL_ERROR \"Cannot find install manifest: ${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt\")\nendif()\nfile(READ \"${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt\" _files)\nstring(REGEX REPLACE \"\\r?\\n\" \";\" _files \"${_files}\")\nforeach(_file ${_files})\n  if(EXISTS \"${_file}\" OR IS_SYMLINK \"${_file}\")\n    message(STATUS \"Removing ${_file}\")\n    file(REMOVE_RECURSE \"${_file}\")\n  endif()\nendforeach()\n")
	ADD_CUSTOM_TARGET(uninstall
	  COMMAND ${CMAKE_COMMAND} -P "${_XMATH_UNINSTALL_SCRIPT}"
	  COMMENT "Uninstalling xMath..."
	)
ENDIF()

# --------------------------------
