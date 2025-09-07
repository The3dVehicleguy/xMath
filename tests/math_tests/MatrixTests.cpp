#include <xmath.hpp>
#include <catch2/catch_all.hpp>

using namespace xMath;

TEST_CASE("Matrix identity and multiply", "[math][matrix]")
{
    auto I = Mat4::Identity();
    auto A = Mat4::Translate(Vec3(1,2,3));
    auto B = I * A;
    // Translate lives in the 4th column for this row-major matrix
    REQUIRE(B[0][3] == Catch::Approx(1.0f));
    REQUIRE(B[1][3] == Catch::Approx(2.0f));
    REQUIRE(B[2][3] == Catch::Approx(3.0f));
}
