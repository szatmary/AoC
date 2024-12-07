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
            } else if (val > target) {
                return false;
            } else if (can_solve(val + *iter, iter + 1) || can_solve(val * *iter, iter + 1)) {
                return true;
            }
            auto val2 = std::atoll((std::to_string(val) + std::to_string(*iter)).c_str());
            return can_solve(val2, iter + 1);
        };
        auto solved = can_solve(n[1], n.begin() + 2);
        if (solved) {
            total += target;
        }
    }

    std::cout << "total: " << total << std::endl;
    return 0;
}