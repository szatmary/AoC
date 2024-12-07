#include "utils.hpp"
#include <numeric>
struct hand1 {
    std::string cards;
    int bid;

    int cardrank(char c) const noexcept
    {
        switch (c) {
        case 'A':
            return 12;
        case 'K':
            return 11;
        case 'Q':
            return 10;
        case 'J':
            return 9;
        case 'T':
            return 8;
        case '9':
            return 7;
        case '8':
            return 6;
        case '7':
            return 5;
        case '6':
            return 4;
        case '5':
            return 3;
        case '4':
            return 2;
        case '3':
            return 1;
        case '2':
            return 0;
        }
        return -1;
    }

    int type() const noexcept
    {
        auto counts = std::array<int, 13> { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        for (auto c : cards) {
            counts[cardrank(c)]++;
        }
        // 5 of a kind
        if (std::any_of(counts.begin(), counts.end(), [](auto c) { return c == 5; })) {
            return 6;
        }
        // 4 of a kind
        if (std::any_of(counts.begin(), counts.end(), [](auto c) { return c == 4; })) {
            return 5;
        }
        // full house
        if (std::any_of(counts.begin(), counts.end(), [](auto c) { return c == 3; }) && std::any_of(counts.begin(), counts.end(), [](auto c) { return c == 2; })) {
            return 4;
        }
        // 3 of a kind
        if (std::any_of(counts.begin(), counts.end(), [](auto c) { return c == 3; })) {
            return 3;
        }
        // two pair
        if (std::count(counts.begin(), counts.end(), 2) == 2) {
            return 2;
        }
        // pair
        if (std::count(counts.begin(), counts.end(), 2) == 1) {
            return 1;
        }
        // high card
        return 0;
    }

    bool operator<(const hand1& other) const noexcept
    {
        if (type() != other.type()) {
            return type() < other.type();
        }
        for (int i = 0; i < 5; ++i) {
            if (cardrank(cards[i]) == cardrank(other.cards[i])) {
                continue;
            }
            return cardrank(cards[i]) < cardrank(other.cards[i]);
        }
        return false;
    }
};

void part1(const std::string& file)
{
    std::vector<hand1> hands;
    lines(file, [&](const std::string& l) {
        char h[6];
        int b;
        std::sscanf(l.c_str(), "%5s %d", h, &b);
        hands.push_back({ h, b });
    });
    std::sort(hands.begin(), hands.end());

    int64_t t = 0;
    for (int i = 0; i < hands.size(); ++i) {
        t += hands[i].bid * (i + 1);
    }
    std::cout << "part 1: " << t << std::endl;
}

struct hand {
    int bid;
    char cards[5];
    hand(std::string hand, int b)
        : bid(b)
    {
        std::map<char, int> rank = { { 'A', 12 }, { 'K', 11 }, { 'Q', 10 }, { 'J', 0 }, { 'T', 9 },
            { '9', 8 }, { '8', 7 }, { '7', 6 }, { '6', 5 }, { '5', 4 }, { '4', 3 }, { '3', 2 }, { '2', 1 } };
        for (int i = 0; i < 5; ++i)
            cards[i] = rank[hand[i]];
    }
    int type() const noexcept
    {
        auto counts = std::array<int, 13> { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        for (auto c : cards)
            counts[c]++;
        std::sort(counts.begin() + 1, counts.end(), [](auto a, auto b) { return !(a < b); });
        switch (counts[0] + counts[1]) {
        case 5:
            return 6;
        case 4:
            return 5;
        case 3:
            return counts[2] == 2 ? 4 : 3;
        case 2:
            return counts[2] == 2 ? 2 : 1;
        default:
            return -1;
        }
    }

    bool operator<(const hand& that) const noexcept
    {
        if (type() != that.type()) {
            return type() < that.type();
        }
        for (int i = 0; i < 5; ++i) {
            if (cards[i] != that.cards[i]) {
                return cards[i] < that.cards[i];
            }
        }
        return false;
    }
};

void part2(const std::string& file)
{
    int64_t t = 0;
    std::vector<hand> hands;
    lines(file, [&](const std::string& l) {
        char h[6];
        int b;
        std::sscanf(l.c_str(), "%5s %d", h, &b);
        hands.push_back(hand { h, b });
    });
    std::sort(hands.begin(), hands.end());
    for (int i = 0; i < hands.size(); ++i) {
        t += hands[i].bid * (i + 1);
    }
    std::cout << "part 2: " << t << std::endl;
}

int main(int argc, char** argv)
{
    part1(argv[1]);
    part2(argv[1]);
    return 0;
}

// part 1: 247961593
// part 2: 248750699