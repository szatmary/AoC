#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <string>
#include <vector>

int main(int arvc, char* argv[])
{
    if (arvc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string line;
    std::getline(file, line);

    std::regex re(R"(mul\((\d+),(\d+)\))");

    const std::vector<std::smatch> matches {
        std::sregex_iterator { std::cbegin(line), std::end(line), re },
        std::sregex_iterator {}
    };

    int total = 0;
    for (const auto& match : matches) {
        total += std::stoi(match[1]) * std::stoi(match[2]);
    }

    std::cout << total << '\n';

    return 0;
}
