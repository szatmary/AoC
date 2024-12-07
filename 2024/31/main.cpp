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

class Matrix : public std::vector<std::vector<std::string>> {
public:
    void read_file(const std::string& filename, const std::string& split)
    {
        std::vector<std::string> lines;
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            if (split.empty()) {
                push_back({ line });
            } else {
                std::regex re(split);
                // passing -1 as the submatch index parameter performs splitting
                std::sregex_token_iterator first { line.begin(), line.end(), re, -1 };
                push_back({ first, {} });
            }
        }
    }

    // std::string str() const
    // {
    //     std::string result;
    //     for (const auto& row : *this) {
    //         for (const auto& col : row) {
    //             result += col + ' ';
    //         }
    //         result += '\n';
    //     }
    //     return result;
    // }

    void print()
    {
        for (const auto& row : *this) {
            for (const auto& col : row) {
                std::cout << "'" << col << "'" << ' ';
            }
            std::cout << '\n';
        }
    }
};

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
        // std::cout << match[0] << '\n';
        std::cout << match[1] << '\n';
        std::cout << match[2] << '\n';
        total += std::stoi(match[1]) * std::stoi(match[2]);
    }

    std::cout << total << '\n';
    // passing -1 as the submatch index parameter performs splitting
    // std::sregex_iterator first { line.begin(), line.end(), re, -1 };
    // // push_back({ first, {} });
    // for (auto it = first; it != std::sregex_token_iterator(); ++it) {
    //     std::cout << *it << '\n';
    // }

    return 0;
}