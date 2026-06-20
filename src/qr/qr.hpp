#pragma once

#include <vector>

#include "../matrix/matrix.hpp"

namespace QR
{
    /// @brief Perform the column-pivoted, economical QR decomposition AP = QR.
    /// @param A
    /// @return P, Q, R, rank
    std::tuple<std::vector<int>, Matrix, Matrix, int> decompose(
        const Matrix &A);

    /// @brief Return the Frobenius norm of AP - QR.
    /// @param A
    /// @param Q
    /// @param R
    /// @param P
    /// @return the reconstruction error
    double validate_decomposition(
        const Matrix &A,
        const Matrix &Q,
        const Matrix &R,
        const std::vector<int> &P);
}
