#include <print>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#include "sorting.h"
#include "gen_bin_file.h"

using namespace std::chrono_literals;

class Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
    explicit Timer() : start(std::chrono::high_resolution_clock::now()) {}
    ~Timer()
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::println("time is {}", duration);
    }
};

void some_sort(std::vector<unsigned short>& arr, std::string name, void(*f)(std::vector<unsigned short>&))
{
    std::println("{}", name);
    Timer t;
    f(arr);
}

std::vector<int> generate_array(size_t size, int range = 1000)
{
    std::vector<int> v(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, range);
    for(int& num : v) {
        num = distr(gen);
    }
    return v;
}

void test_counting_sort(std::vector<unsigned short> arr)
{
    some_sort(arr, "counting_sort", &counting_sort);
}

void test_radix_sort(std::vector<unsigned short> arr)
{
    some_sort(arr, "radix_sort", &radix_sort);
}

void test_bucket_sort(std::vector<unsigned short> arr)
{
    some_sort(arr, "bucket_sort", &bucket_sort);
}

void stop()
{
    std::this_thread::sleep_for(6min);
    std::println(std::cerr, "stopped 2 min");
    exit(1);
}

int main()
{
    auto v = gen_bin_array();
    std::thread t(stop);
    test_counting_sort(v);
    test_bucket_sort(v);
    test_radix_sort(v);
    exit(0);
}