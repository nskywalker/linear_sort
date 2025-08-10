//
// Created by googl on 10.08.2025.
//

#include "sorting.h"

#include <algorithm>
#include <deque>
#include <list>
#include <vector>

void counting_sort(std::vector<unsigned short>& array)
{
    const int max = std::ranges::max(array);
    std::vector<int> count(max + 1, 0);
    for (const auto& elem : array) {
        ++count[elem];
    }
    auto first_elem = count.front();
    while (first_elem != 0)
    {
        array[--first_elem] = 0;
    }
    for (int i = 1; i < count.size(); ++i) {
        auto prev_elems = count[i - 1];
        auto curr_elems = count[i];
        while (curr_elems != 0)
        {
            array[--curr_elems + prev_elems] = i;
        }
        count[i] += prev_elems;
    }
}

int find_digits(std::vector<unsigned short>& array)
{
    const int max = std::ranges::max(array);
    int digits = 0;
    for (int r = 1; ; r *= 10)
    {
        int res = max / r % 10;
        if (res == 0) {
            break;
        }
        ++digits;
    }
    return digits;
}

void radix_sort(std::vector<unsigned short>& array)
{
    const int base = 10;
    int digits = find_digits(array);
    int r = 1;
    std::vector<int> temp(array.size(), 0);
    for (int d = 1; d <= digits; ++d) {
        std::vector<int> radix(base, 0);
        for (const int i : array) {
            const int dig = i / r % base;
            ++radix[dig];
        }
        int z = 0;
        for (int i = 0; i < base; i++)  {
            z += radix[i];
            radix[i] = z;
        }
        for(int i = array.size()-1; i >= 0; i--) {
            int dig = array[i] / r % base;
            radix[dig]--;
            temp[radix[dig]] = array[i];
        }
        std::ranges::copy(temp, array.begin());
        r *= base;
    }
}

void bucket_sort(std::vector<unsigned short>& array)
{
    const int max = std::ranges::max(array);
    int num_buckets = 10;
    std::vector buckets(num_buckets, std::deque<int>());
    for (int elem : array) {
        auto curNumBacket = static_cast<int>(elem * 1.0 / (max + 1) * num_buckets);
        auto& curBacket = buckets[curNumBacket];
        if (curBacket.empty()) {
            curBacket.push_back(elem);
        } else {
            int j = 0;
            while (j < curBacket.size() && curBacket[j] < elem) {
                ++j;
                curBacket.insert(curBacket.begin() + j, elem);
            }
        }
    }
    int j = 0;
    for (auto& curBucket : buckets) {
        if (!curBucket.empty()) {
            for (const int k : curBucket) {
                array[j++] = k;
            }
        }
    }
}
