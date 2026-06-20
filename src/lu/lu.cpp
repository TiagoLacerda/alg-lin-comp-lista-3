#include "lu.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

#include "../matrix/matrix_operations.hpp"

std::tuple<std::vector<int>, std::vector<int>, Matrix, Matrix> LU::decompose(
    const Matrix &A)
{
    if (A.get_rows() != A.get_cols())
    {
        throw std::runtime_error("Cannot perform LU decomposition on a non-square matrix");
    }

    double tolerance = 1e-6;

    int rows = A.get_rows();
    int cols = A.get_cols();

    std::vector<int> P(rows);
    std::vector<int> Q(rows);

    Matrix L(rows, cols, 0.0);
    Matrix U(A);

    for (int k = 0; k < rows; ++k)
    {
        P[k] = k;
        Q[k] = k;
        L(k, k) = 1.0;
    }

    for (int k = 0; k < rows; ++k)
    {
        auto [pi, pj, pivot] = find_best_pivot(U, k);

        if (std::abs(pivot) <= tolerance)
        {
            break;
        }

        if (pi != k)
        {
            std::swap(P[k], P[pi]);

            for (int j = 0; j < k; ++j)
            {
                std::swap(L(k, j), L(pi, j));
            }

            for (int j = 0; j < rows; ++j)
            {
                std::swap(U(k, j), U(pi, j));
            }
        }

        if (pj != k)
        {
            std::swap(Q[k], Q[pj]);

            for (int i = 0; i < rows; ++i)
            {
                std::swap(U(i, k), U(i, pj));
            }
        }

        for (int i = k + 1; i < rows; ++i)
        {
            double factor = U(i, k) / pivot;

            L(i, k) = factor;

            for (int j = k; j < cols; ++j)
            {
                U(i, j) -= factor * U(k, j);
            }
        }
    }

    return {std::move(P), std::move(Q), std::move(L), std::move(U)};
}

double LU::validate_decomposition(
    const Matrix &A,
    const Matrix &L,
    const Matrix &U,
    const std::vector<int> &P,
    const std::vector<int> &Q)
{
    if (A.get_rows() != A.get_cols())
    {
        throw std::runtime_error("Validation requires a square matrix");
    }

    auto [n, m] = A.get_shape();

    Matrix Pmat(n, n, 0.0);
    Matrix Qmat(n, n, 0.0);

    for (int i = 0; i < n; ++i)
    {
        Pmat.at(i * n + P[i]) = 1.0;
        Qmat.at(Q[i] * n + i) = 1.0;
    }

    auto diff = ((Pmat * A) * Qmat) - (L * U);

    return norm(diff);
}

std::tuple<int, int, double> LU::find_best_pivot(const Matrix &A, int k)
{
    auto [rows, cols] = A.get_shape();

    if (rows != cols)
    {
        throw std::runtime_error("Cannot perform LU decomposition on a non-square matrix");
    }

    if (k >= rows)
    {
        throw std::runtime_error("Cannot find pivot for kth round of eliminations with k >= n");
    }

    int best_i = k;
    int best_j = k;

    double best_abs_value = 0.0;

    for (int i = k; i < rows; ++i)
    {
        for (int j = k; j < cols; ++j)
        {
            double abs_value = std::abs(A.at(i * cols + j));

            if (abs_value > best_abs_value)
            {
                best_i = i;
                best_j = j;
                best_abs_value = abs_value;
            }
        }
    }

    return {best_i, best_j, A.at(best_i * cols + best_j)};
}