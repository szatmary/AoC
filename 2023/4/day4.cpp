#include "utils.hpp"

void part1(const std::string& file)
{
    int total = 0;
    lines(file, [&](const std::string& l) {
        auto s = split(l, R"(\|\s+)");
        auto winning = split(s[0], R"(\s+)");
        auto have = split(s[1], R"(\s+)");
        auto val = 0;
        for (auto& h : have) {
            if (std::find(winning.begin(), winning.end(), h) != winning.end()) {
                val = val == 0 ? 1 : val * 2;
            }
        }
        total += val;
    });
    std::cout << "Total: " << total << std::endl;
}

int expand(const std::vector<int>& cards, int i)
{
    if (i > cards.size()) {
        return 0;
    }
    int total = 1;
    for (int j = i + 1; j < i + 1 + cards[i]; ++j) {
        total += expand(cards, j);
    }
    return total;
}

void part2(const std::string& file)
{
    std::vector<int> card;
    lines(file, [&](const std::string& l) {
        auto s = split(l, R"(\|\s+)");
        auto winning = split(s[0], R"(\s+)");
        auto have = split(s[1], R"(\s+)");
        int copies = 0;
        for (auto& h : have) {
            if (std::find(winning.begin(), winning.end(), h) != winning.end()) {
                copies++;
            }
        }
        card.push_back(copies);
    });

    int t = 0;
    for (int i = 0; i < card.size(); ++i) {
        t += expand(card, i);
    }
    std::cout << "Total: " << t << std::endl;
}

int main(int argc, char const* argv[])
{
    part1(argv[1]);
    part2(argv[1]);
    return 0;
}