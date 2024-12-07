#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

void read_file(const std::string& filename, auto cb)
{
    std::ifstream
        file(filename);
    std::string line;
    while (std::getline(file, line)) {
        cb(line);
    }
}

// std::vector<int64_t> parse(std::string input, std::string regex)
// {
//     std::vector<int64_t> result;
//     std::regex re(regex);
//     std::smatch match;
//     if (std::regex_search(input, match, re)) {
//         for (size_t i = 1; i < match.size(); ++i) {
//             std::printf("match[%d]: %s\n", i, match[i].str().c_str());
//             result.push_back(std::stoll(match[i].str()));
//         }
//     }
//     return result;
// }

std::vector<int64_t> split(const std::string& input, const std::string& regex)
{
    std::vector<int64_t> result;
    std::regex re(regex);
    std::sregex_token_iterator
        first(input.begin(), input.end(), re, -1),
        last;
    for (auto it = first; it != last; ++it) {
        // std::cout << "match: " << it->str() << std::endl;
        result.push_back(std::stoll(it->str()));
    }
    return result;
}

int main(int argc, char* argv[])
{
    std::vector<std::vector<int64_t>> numbers;
    read_file(argv[1], [&](const std::string& line) {
        auto v = split(line, R"(:?\s)");
        numbers.push_back(v);
    });

    int64_t total = 0;
    for (const auto& n : numbers) {
        auto target = n[0];
        std::function<bool(int64_t val, const std::vector<int64_t>::const_iterator& iter)> can_solve
            = [&](int64_t val, const std::vector<int64_t>::const_iterator& iter) -> bool {
            if (iter == n.end()) {
                return val == target;
            }
            // std::printf("val: %ld, *iter: %ld\n", val, *iter);
            return can_solve(val + *iter, iter + 1) || can_solve(val * *iter, iter + 1);
        };
        auto solved = can_solve(n[1], n.begin() + 2);
        if (solved) {
            total += target;
        }
        // std::cout << "len: " << n.size() << std::endl;
        // std::cout << "solved: " << solved << std::endl;
    }

    std::cout << "total: " << total << std::endl;
    // for (auto iter = numbers.begin(); iter != numbers.end(); ++iter) {
    // }

    return 0;
}