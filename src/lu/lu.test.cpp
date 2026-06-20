#include "doctest.h"

#include "lu.hpp"

#include "../matrix/matrix_io.hpp"
#include "../matrix/matrix_operations.hpp"

#include <algorithm>
#include <string>
#include <vector>

TEST_CASE("LU reconstructs every square example matrix")
{
    const std::vector<std::string> examples = {
        "16_16_LI.txt",
        "16_16_LD.txt",
        "32_32_LI.txt",
        "32_32_LD.txt",
    };

    for (const auto &example : examples)
    {
        CAPTURE(example);

        Matrix A = matrix_io::load("assets/matrices/" + example);
        auto [P, Q, L, U] = LU::decompose(A);

        CHECK(P.size() == static_cast<std::size_t>(A.get_rows()));
        CHECK(Q.size() == static_cast<std::size_t>(A.get_cols()));

        double error = LU::validate_decomposition(A, L, U, P, Q);
        CHECK(error <= 1e-8 * std::max(1.0, norm(A)));
    }
}
