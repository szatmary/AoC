#include "utils.hpp"

void part1(const std::string& file)
{
    double sum = 0;
    lines(file, [&](const std::string& line) {
        auto x = std::atoi(line.c_str());
        sum += std::floor(x / 3.0) - 2;
    });
    std::cout << "Part 1: " << int(sum) << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input file>" << std::endl;
        return -1;
    }

    part1(argv[1]);
    return 0;
}