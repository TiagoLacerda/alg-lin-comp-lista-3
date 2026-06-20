#include "doctest.h"

#include "matrix.hpp"

#include <stdexcept>

TEST_CASE("Matrix constructor allocates uninitialized matrix with dimensions")
{
    Matrix A(2, 3);

    CHECK(A.get_rows() == 2);
    CHECK(A.get_cols() == 3);
}

TEST_CASE("Matrix constructor rejects invalid dimensions")
{
    CHECK_THROWS_AS(Matrix(-1, 3), std::invalid_argument);
    CHECK_THROWS_AS(Matrix(3, -1), std::invalid_argument);
}

TEST_CASE("Matrix fill constructor initializes all elements")
{
    Matrix A(2, 3, 7.5);

    CHECK(A.get_rows() == 2);
    CHECK(A.get_cols() == 3);

    for (int idx = 0; idx < A.get_size(); ++idx)
    {
        CHECK(A.at(idx) == doctest::Approx(7.5));
    }
}

TEST_CASE("Matrix fill constructor rejects invalid dimensions")
{
    CHECK_THROWS_AS(Matrix(-1, 3, 1.0), std::invalid_argument);
    CHECK_THROWS_AS(Matrix(3, -1, 1.0), std::invalid_argument);
}

TEST_CASE("Matrix copy constructor performs deep copy")
{
    Matrix A(2, 3, 4.0);

    for (int idx = 0; idx < A.get_size(); ++idx)
    {
        A.at(idx) = static_cast<double>(idx + 1);
    }

    Matrix B(A);

    CHECK(B.get_shape() == A.get_shape());

    for (int idx = 0; idx < A.get_size(); ++idx)
    {
        CHECK(B.at(idx) == doctest::Approx(A.at(idx)));
    }

    B.at(0) = 99.0;

    CHECK(A.at(0) == doctest::Approx(1.0));
    CHECK(B.at(0) == doctest::Approx(99.0));
}

TEST_CASE("Matrix copy assignment performs deep copy")
{
    Matrix A(2, 3, 1.0);
    Matrix B(4, 5, 2.0);

    A = B;

    CHECK(A.get_rows() == 4);
    CHECK(A.get_cols() == 5);

    for (int idx = 0; idx < B.get_size(); ++idx)
    {
        CHECK(A.at(idx) == doctest::Approx(B.at(idx)));
    }

    A.at(0) = 42.0;

    CHECK(B.at(0) == doctest::Approx(2.0));
    CHECK(A.at(0) == doctest::Approx(42.0));
}

TEST_CASE("Matrix copy assignment handles same dimensions")
{
    Matrix A(2, 2, 1.0);
    Matrix B(2, 2, 3.0);

    A = B;

    CHECK(A.get_rows() == 2);
    CHECK(A.get_cols() == 2);

    for (int idx = 0; idx < A.get_size(); ++idx)
    {
        CHECK(A.at(idx) == doctest::Approx(3.0));
    }
}

TEST_CASE("Matrix self-assignment is safe")
{
    Matrix A(2, 3, 8.0);

    A = A;

    CHECK(A.get_rows() == 2);
    CHECK(A.get_cols() == 3);

    for (int idx = 0; idx < A.get_size(); ++idx)
    {
        CHECK(A.at(idx) == doctest::Approx(8.0));
    }
}
