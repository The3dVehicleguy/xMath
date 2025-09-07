#include <limits>
#include <catch2/catch_all.hpp>
// Pull in epsilon explicitly and umbrella for aliases
#include <xmath.hpp>

TEST_CASE("epsilon<T>() returns std::numeric_limits<T>::epsilon", "[math][epsilon]")
{
    REQUIRE(xMath::Utils::epsilon<float>() == std::numeric_limits<float>::epsilon());
    REQUIRE(xMath::Utils::epsilon<double>() == std::numeric_limits<double>::epsilon());
}

TEST_CASE("epsilonEqual boundary behavior", "[math][epsilon]")
{
    const float eps = xMath::epsilon<float>();
    // Within epsilon
    REQUIRE(xMath::Utils::epsilonEqual(1.0f + eps * 0.5f, 1.0f, eps));
    // Outside epsilon
    REQUIRE_FALSE(xMath::Utils::epsilonEqual(1.0f + eps * 2.0f, 1.0f, eps));
    // Symmetry
    REQUIRE(xMath::Utils::epsilonEqual(2.0f, 2.0f + eps * 0.9f, eps));
}
