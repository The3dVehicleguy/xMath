﻿#include <cmath>
#include <xmath.hpp>
#include <catch2/catch_all.hpp>

using namespace xMath;

TEST_CASE("Matrix Zero and Identity basics", "[math][matrix]")
{
    auto Z = Mat4::Zero();
    auto I = Mat4::Identity();

    // Zero * anything = Zero
    auto T = Mat4::Translate(Vec3(1,2,3));
    auto ZT = Z * T;
    for (int r = 0; r < 4; ++r)
	{
        for (int c = 0; c < 4; ++c)
		{
            REQUIRE(ZT[r][c] == Catch::Approx(0.0f));
        }
    }

    // Identity * T = T
    auto IT = I * T;
    for (int c = 0; c < 4; ++c)
	{
        REQUIRE(IT[3][c] == Catch::Approx(T[3][c]));
    }
}

TEST_CASE("Matrix transpose properties", "[math][matrix]")
{
    auto R = Mat4::RotationDegrees(Vec3(0, 45.0f, 0));
    auto Rt = Mat4::GetTranspose(R);
    auto Rtt = Mat4::GetTranspose(Rt);
    // Double transpose equals original
    for (int r = 0; r < 4; ++r)
	{
        for (int c = 0; c < 4; ++c)
		{
            REQUIRE(Rtt[r][c] == Catch::Approx(R[r][c]));
        }
    }
}

static bool approxIdentity(const Mat4& M, float eps = 1e-4f)
{
    for (int r = 0; r < 4; ++r)
	{
        for (int c = 0; c < 4; ++c)
		{
            const float expected = (r == c) ? 1.0f : 0.0f;
            if (!(std::fabs(M[r][c] - expected) <= eps))
				return false;
        }
    }
    return true;
}

TEST_CASE("Matrix inverse for simple transform", "[math][matrix][inverse]")
{
    auto T = Mat4::Translate(Vec3(1,2,3));
    auto S = Mat4::Scale(Vec3(2, 3, 4));
    auto M = T * S; // affine, invertible
    auto Minv = M.GetInverse();
    auto I = Mat4::Multiply(M, Minv);
    REQUIRE(approxIdentity(I));
}

TEST_CASE("Matrix inverse of singular matrix yields non-finite entries", "[math][matrix][inverse][singular]")
{
    // Construct a singular matrix (two identical rows)
    Mat4 A({
        Vec4(1, 0, 0, 0),
        Vec4(1, 0, 0, 0), // duplicate of row 0 -> determinant 0
        Vec4(0, 1, 0, 0),
        Vec4(0, 0, 1, 1)
    });
    auto Inv = A.GetInverse();
    bool anyNonFinite = false;
    for (int r = 0; r < 4; ++r)
	{
        for (int c = 0; c < 4; ++c)
		{
            if (!std::isfinite(Inv[r][c]))
            {
                anyNonFinite = true; break;
            }
        }
        if (anyNonFinite) break;
    }
    REQUIRE(anyNonFinite); // documented as undefined; characterize as non-finite
}
