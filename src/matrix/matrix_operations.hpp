#pragma once

#include "matrix.hpp"

Matrix operator*(double scalar, const Matrix &matrix);

Matrix operator*(const Matrix &matrix, double scalar);

Matrix operator/(const Matrix& matrix, double scalar);

Matrix operator*(const Matrix &A, const Matrix &B);

Matrix operator-(const Matrix &A, const Matrix &B);

Matrix row(const Matrix &A, int i);

Matrix col(const Matrix &A, int j);

double norm_squared(const Matrix &A);

double norm(const Matrix &A);

double dot(const Matrix &u, const Matrix &v);