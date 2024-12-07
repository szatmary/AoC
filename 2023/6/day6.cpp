// Time:        40     81     77     72
// Distance:   219   1012   1365   1089

#include "utils.hpp"

std::vector<std::pair<int, int>> races {
    { 40, 219 },
    { 81, 1012 },
    { 77, 1365 },
    { 72, 1089 }
};

// Time:      7  15   30
// Distance:  9  40  200
std::vector<std::pair<int, int>> example {
    { 7, 9 },
    { 15, 40 },
    { 30, 200 }
};

void part1()
{
    auto moe = 1;
    for (auto r : races) {
        auto c = 0;
        for (int i = 1; i < r.first; ++i) {
            auto distance = (r.first - i) * i;
            if (distance > r.second) {
                // std::cout << "hold for " << i << std::endl;
                c++;
            }
        }
        moe = moe * c;
        std::cout << "ways to win: " << c << std::endl;
    }
    std::cout << "moe: " << moe << std::endl;
}

void part2()
{
    int64_t time = 40817772;
    int64_t distance = 219101213651089;

    auto waystowin = 0;
    for (int i = 1; i < time; ++i) {
        auto traveled = (time - i) * i;
        if (traveled > distance) {
            waystowin++;
        }
    }
    std::cout << "ways to win: " << waystowin << std::endl;
    // 953734 too low
    // 28101347
}

int main(int argc, char** argv)
{
    part1();
    part2();
    return 0;
}