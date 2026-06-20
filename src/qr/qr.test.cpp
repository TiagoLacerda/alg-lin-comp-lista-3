#include "doctest.h"

#include "qr.hpp"

#include "../matrix/matrix_io.hpp"
#include "../matrix/matrix_operations.hpp"

#include <algorithm>
#include <string>
#include <vector>

TEST_CASE("QR decomposes every example matrix with the expected numerical rank")
{
    struct Example
    {
        std::string name;
        int rank;
    };

    const std::vector<Example> examples = {
        {"8_4_LI.txt", 4},
        {"8_4_LI_SCRAMBLED.txt", 4},
        {"8_4_LD.txt", 2},
        {"8_4_LD_SCRAMBLED.txt", 2},
        {"16_16_LI.txt", 16},
        {"16_16_LD.txt", 15},
        {"32_32_LI.txt", 32},
        {"32_32_LD.txt", 31},
    };

    for (const auto &example : examples)
    {
        CAPTURE(example.name);

        Matrix A = matrix_io::load("assets/matrices/" + example.name);
        auto [P, Q, R, rank] = QR::decompose(A);

        CHECK(rank == example.rank);
        CHECK(Q.get_rows() == A.get_rows());
        CHECK(Q.get_cols() == rank);
        CHECK(R.get_rows() == rank);
        CHECK(R.get_cols() == A.get_cols());

        double error = QR::validate_decomposition(A, Q, R, P);
        CHECK(error <= 1e-8 * std::max(1.0, norm(A)));
    }
}
