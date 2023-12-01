#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

void lines(const std::string& file, auto line)
{
    std::string l;
    std::ifstream f(file);
    while (std::getline(f, l)) {
        line(l);
    }
}

std::vector<int> find_digits(const std::string& s)
{
    auto m = std::unordered_map<std::string, int> {
        { "1", 1 },
        { "2", 2 },
        { "3", 3 },
        { "4", 4 },
        { "5", 5 },
        { "6", 6 },
        { "7", 7 },
        { "8", 8 },
        { "9", 9 },
        { "one", 1 },
        { "two", 2 },
        { "three", 3 },
        { "four", 4 },
        { "five", 5 },
        { "six", 6 },
        { "seven", 7 },
        { "eight", 8 },
        { "nine", 9 },
    };

    std::vector<int> digits;
    for (auto i = 0; i < s.size(); ++i) {
        auto substr = s.substr(i);
        for (auto& d : m) {
            if (0 == substr.find(d.first)) {
                digits.push_back(d.second);
                break;
            }
        }
    }
    return digits;
}

int main(int argc, char* argv[])
{
    auto total = 0;
    lines(argv[1], [&](const std::string& line) {
        auto digits = find_digits(line);
        auto num = (digits.front() * 10) + digits.back();
        total += num;
    });
    std::cout << total << std::endl;
    return 0;
}
