#include "doctest.h"

#include "matrix.hpp"
#include "matrix_operations.hpp"

TEST_CASE("Matrix can be multiplied by scalar on the right")
{
    Matrix A(2, 3);

    for (int idx = 0; idx < A.get_size(); ++idx)
        A.at(idx) = static_cast<double>(idx + 1);

    Matrix B = A * 2.0;

    CHECK(B.get_rows() == 2);
    CHECK(B.get_cols() == 3);

    for (int idx = 0; idx < B.get_size(); ++idx)
        CHECK(B.at(idx) == doctest::Approx(2.0 * (idx + 1)));
}

TEST_CASE("Matrix can be multiplied by scalar on the left")
{
    Matrix A(2, 3);

    for (int idx = 0; idx < A.get_size(); ++idx)
        A.at(idx) = static_cast<double>(idx + 1);

    Matrix B = 2.0 * A;

    CHECK(B.get_rows() == 2);
    CHECK(B.get_cols() == 3);

    for (int idx = 0; idx < B.get_size(); ++idx)
        CHECK(B.at(idx) == doctest::Approx(2.0 * (idx + 1)));
}

TEST_CASE("Scalar multiplication does not mutate original matrix")
{
    Matrix A(2, 2);

    A.at(0) = 1.0;
    A.at(1) = -2.0;
    A.at(2) = 3.5;
    A.at(3) = -4.5;

    Matrix B = A * 10.0;

    CHECK(A.at(0) == doctest::Approx(1.0));
    CHECK(A.at(1) == doctest::Approx(-2.0));
    CHECK(A.at(2) == doctest::Approx(3.5));
    CHECK(A.at(3) == doctest::Approx(-4.5));

    CHECK(B.at(0) == doctest::Approx(10.0));
    CHECK(B.at(1) == doctest::Approx(-20.0));
    CHECK(B.at(2) == doctest::Approx(35.0));
    CHECK(B.at(3) == doctest::Approx(-45.0));
}

TEST_CASE("Scalar multiplication by zero produces zero matrix")
{
    Matrix A(2, 2);

    A.at(0) = 1.0;
    A.at(1) = -2.0;
    A.at(2) = 3.5;
    A.at(3) = -4.5;

    Matrix B = A * 0.0;

    CHECK(B.get_rows() == 2);
    CHECK(B.get_cols() == 2);

    for (int idx = 0; idx < B.get_size(); ++idx)
    {
        CHECK(B.at(idx) == doctest::Approx(0.0));
    }
}

TEST_CASE("Scalar multiplication by one copies matrix values")
{
    Matrix A(2, 2);

    A.at(0) = 1.0;
    A.at(1) = -2.0;
    A.at(2) = 3.5;
    A.at(3) = -4.5;

    Matrix B = A * 1.0;

    CHECK(B.get_shape() == A.get_shape());

    for (int idx = 0; idx < A.get_size(); ++idx)
    {
        CHECK(B.at(idx) == doctest::Approx(A.at(idx)));
    }
}
