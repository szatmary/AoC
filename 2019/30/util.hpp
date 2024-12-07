#pragma once

#include <fstream>
#include <limits>
#include <map>
#include <regex>
#include <string>
#include <vector>

std::vector<std::string> ReadFile(const std::string& file)
{
    std::string l;
    std::vector<std::string> g;
    std::ifstream f(file);
    while (std::getline(f, l)) {
        g.push_back(l);
    }
    return g;
}

std::vector<std::string> split(const std::string& input, const std::string& regex)
{
    // passing -1 as the submatch index parameter performs splitting
    std::regex re(regex);
    std::sregex_token_iterator first { input.begin(), input.end(), re, -1 };
    return { first, {} };
}

//
template <typename T>
class SparceMatrix {
private:
    std::map<uint64_t, T> data;
    int xmin = 0;
    int ymin = 0;
    int xmax = 0;
    int ymax = 0;

public:
    SparceMatrix() = default;

    void set(int x, int y, T value) noexcept
    {
        data[x * std::numeric_limits<uint32_t>::max() + y] = value;
        xmin = std::min(xmin, x);
        ymin = std::min(ymin, y);
        xmax = std::max(xmax, x);
        ymax = std::max(ymax, y);
    }

    T get(int x, int y, T default_value = T()) const noexcept
    {
        auto itr = data.find(x * std::numeric_limits<uint32_t>::max() + y);
        if (itr == data.end())
            return default_value;
        return itr->second;
    }

    void print()
    {
        for (int y = ymin; y <= ymax; ++y) {
            for (int x = xmin; x <= xmax; ++x) {
                std::cout << get(x, y);
            }
            std::cout << std::endl;
        }
    }
};