#include "utils.hpp"

#include <random>
#include <stdexcept>

void random_row_col_permutations(Matrix &A, int k)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> row_dist(0, A.get_rows() - 1);
    std::uniform_int_distribution<> col_dist(0, A.get_cols() - 1);

    for (int iter = 0; iter < k; ++iter)
    {
        int r1 = row_dist(gen);
        int r2 = row_dist(gen);

        for (int j = 0; j < A.get_cols(); ++j)
        {
            std::swap(A(r1, j), A(r2, j));
        }

        int c1 = col_dist(gen);
        int c2 = col_dist(gen);

        for (int i = 0; i < A.get_rows(); ++i)
        {
            std::swap(A(i, c1), A(i, c2));
        }
    }
}

std::tuple<Matrix, Matrix> scramble_rows_preserving_scale(
    Matrix &A,
    int k)
{
    int rows = A.get_rows();

    Matrix B(A);
    Matrix E(rows, rows, 0.0);

    for (int i = 0; i < rows; ++i)
    {
        E(i, i) = 1.0;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> row_dist(0, rows - 1);
    std::uniform_real_distribution<> angle_dist(-0.5, 0.5);
    std::uniform_int_distribution<> operation_dist(0, 2);

    for (int iter = 0; iter < k; ++iter)
    {
        int operation = operation_dist(gen);

        int r1 = row_dist(gen);
        int r2 = row_dist(gen);

        if (r1 == r2)
        {
            continue;
        }

        if (operation == 0)
        {
            for (int j = 0; j < B.get_cols(); ++j)
            {
                std::swap(B(r1, j), B(r2, j));
            }

            for (int j = 0; j < E.get_cols(); ++j)
            {
                std::swap(E(r1, j), E(r2, j));
            }
        }
        else if (operation == 1)
        {
            for (int j = 0; j < B.get_cols(); ++j)
            {
                B(r1, j) = -B(r1, j);
            }

            for (int j = 0; j < E.get_cols(); ++j)
            {
                E(r1, j) = -E(r1, j);
            }
        }
        else
        {
            double theta = angle_dist(gen);
            double c = std::cos(theta);
            double s = std::sin(theta);

            for (int j = 0; j < B.get_cols(); ++j)
            {
                double x = B(r1, j);
                double y = B(r2, j);

                B(r1, j) = c * x - s * y;
                B(r2, j) = s * x + c * y;
            }

            for (int j = 0; j < E.get_cols(); ++j)
            {
                double x = E(r1, j);
                double y = E(r2, j);

                E(r1, j) = c * x - s * y;
                E(r2, j) = s * x + c * y;
            }
        }
    }

    transpose(E);

    return {std::move(B), std::move(E)};
}