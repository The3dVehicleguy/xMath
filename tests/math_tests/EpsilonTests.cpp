#include <limits>
#include <catch2/catch_all.hpp>
// Pull in epsilon explicitly and umbrella for aliases
#include <xmath.hpp>

TEST_CASE("epsilon<T>() returns std::numeric_limits<T>::epsilon", "[math][epsilon]")
{
    REQUIRE(xMath::Utils::Epsilon<float>() == std::numeric_limits<float>::epsilon());
    REQUIRE(xMath::Utils::Epsilon<double>() == std::numeric_limits<double>::epsilon());
}

TEST_CASE("epsilonEqual boundary behavior", "[math][epsilon]")
{
    const float eps = xMath::Epsilon<float>();
    // Within epsilon
    REQUIRE(xMath::Utils::EpsilonEqual(1.0f + eps * 0.5f, 1.0f, eps));
    // Outside epsilon
    REQUIRE_FALSE(xMath::Utils::EpsilonEqual(1.0f + eps * 2.0f, 1.0f, eps));
    // Symmetry
    REQUIRE(xMath::Utils::EpsilonEqual(2.0f, 2.0f + eps * 0.9f, eps));
}
