//
// Created by googl on 10.08.2025.
//

#include <fstream>
#include <vector>
#include <ranges>
#include <limits>
#include "gen_bin_file.h"

#include <random>

void gen_bin_file()
{
    std::ofstream out("array.bin", std::ios::binary);
    std::vector<unsigned short> array;
    array.reserve(10000000ull);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, std::numeric_limits<unsigned short>::max());
    for (auto _ : std::views::iota(0ull, array.capacity()))
    {
        array.push_back(distr(gen));
    }
    out.write(reinterpret_cast<char*>(array.data()), sizeof(unsigned short) * array.size());
}
