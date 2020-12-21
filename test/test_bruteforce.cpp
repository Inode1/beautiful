#include <unordered_map>
#include <numeric>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <beautiful_numbers.hpp>

void increment(std::vector<size_t>& set, size_t base)
{
    for (auto& value: set)
    {
        if (value == base - 1)
        {
            value = 0;
        }
        else
        {
            ++value;
            return;
        }
    }
}

uint64_t bruteforce(size_t count)
{
    size_t positions = count / 2;
    std::vector<size_t> set(positions, 0);
    std::unordered_map<size_t, uint64_t> check;
    size_t size = std::pow(count, positions);

    uint64_t sum = 0;
    for (uint64_t i = 0; i < size; ++i)
    {
        sum = std::accumulate(set.begin(), set.end(), 0);
        //std::cout << sum << std::endl;
        if (auto find = check.find(sum); find != check.end())
        {
            ++find->second;
        } else
        {
            check[sum] = 1;
        }
        increment(set, count);
    }
    sum = 0;
    std::vector<std::pair<size_t, uint64_t>> tmp;
    for (const auto& [_, value]: check)
    {
        tmp.push_back({_, value});
        sum += value * value;
    }

    return sum;
}

int main()
{
    constexpr unsigned size = 13;
    constexpr uint64_t count = beautiful_numbers::count_v<size>;
    std::cout << count << ":" << bruteforce(size) * 13 << std::endl;
    return bruteforce(size) * 13 != count;
}