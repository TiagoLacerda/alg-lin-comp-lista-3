#pragma once

#include <vector>

#include "../matrix/matrix.hpp"

namespace LU
{
    /// @brief Perform the PAQ=LU decomposition of a full-rank matrix.
    /// @param A
    /// @return P, Q, L, U
    std::tuple<std::vector<int>, std::vector<int>, Matrix, Matrix> decompose(
        const Matrix &A);

    /// @brief Return the Frobenius norm of PAQ - LU.
    /// @param A
    /// @param L
    /// @param U
    /// @param P
    /// @param Q
    /// @return
    double validate_decomposition(
        const Matrix &A,
        const Matrix &L,
        const Matrix &U,
        const std::vector<int> &P,
        const std::vector<int> &Q);

    /// @brief Find the the best pivot inside the submatrix corresponding to the kth elimination round in the LU decomposition.
    /// @param A
    /// @param k Zero-based elimination round index
    /// @return the row, column and value of the best found pivot
    std::tuple<int, int, double> find_best_pivot(const Matrix &A, const int k);
}
