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
    std::filesystem::path directory = "E:/Documents/Projects/alg-lin-comp-lista-3/assets/matrices";
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

    auto stem = name.stem().string();
    auto extension = name.extension().string();

    // matrix_io::save((directory / (stem + "_Q" + extension)).string(), Q);
    // matrix_io::save((directory / (stem + "_R" + extension)).string(), R);

    return 0;
}

// int main(void)
// {
//     std::filesystem::path directory = "E:/Documents/Projects/alg-lin-comp-lista-3/assets/matrices";
//     std::filesystem::path name = "8_4_LD.txt";
//     std::filesystem::path path = directory / name;

//     auto A = matrix_io::load(path.string());

//     auto [B, E] = scramble_rows_preserving_scale(A, 1000);

//     matrix_io::print(A);
//     matrix_io::print(B);
//     matrix_io::print(E);

//     auto stem = name.stem().string();
//     auto extension = name.extension().string();

//     matrix_io::save((directory / (stem + "_SCRAMBLED" + extension)).string(), B);

//     return 0;
// }
