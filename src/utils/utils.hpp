#pragma once

#include "../matrix/matrix.hpp"

void random_row_col_permutations(Matrix &A, int k);

std::tuple<Matrix, Matrix> scramble_rows_preserving_scale(Matrix &A, int k);