#include <algorithm>
#include <cstddef>
#include <utility>
#include <stdexcept>

#include "matrix.hpp"

int Matrix::get_rows() const
{
    return this->rows;
}

int Matrix::get_cols() const
{
    return this->cols;
}

int Matrix::get_size() const
{
    return this->rows * this->cols;
}

std::pair<int, int> Matrix::get_shape() const
{
    return {this->rows, this->cols};
}

Matrix::Matrix(int rows, int cols)
    : rows(rows),
      cols(cols),
      data(nullptr)
{
    if (rows < 0 || cols < 0)
    {
        throw std::invalid_argument("Matrix dimensions cannot be negative");
    }

    data = new double[rows * cols];
}

Matrix::Matrix(int rows, int cols, double value)
    : Matrix(rows, cols)
{
    for (int idx = 0; idx < rows * cols; ++idx)
    {
        data[idx] = value;
    }
}

Matrix::~Matrix()
{
    delete[] data;
}

Matrix::Matrix(const Matrix &other)
    : rows(other.rows),
      cols(other.cols),
      data(nullptr)
{
    if (other.data != nullptr)
    {
        data = new double[rows * cols];

        for (int idx = 0; idx < rows * cols; ++idx)
        {
            data[idx] = other.data[idx];
        }
    }
}

Matrix &Matrix::operator=(const Matrix &other)
{
    if (this == &other)
    {
        return *this;
    }

    double *buffer = new double[other.rows * other.cols];

    for (int idx = 0; idx < other.rows * other.cols; ++idx)
    {
        buffer[idx] = other.data[idx];
    }

    delete[] data;

    rows = other.rows;
    cols = other.cols;
    data = buffer;

    return *this;
}

Matrix::Matrix(Matrix &&other) noexcept
    : rows(other.rows),
      cols(other.cols),
      data(other.data)
{
    other.rows = 0;
    other.cols = 0;
    other.data = nullptr;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    delete[] data;

    rows = other.rows;
    cols = other.cols;
    data = other.data;

    other.rows = 0;
    other.cols = 0;
    other.data = nullptr;

    return *this;
}

Matrix &Matrix::operator+=(const Matrix &other)
{
    if (rows != other.get_rows() || cols != other.get_cols())
    {
        throw std::runtime_error("Cannot add matrices with incompatible dimensions");
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            (*this)(i, j) += other(i, j);
        }
    }

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other)
{
    if (rows != other.get_rows() || cols != other.get_cols())
    {
        throw std::runtime_error("Cannot add matrices with incompatible dimensions");
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            (*this)(i, j) -= other(i, j);
        }
    }

    return *this;
}

double &Matrix::operator()(int row, int col)
{
    return data[row * cols + col];
}

const double &Matrix::operator()(int row, int col) const
{
    return data[row * cols + col];
}

double &Matrix::at(int idx)
{
    return data[idx];
}

const double &Matrix::at(int idx) const
{
    return data[idx];
}

Matrix Matrix::transposed(const Matrix &A)
{
    Matrix B(A);

    transpose(B);

    return B;
}

Matrix &transpose(Matrix &A)
{
    int rows = A.rows;
    int cols = A.cols;

    double *transposed_data = new double[rows * cols];

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            transposed_data[j * rows + i] = A.data[i * cols + j];
        }
    }

    delete[] A.data;

    A.rows = cols;
    A.cols = rows;
    A.data = transposed_data;

    return A;
}
void Matrix::resize(int newRows, int newCols)
{
    if (newRows == rows && newCols == cols)
    {
        return;
    }

    if (newRows < 0 || newCols < 0)
    {
        throw std::invalid_argument("Matrix dimensions cannot be negative.");
    }

    double *newData = new double[newRows * newCols];

    for (int i = 0; i < newRows * newCols; ++i)
    {
        newData[i] = 0.0;
    }

    const int copyRows = std::min(rows, newRows);
    const int copyCols = std::min(cols, newCols);

    for (int r = 0; r < copyRows; ++r)
    {
        for (int c = 0; c < copyCols; ++c)
        {
            newData[r * newCols + c] = data[r * cols + c];
        }
    }

    delete[] data;

    data = newData;
    rows = newRows;
    cols = newCols;
}
