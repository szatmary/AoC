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

bool increasing(const std::vector<std::string>& row)
{
    auto prev = std::stoi(row[0]);
    for (const auto& col : row) {
        if (std::stoi(col) < prev) {
            return false;
        }
        prev = std::stoi(col);
    }
    return true;
}

bool decreasing(const std::vector<std::string>& row)
{
    auto prev = std::stoi(row[0]);
    for (const auto& col : row) {
        if (std::stoi(col) > prev) {
            return false;
        }
        prev = std::stoi(col);
    }
    return true;
}

bool IsSafe(const std::vector<std::string>& row)
{
    if (!increasing(row) && !decreasing(row)) {
        return false;
    }
    for (int i = 1; i < row.size(); i++) {
        auto diff = std::abs(std::stoi(row[i]) - std::stoi(row[i - 1]));
        if (diff < 1) {
            return false;
        }
        if (diff > 3) {
            return false;
        }
    }
    return true;
}

int main(int arvc, char* argv[])
{
    if (arvc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    auto m = Matrix();
    m.read_file(argv[1], " ");
    // m.print();
    int safe = 0;
    for (const auto& row : m) {
        if (IsSafe(row)) {
            ++safe;
        } else {
            for (int i = 0; i < row.size(); i++) {
                auto vec = row;
                std::vector<std::string>::iterator it = vec.begin();
                std::advance(it, i);
                vec.erase(it);
                if (IsSafe(vec)) {
                    ++safe;
                    break;
                }
            }
        }
    }

    std::cout << "Safe: " << safe << '\n';
    return 0;
}