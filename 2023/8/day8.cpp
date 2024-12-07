#include "utils.hpp"
#include <numeric>

auto inst = std::string("LRRRLRRRLRRLRRLRLRRLRRLRRRLRRLRRRLRRRLLRRRLRRRLRRRLRLRRLRRRLRLRRRLRRRLLRLRLRRLRRLLLRRLRRLRRRLLRRRLLRRRLRLRRRLRRRLLRRLRLLRLRRRLRRLRRLRLRLRLRLRLRRRLRLRRRLLRLRRLRRRLRRRLRLRRLRLLLRLRLRLRLRLRRRLLRRLRLRLLRRRLRRLRRRLRRLRRLRRRLLRRLRLRRLRRRLRRLRLRRLRLLRRLLRLRRRLRRLRLLRRRR");
// auto inst = std::string("RL");
char dir(int64_t x)
{
    auto d = inst[x % inst.size()];
    return d;
}

void part1(const std::string& file)
{
    std::map<std::string, std::pair<std::string, std::string>> rules;
    lines(file, [&](auto& line) {
        char n[4], l[4], r[4];
        std::sscanf(line.c_str(), "%3s = (%3s, %3s)", n, &l, &r);
        rules[n] = std::make_pair(l, r);
    });

    int steps = 0;
    std::string position = "AAA";
    for (;;) {
        if (position == "ZZZ") {
            break;
        }
        switch (dir(steps)) {
        case 'L':
            position = rules[position].first;
            break;
        case 'R':
            position = rules[position].second;
            break;
        }
        ++steps;
    }

    std::cout << "part 1: " << steps << std::endl;
}

void part2(const std::string& file)
{
    std::map<std::string, std::pair<std::string, std::string>> rules;
    lines(file, [&](auto& line) {
        char n[4], l[4], r[4];
        std::sscanf(line.c_str(), "%3s = (%3s, %3s)", n, &l, &r);
        rules[n] = std::make_pair(l, r);
    });

    std::vector<std::string> ghosts;
    for (auto& [k, v] : rules) {
        if (k[2] == 'A')
            ghosts.push_back(k);
    }

    for (auto& g : ghosts) {
        std::cout << g << std::endl;
    }

    int64_t gcd = 1;
    for (int g = 0; g < ghosts.size(); ++g) {
        int64_t steps = 0;
        for (;;) {
            if (ghosts[g][2] == 'Z') {
                break;
            }
            switch (dir(steps)) {
            case 'L':
                ghosts[g] = rules[ghosts[g]].first;
                break;
            case 'R':
                ghosts[g] = rules[ghosts[g]].second;
                break;
            }
            ++steps;
        }
        gcd = std::lcm(gcd, steps);
        std::cout << "part 2: " << steps << std::endl;
    }
    std::cout << "part 2: " << gcd << std::endl;
}

int main(int argc, char** argv)
{
    part1(argv[1]);
    part2(argv[1]);
    return 0;
}
