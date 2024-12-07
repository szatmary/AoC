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

// const std::vector<std::smatch> matches {
//     std::sregex_iterator { std::cbegin(line), std::end(line), re },
//     std::sregex_iterator {}
// };

std::vector<std::string> load_file(const std::string& filename)
{
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back({ line });
    }
    return lines;
}

std::vector<std::pair<int, int>> parse_order(const std::vector<std::string>& lines)
{
    std::vector<std::pair<int, int>> order;
    for (const auto& l : lines) {
        std::smatch match;
        const std::regex re(R"((\d+)\|(\d+))");
        std::regex_match(l, match, re);
        // std::printf("Matched %s  = %s %s\n", l.c_str(), match[1].str().c_str(), match[2].str().c_str());
        order.push_back({ std::stoi(match[1]), std::stoi(match[2]) });
    }
    return order;
}

// TODO split shoudl be a regex
std::vector<std::string> split(const std::string& s, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = 0;
    while ((end = s.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
    }
    tokens.push_back(s.substr(start));
    return tokens;
}

int middle(std::vector<int> numbers)
{
    int m = numbers.size() / 2;
    return numbers[m];
}

/// does before combe before after in the list of numbers
bool before(const std::vector<int>& number, const std::pair<int, int>& rule)
{
    auto it = std::find(number.begin(), number.end(), rule.first);
    auto it2 = std::find(number.begin(), number.end(), rule.second);
    // return true rule does nto apply
    if (it == number.end() || it2 == number.end()) {
        return true;
    }
    return it < it2;
}

int main(int arvc, char* argv[])
{
    if (arvc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    auto order_file = load_file(argv[1]);
    auto order = parse_order(order_file);

    std::vector<std::vector<int>> pages;
    auto page_file = load_file("pages.txt");
    for (const auto& p : page_file) {
        pages.emplace_back();
        for (const auto& n : split(p, ",")) {
            pages.back().push_back(std::stoi(n));
        }
    }

    int answer = 0;
    for (const auto& p : pages) {
        bool incorrect = false;
        for (const auto& o : order) {
            if (!before(p, o)) {
                incorrect = true;
            }
        }
        if (!incorrect)
            answer += middle(p);
    }

    std::cout << "ans: " << answer << '\n';
    return 0;
}

// 10204714 too high
// 8934 too high
