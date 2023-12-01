#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void lines(const std::string& file, auto line)
{
    std::string l;
    std::ifstream f(file);
    while (std::getline(f, l)) {
        line(l);
    }
}

int main(int argc, char* argv[])
{
    auto total = 0;
    auto digits = std::string("0123456789");
    lines(argv[1], [&](const std::string& line) {
        auto first = line.find_first_of(digits);
        auto last = line.find_last_of(digits);
        auto num = (10 * (line[first] - '0')) + (line[last] - '0');
        total += num;
    });
    std::cout << total << std::endl;
    return 0;
}
