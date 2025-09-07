# --------------------------------
# Math Tests
# --------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

MESSAGE(STATUS "=================================================")
MESSAGE(STATUS "Generating Math Unit Tests")

FILE(GLOB MATH_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/math_tests/*.cpp
)

ADD_EXECUTABLE(MathTests
    ${MATH_TEST_SOURCES}
)

TARGET_INCLUDE_DIRECTORIES(MathTests PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
    ${CMAKE_SOURCE_DIR}/dependency
)

TARGET_LINK_LIBRARIES(MathTests PRIVATE
    Catch2::Catch2WithMain
    xMath
)

IF(MSVC)
    TARGET_COMPILE_OPTIONS(MathTests PRIVATE /MP /W4 /utf-8)
ELSE()
    TARGET_COMPILE_OPTIONS(MathTests PRIVATE -Wall -Wextra -Wpedantic)
ENDIF()

# Disable engine logging; profiling off by omission
TARGET_COMPILE_DEFINITIONS(MathTests PRIVATE XMATH_NO_LOGGING ZoneScoped=)

INCLUDE(Catch)
catch_discover_tests(MathTests)
