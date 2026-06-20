#include "qr.hpp"

#include "../matrix/matrix_operations.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <vector>

std::tuple<std::vector<int>, Matrix, Matrix, int> QR::decompose(
    const Matrix &A)
{
    int rows = A.get_rows();
    int cols = A.get_cols();
    int max_rank = std::min(rows, cols);
    int rank = 0;

    std::vector<int> P(cols);
    std::iota(P.begin(), P.end(), 0);

    Matrix Q(rows, max_rank, 0.0);
    Matrix R(max_rank, cols, 0.0);

    // Working matrix, containing pivoted columns of A with projections onto the accepted Q basis removed.
    Matrix V(A);

    double tolerance = std::numeric_limits<double>::epsilon() *
                       std::max(rows, cols) * std::max(1.0, norm(A));

    for (int k = 0; k < max_rank; ++k)
    {
        // Modified Gram-Schmidt: Find the remaining column in V with the largest residual norm.

        int pivot = k;

        double pivot_norm = 0.0;

        for (int j = k; j < cols; ++j)
        {
            double column_norm = norm(col(V, j));

            if (column_norm > pivot_norm)
            {
                pivot = j;
                pivot_norm = column_norm;
            }
        }

        // V has already had projections onto previously accepted Q columns removed.

        if (pivot_norm <= tolerance)
        {
            break; // Since the largest residual norm was chosen, no remaining column can pass.
        }

        // A column above tolerance remains, accept it as a new basis vector.

        if (pivot != k)
        {
            std::swap(P[k], P[pivot]);

            for (int i = 0; i < rows; ++i)
            {
                std::swap(V(i, k), V(i, pivot));
            }

            for (int i = 0; i < k; ++i)
            {
                std::swap(R(i, k), R(i, pivot));
            }
        }

        R(k, k) = pivot_norm;

        for (int i = 0; i < rows; ++i)
        {
            Q(i, k) = V(i, k) / pivot_norm;
        }

        auto q = col(Q, k);

        // Remove projections onto pivot from next unprocessed columns

        for (int j = k + 1; j < cols; ++j)
        {
            auto v = col(V, j);
            double projection = dot(q, v);

            R(k, j) = projection;
            v -= projection * q;

            for (int i = 0; i < rows; ++i)
            {
                V(i, j) = v(i, 0);
            }
        }

        ++rank;
    }

    Q.resize(rows, rank);
    R.resize(rank, cols);

    return {std::move(P), std::move(Q), std::move(R), rank};
}

double QR::validate_decomposition(
    const Matrix &A,
    const Matrix &Q,
    const Matrix &R,
    const std::vector<int> &P)
{
    int cols = A.get_cols();

    if (static_cast<int>(P.size()) != cols)
    {
        throw std::runtime_error("Permutation size must equal the number of columns in A");
    }

    Matrix Pmat(cols, cols, 0.0);

    for (int i = 0; i < cols; ++i)
    {
        Pmat(P[i], i) = 1.0;
    }

    auto diff = (A * Pmat) - (Q * R);

    return norm(diff);
}
