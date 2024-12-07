#include "utils.hpp"

void part1(const std::string& file)
{
    lines(file, [](const std::string& line) {
    });
}

void part2(const std::string& file)
{
    lines(file, [](const std::string& line) {
    });
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input file>" << std::endl;
        return -1;
    }

    part1(argv[1]);
    part2(argv[1]);
    return 0;
}