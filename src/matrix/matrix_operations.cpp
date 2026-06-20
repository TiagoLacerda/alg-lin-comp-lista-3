#include "matrix_operations.hpp"

#include <cmath>
#include <stdexcept>

Matrix operator*(double scalar, const Matrix &matrix)
{
    return matrix * scalar;
}

Matrix operator*(const Matrix &matrix, double scalar)
{
    int rows = matrix.get_rows();
    int cols = matrix.get_cols();

    Matrix result(rows, cols);

    for (int idx = 0; idx < rows * cols; ++idx)
    {
        result.at(idx) = matrix.at(idx) * scalar;
    }

    return result;
}

Matrix operator/(const Matrix &matrix, double scalar)
{
    if (scalar == 0.0)
    {
        throw std::runtime_error("Cannot divide matrix by zero");
    }

    Matrix result(matrix);

    for (int i = 0; i < result.get_rows(); ++i)
    {
        for (int j = 0; j < result.get_cols(); ++j)
        {
            result(i, j) /= scalar;
        }
    }

    return result;
}

Matrix operator*(const Matrix &A, const Matrix &B)
{
    if (A.get_cols() != B.get_rows())
    {
        throw std::runtime_error("Cannot multiply matrices with incompatible dimensions");
    }

    Matrix C(A.get_rows(), B.get_cols());

    for (int i = 0; i < A.get_rows(); ++i)
    {
        for (int j = 0; j < B.get_cols(); ++j)
        {
            C(i, j) = 0.0;

            for (int k = 0; k < A.get_cols(); ++k)
            {
                C(i, j) += A(i, k) * B(k, j);
            }
        }
    }

    return C;
}

Matrix operator+(const Matrix &A, const Matrix &B)
{
    Matrix C(A);
    C += B;
    return C;
}

Matrix operator-(const Matrix &A, const Matrix &B)
{
    Matrix C(A);
    C -= B;
    return C;
}

Matrix row(const Matrix &A, int i)
{
    int cols = A.get_cols();

    Matrix u(1, cols);

    for (int j = 0; j < cols; ++j)
    {
        u(0, j) = A(i, j);
    }

    return u;
}

Matrix col(const Matrix &A, int j)
{
    int rows = A.get_rows();

    Matrix u(rows, 1);

    for (int i = 0; i < rows; ++i)
    {
        u(i, 0) = A(i, j);
    }

    return u;
}

double norm_squared(const Matrix &A)
{
    double sum = 0.0;

    for (int idx = 0; idx < A.get_size(); ++idx)
    {
        sum += A.at(idx) * A.at(idx);
    }

    return sum;
}

double norm(const Matrix &A)
{
    return std::sqrt(norm_squared(A));
}

double dot(const Matrix &u, const Matrix &v)
{
    int size = u.get_size();

    if (size != v.get_size())
    {
        throw std::runtime_error("Cannot take the dot product of vectors with incompatible dimensions");
    }

    double result = 0.0;

    for (int idx = 0; idx < size; ++idx)
    {
        result += u.at(idx) * v.at(idx);
    }

    return result;
}