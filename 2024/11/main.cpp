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

std::vector<std::string> read_file(const std::string& filename)
{
    std::vector<std::string> lines;
    std::ifstream
        file(filename);
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::vector<std::string> split(const std::string& input, const std::string& regex)
{
    std::regex re(regex);
    // passing -1 as the submatch index parameter performs splitting
    std::sregex_token_iterator first { input.begin(), input.end(), re, -1 };
    return { first, {} };
}

int main(int arvc, char* argv[])
{
    if (arvc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::vector<int> a, b, c;
    auto lines = read_file(argv[1]);
    for (const auto& line : lines) {
        auto parts = split(line, R"(\s+)");
        a.push_back(std::stoi(parts[0]));
        b.push_back(std::stoi(parts[1]));
    }

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    for (int i = 0; i < a.size(); ++i) {
        c.push_back(std::abs(a[i] - b[i]));
    }

    for (const auto& i : c) {
        std::cout << i << '\n';
    }

    auto total = std::accumulate(c.begin(), c.end(), 0);
    std::cout << "Total: " << total << '\n';

    return 0;
}