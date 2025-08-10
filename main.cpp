#include <print>
#include <chrono>
#include <numeric>
#include <random>

#include "sorting.h"

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

void some_sort(std::vector<int>& arr, std::string name, void(*f)(std::vector<int>&))
{
    std::println("{}", name);
    Timer t;
    f(arr);
}

int main()
{
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0);
    std::shuffle(v.begin(), v.end(), std::mt19937(std::random_device()()));
    std::println("{}", v);
    radix_sort(v);
    std::println("{}", v);
}