#pragma once

#include <string>

#include "matrix.hpp"

namespace matrix_io
{
    Matrix load(const std::string &path);

    void save(const std::string &path, const Matrix &matrix);

    void print(const Matrix &matrix, int decimals = 2);
}