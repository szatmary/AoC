#include "utils.hpp"

int fuel(int x)
{
    int totalfuel = x / 3 - 2;
    int next = totalfuel;
    for (;;) {
        next = next / 3 - 2;
        if (next <= 0) {
            break;
        }
        totalfuel += next;
    }
    return totalfuel;
}

// 4931807 too high
void part2(const std::string& file)
{
    int sum = 0;
    lines(file, [&](const std::string& line) {
        auto x = std::atoi(line.c_str());
        sum += fuel(x);
    });
    // sum = std::floor(100756 / 3.0) - 2;
    // std::cout << "Part 1: " << sum << std::endl;

    // double fuel = sum;
    std::cout << "Part 2: " << int(sum) << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input file>" << std::endl;
        return -1;
    }

    part2(argv[1]);
    return 0;
}