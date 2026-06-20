#include "matrix_io.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace matrix_io
{
    Matrix load(const std::string &path)
    {
        std::ifstream file(path);

        if (!file)
        {
            throw std::runtime_error("Failed to open file: " + path);
        }

        int rows;
        int cols;

        if (!(file >> rows >> cols))
        {
            throw std::runtime_error("Failed to read matrix dimensions");
        }

        Matrix matrix(rows, cols);

        for (int idx = 0; idx < rows * cols; ++idx)
        {
            if (!(file >> matrix.at(idx)))
            {
                throw std::runtime_error("Failed to read matrix data");
            }
        }

        return matrix;
    }

    void save(const std::string &path, const Matrix &matrix)
    {
        std::ofstream file(path);

        if (!file)
        {
            throw std::runtime_error("Failed to open file: " + path);
        }

        int rows = matrix.get_rows();
        int cols = matrix.get_cols();

        file << rows << ' ' << cols << '\n';

        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                if (col > 0)
                {
                    file << ' ';
                }

                file << matrix(row, col);
            }

            file << '\n';
        }
    }

    void print(const Matrix &matrix, int decimals)
    {
        int rows = matrix.get_rows();
        int cols = matrix.get_cols();

        std::vector<std::size_t> widths(cols, 0);

        for (int col = 0; col < cols; ++col)
        {
            for (int row = 0; row < rows; ++row)
            {
                std::ostringstream ss;

                ss << std::fixed
                   << std::setprecision(decimals)
                   << matrix(row, col);

                widths[col] = std::max(widths[col], ss.str().size());
            }
        }

        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                std::cout << std::setw(static_cast<int>(widths[col]))
                          << std::fixed
                          << std::setprecision(decimals)
                          << matrix(row, col);

                if (col + 1 < cols)
                {
                    std::cout << ' ';
                }
            }

            std::cout << '\n';
        }
    }
}