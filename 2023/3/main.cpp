#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

void lines(const std::string& file, auto line)
{
    std::string l;
    std::ifstream f(file);
    while (std::getline(f, l)) {
        line(l);
    }
}

std::vector<std::string> readlines(const std::string& file)
{
    std::vector<std::string> lines;
    std::string l;
    std::ifstream f(file);
    while (std::getline(f, l)) {
        lines.push_back(l);
    }
    return lines;
}

std::vector<std::string> split(const std::string& input, const std::string& regex)
{
    // passing -1 as the submatch index parameter performs splitting
    std::regex re(regex);
    std::sregex_token_iterator first { input.begin(), input.end(), re, -1 };
    return { first, {} };
}

bool sym(const std::vector<std::string>& input, int x, int y)
{
    if (x < 0 || x >= input.size() || y < 0 || y >= input[x].size()) {
        return false;
    }
    if (!std::isdigit(input[x][y]) && input[x][y] != '.') {
        std::cerr << "found at " << x << " " << y << std::endl;
        return true;
    }
    return false;
}

bool ispartnum(const std::vector<std::string>& input, int x, int y, int l)
{
    std::cout << "searching " << x << " " << y << " " << l << std::endl;
    // #123#
    if (sym(input, x, y - 1) || sym(input, x, y + l)) {
        return true;
    }

    // #####
    // .123.
    // #####
    for (int i = y - 1; i <= y + l; ++i) {
        if (sym(input, x - 1, i) || sym(input, x + 1, i)) {
            return true;
        }
    }
    return false;
}

void part1(const std::string& file)
{
    int t = 0;
    auto lines = readlines(file);
    for (int x = 0; x < lines.size(); ++x) {
        auto& line = lines[x];
        std::cout << line << std::endl;
        for (int y = 0; y < lines[x].size(); ++y) {
            if (line[y] >= '0' && line[y] <= '9') {
                auto num = std::atoi(&line[y]);
                auto len = std::to_string(num).size();
                std::cout << "found num:" << num << " " << len << std::endl;
                if (ispartnum(lines, x, y, len)) {
                    std::cout << "match " << num << std::endl;
                    t += num;
                } else {
                    std::cout << "no match " << num << std::endl;
                }
                y += len - 1;
            }
        }
    }
    std::cout << "total:" << t << std::endl;
}

bool isstar(const std::vector<std::string>& input, int x, int y)
{
    if (x < 0 || x >= input.size() || y < 0 || y >= input[x].size()) {
        return false;
    }
    if (input[x][y] == '*') {
        return true;
    }
    return false;
}

std::map<std::pair<int, int>, std::vector<int>> maybeygears;
void markgear(const std::vector<std::string>& input, int x, int y, int l, int v)
{
    std::cout << "searching " << x << " " << y << " " << l << std::endl;
    // #123#
    if (isstar(input, x, y - 1)) {
        maybeygears[{ x, y - 1 }].push_back(v);
        std::cout << "maybe found gear " << x << " " << y - 1 << std::endl;
    }

    if (isstar(input, x, y + l)) {
        maybeygears[{ x, y + l }].push_back(v);
        std::cout << "maybe found gear " << x << " " << y + l << std::endl;
    }
    // #####
    // .123.
    // #####
    for (int i = y - 1; i <= y + l; ++i) {
        if (isstar(input, x - 1, i)) {
            maybeygears[{ x - 1, i }].push_back(v);
            std::cout << "maybe found gear " << x - 1 << " " << i << std::endl;
        }
        if (isstar(input, x + 1, i)) {
            maybeygears[{ x + 1, i }].push_back(v);
            std::cout << "maybe found gear " << x + 1 << " " << i << std::endl;
        }
    }
}

void part2(const std::string& file)
{
    // x,y, count
    std::map<std::pair<int, int>, int> m;
    auto lines = readlines(file);
    for (int x = 0; x < lines.size(); ++x) {
        auto& line = lines[x];
        std::cout << line << std::endl;
        for (int y = 0; y < lines[x].size(); ++y) {
            if (line[y] >= '0' && line[y] <= '9') {
                auto num = std::atoi(&line[y]);
                auto len = std::to_string(num).size();
                markgear(lines, x, y, len, num);
                y += len - 1;
            }
        }
    }

    int total = 0;
    for (auto& [k, v] : maybeygears) {
        if (v.size() == 2) {
            std::cout << "hello" << std::endl;
            std::cout << "found gear " << k.first << " " << k.second << std::endl;
            total += (v[0] * v[1]);
        }
    }
    std::cout << "hello" << std::endl;
    std::cout << "total: " << total << std::endl;
}

int main(int argc, char** argv)
{
    // std::cout << "Part 1: " << std::endl;
    // part1(argv[1]);
    // std::cout << "Part 2: " << std::endl;
    part2(argv[1]);
    return 0;
}

// g++ -std=c++20 -O3 main.cpp && ./a.out example.txt