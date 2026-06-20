#include "doctest.h"

#include "matrix_io.hpp"

#include <fstream>
#include <cstdio>
#include <stdexcept>
#include <string>

static void write_text_file(const std::string &path, const std::string &content)
{
    std::ofstream file(path);

    file << content;
}

static bool file_exists(const std::string &path)
{
    std::ifstream file(path);

    return static_cast<bool>(file);
}

TEST_CASE("matrix_io::load reads matrix from file")
{
    const std::string path = "test_matrix_load.txt";

    write_text_file(
        path,
        "2 3\n"
        "1.0 2.0 3.0\n"
        "4.0 5.0 6.0\n");

    Matrix A = matrix_io::load(path);

    CHECK(A.get_rows() == 2);
    CHECK(A.get_cols() == 3);

    for (int idx = 0; idx < A.get_size(); ++idx)
        CHECK(A.at(idx) == doctest::Approx(static_cast<double>(idx + 1)));

    std::remove(path.c_str());
}

TEST_CASE("matrix_io::load throws when file does not exist")
{
    CHECK_THROWS_AS(
        matrix_io::load("file_that_should_not_exist.txt"),
        std::runtime_error);
}

TEST_CASE("matrix_io::load throws when dimensions cannot be read")
{
    const std::string path = "test_matrix_bad_dimensions.txt";

    write_text_file(path, "not_a_matrix\n");

    CHECK_THROWS_AS(
        matrix_io::load(path),
        std::runtime_error);

    std::remove(path.c_str());
}

TEST_CASE("matrix_io::load throws when dimensions are invalid")
{
    const std::string path = "test_matrix_invalid_dimensions.txt";

    write_text_file(
        path,
        "-1 3\n");

    CHECK_THROWS_AS(
        matrix_io::load(path),
        std::invalid_argument);

    std::remove(path.c_str());
}

TEST_CASE("matrix_io::load throws when matrix data is incomplete")
{
    const std::string path = "test_matrix_incomplete_data.txt";

    write_text_file(
        path,
        "2 3\n"
        "1.0 2.0 3.0\n"
        "4.0\n");

    CHECK_THROWS_AS(
        matrix_io::load(path),
        std::runtime_error);

    std::remove(path.c_str());
}

TEST_CASE("matrix_io::save writes matrix to file")
{
    const std::string path = "test_matrix_save.txt";

    Matrix A(2, 3);

    for (int idx = 0; idx < A.get_size(); ++idx)
        A.at(idx) = static_cast<double>(idx + 1);

    matrix_io::save(path, A);

    std::ifstream file(path);

    REQUIRE(file_exists(path));
    REQUIRE(file);

    int rows;
    int cols;

    file >> rows >> cols;

    CHECK(rows == 2);
    CHECK(cols == 3);

    double value;

    file >> value;
    CHECK(value == doctest::Approx(1.0));

    file >> value;
    CHECK(value == doctest::Approx(2.0));

    file >> value;
    CHECK(value == doctest::Approx(3.0));

    file >> value;
    CHECK(value == doctest::Approx(4.0));

    file >> value;
    CHECK(value == doctest::Approx(5.0));

    file >> value;
    CHECK(value == doctest::Approx(6.0));

    std::remove(path.c_str());
}

TEST_CASE("matrix_io::save output can be loaded back")
{
    const std::string path = "test_matrix_roundtrip.txt";

    Matrix A(2, 2);

    A.at(0) = 1.25;
    A.at(1) = 2.50;
    A.at(2) = 3.75;
    A.at(3) = 4.00;

    matrix_io::save(path, A);

    Matrix B = matrix_io::load(path);

    CHECK(B.get_shape() == A.get_shape());

    for (int idx = 0; idx < A.get_size(); ++idx)
    {
        CHECK(B.at(idx) == doctest::Approx(A.at(idx)));
    }

    std::remove(path.c_str());
}

TEST_CASE("matrix_io::save throws when path cannot be opened")
{
    Matrix A(2, 2, 1.0);

    CHECK_THROWS_AS(
        matrix_io::save("/this/path/should/not/exist/matrix.txt", A),
        std::runtime_error);
}
