﻿#include <xmath.hpp>
#include <catch2/catch_all.hpp>

TEST_CASE("Vec3 normalize edge cases", "[math][vec3]")
{
    auto n0 = xMath::Utils::Normalize(xMath::Vec3(0,0,0));
    REQUIRE(n0.x == Catch::Approx(0.0f));
    REQUIRE(n0.y == Catch::Approx(0.0f));
    REQUIRE(n0.z == Catch::Approx(0.0f));
}

TEST_CASE("Vec3 multiply by matrix treats w=1 for Vec3 overload", "[math][vec3][matrix]")
{
    auto T = xMath::Mat4::Translate(xMath::Vec3(5, -2, 3));
    xMath::Vec3 p(1,2,3);
    // Using mat * Vec3 should promote to Vec4 with w=1, translating the point
    auto r = T * p;
    REQUIRE(r.x == Catch::Approx(1+5));
    REQUIRE(r.y == Catch::Approx(2-2));
    REQUIRE(r.z == Catch::Approx(3+3));
    REQUIRE(r.w == Catch::Approx(1.0f));
}
