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

std::vector<std::string> split(const std::string& input, const std::string& regex)
{
    // passing -1 as the submatch index parameter performs splitting
    std::regex re(regex);
    std::sregex_token_iterator first { input.begin(), input.end(), re, -1 };
    return { first, {} };
}

std::map<std::string, int> parse(const std::string& input)
{
    std::map<std::string, int> v;
    for (auto& i : split(input, ",")) {
        int x;
        char color[256] = { 0 };
        std::sscanf(i.c_str(), "%d %s", &x, &color[0]);
        v.insert({ color, x });
    }
    return v;
}

void part1(const std::string& file)
{
    int red = 12;
    int green = 13;
    int blue = 14;

    int game = 1;
    int total = 0;
    lines(file, [&](const std::string& l) {
        auto pulls = split(l, ";");
        bool possible = true;
        for (const auto& pull : pulls) {
            auto v = parse(pull);
            if (v["red"] > red || v["green"] > green || v["blue"] > blue) {
                possible = false;
            }
        }
        if (possible) {
            total += game;
        }
        ++game;
    });
    std::cout << "Total: " << total << std::endl;
}

void part2(const std::string& file)
{
    int game = 1;
    int total = 0;
    lines(file, [&](const std::string& l) {
        int red = 0;
        int green = 0;
        int blue = 0;
        auto pulls = split(l, ";");
        for (const auto& pull : pulls) {
            auto v = parse(pull);
            red = std::max(red, v["red"]);
            green = std::max(green, v["green"]);
            blue = std::max(blue, v["blue"]);
        }
        total += red * green * blue;
        ++game;
    });
    std::cout << "Total: " << total << std::endl;
}

int main(int argc, char** argv)
{
    std::cout << "Part 1: " << std::endl;
    part1(argv[1]);
    std::cout << "Part 2: " << std::endl;
    part2(argv[1]);
}

// g++ -std=c++20 -O3 main.cpp && ./a.out example.txt