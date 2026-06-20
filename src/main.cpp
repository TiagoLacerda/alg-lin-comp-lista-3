#include <cmath>
#include <filesystem>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

#include "lu/lu.hpp"
#include "matrix/matrix_io.hpp"
#include "qr/qr.hpp"
#include "utils/utils.hpp"

int main(void)
{
    std::filesystem::path directory = "assets/matrices";
    std::filesystem::path name = "8_4_LD_SCRAMBLED.txt";
    std::filesystem::path path = directory / name;

    auto A = matrix_io::load(path.string());

    auto [P, Q, R, k] = QR::decompose(A);

    matrix_io::print(A);
    std::cout << std::endl;
    matrix_io::print(Q);
    std::cout << std::endl;
    matrix_io::print(R);
    std::cout << std::endl;

    auto err = QR::validate_decomposition(A, Q, R, P);

    std::cout << "k = " << k << std::endl;
    std::cout << "Err = " << err << std::endl;

    return 0;
}
