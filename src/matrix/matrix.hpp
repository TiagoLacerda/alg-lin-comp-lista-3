#pragma once

#include <utility>

/// @brief Row-major implementation of a matrix (rank-2 tensor).
struct Matrix
{
public:
    int get_rows() const;
    int get_cols() const;
    int get_size() const;

    /// @return rows, cols
    std::pair<int, int> get_shape() const;

    Matrix() = delete;

    Matrix(int rows, int cols);
    Matrix(int rows, int cols, double value);

    ~Matrix();

    Matrix(const Matrix &);
    Matrix &operator=(const Matrix &);

    Matrix(Matrix &&other) noexcept;
    Matrix &operator=(Matrix &&other) noexcept;

    Matrix &operator+=(const Matrix &other);
    Matrix &operator-=(const Matrix &other);

    double &operator()(int row, int col);
    const double &operator()(int row, int col) const;

    double &at(int idx);
    const double &at(int idx) const;

    Matrix transposed(const Matrix &A);

    friend Matrix &transpose(Matrix &A);

    void resize(int newRows, int newCols);

private:
    int rows = 0;
    int cols = 0;

    double *data = nullptr;
};