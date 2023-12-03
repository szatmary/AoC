#include "utils.hpp"
#include <map>

void part1(const std::string& file)
{
    int t = 0;
    auto g = grid::loadfromfile(file);
    g.scan([&](grid::point p, const char* c) -> int {
        if (*c >= '0' && *c <= '9') {
            bool partnum = false;
            auto num = std::atoi(c);
            int len = std::to_string(num).size();
            g.scan_bounding_box({ p.x - 1, p.y - 1 }, { p.x + len, p.y + 1 }, [&](int x, int y, const char* c) {
                if (*c != '.') {
                    partnum = true;
                }
            });

            t += (partnum ? num : 0);
            return len;
        }
        return 1;
    });
    std::cout << "total:" << t << std::endl;
}

void part2(const std::string& file)
{
    int t = 0;
    auto g = grid::loadfromfile(file);
    std::map<grid::point, std::vector<int>> maybeygears;
    g.scan([&](grid::point p, const char* c) -> int {
        if (*c >= '0' && *c <= '9') {
            auto num = std::atoi(c);
            int len = std::to_string(num).size();
            g.scan_bounding_box({ p.x - 1, p.y - 1 }, { p.x + len, p.y + 1 }, [&](int x, int y, const char* c) {
                if (*c == '*') {
                    maybeygears[{ x, y }].push_back(num);
                }
            });
            return len;
        }
        return 1;
    });
    for (auto& [k, v] : maybeygears) {
        if (v.size() == 2) {
            t += v[0] * v[1];
        }
    }
    std::cout << "total:" << t << std::endl;
}

int main(int argc, char** argv)
{
    std::cout << "Part 1: " << std::endl;
    part1(argv[1]);
    std::cout << "Part 2: " << std::endl;
    part2(argv[1]);
    return 0;
}

// g++ -std=c++20 -O3 main.cpp && ./a.out example.txt