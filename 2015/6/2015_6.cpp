#include "utils.hpp"

void part1(const std::string& file)
{
    grid g(1000, 1000);
    lines(file, [&](const auto& l) {
        auto [m, ok] = match(R"(^(turn on|turn off|toggle) (\d+),(\d+) through (\d+),(\d+)$)", l);
        if (!ok) {
            std::cout << "No match for " << l << std::endl;
            return;
        }
        auto x1 = std::stoi(m[2]);
        auto y1 = std::stoi(m[3]);
        auto x2 = std::stoi(m[4]);
        auto y2 = std::stoi(m[5]);
        std::cout << m[1] << " " << x1 << "," << y1 << " through " << x2 << "," << y2 << std::endl;
        if (m[1] == "turn on") {
            for (int y = y1; y <= y2; ++y) {
                for (int x = x1; x <= x2; ++x) {
                    g.set({ x, y }, '*');
                }
            }
        } else if (m[1] == "turn off") {
            for (int y = y1; y <= y2; ++y) {
                for (int x = x1; x <= x2; ++x) {
                    g.set({ x, y }, ' ');
                }
            }
        } else if (m[1] == "toggle") {
            for (int y = y1; y <= y2; ++y) {
                for (int x = x1; x <= x2; ++x) {
                    g.set({ x, y }, g.get({ x, y }) == ' ' ? '*' : ' ');
                }
            }
        }
    });

    std::cout << "Lights on: " << g.count('*') << std::endl;
}

void part2(const std::string& file)
{
    grid g(1000, 1000, '\0');
    // std::map<point, int> g;
    lines(file, [&](const auto& l) {
        std::smatch m;
        std::regex re(R"(^(turn on|turn off|toggle) (\d+),(\d+) through (\d+),(\d+)$)");
        if (!std::regex_match(l, m, re)) {
            std::cout << "No match for " << l << std::endl;
            return;
        }
        auto x1 = std::stoi(m[2]);
        auto y1 = std::stoi(m[3]);
        auto x2 = std::stoi(m[4]);
        auto y2 = std::stoi(m[5]);
        std::cout << m[1] << " " << x1 << "," << y1 << " through " << x2 << "," << y2 << std::endl;
        if (m[1] == "turn on") {
            for (int y = y1; y <= y2; ++y) {
                for (int x = x1; x <= x2; ++x) {
                    g.set({ x, y }, g.get({ x, y }) + 1);
                }
            }
        } else if (m[1] == "turn off") {
            for (int y = y1; y <= y2; ++y) {
                for (int x = x1; x <= x2; ++x) {
                    g.set({ x, y }, std::max(g.get({ x, y }) - 1, 0));
                }
            }
        } else if (m[1] == "toggle") {
            for (int y = y1; y <= y2; ++y) {
                for (int x = x1; x <= x2; ++x) {
                    g.set({ x, y }, g.get({ x, y }) + 2);
                }
            }
        }
    });

    int total = 0;
    g.scan([&](grid::point p, const char* d) {
        total += *d;
        return 1;
    });
    std::cout << "Total brightness: " << total << std::endl;
}

int main(int argc, char** argv)
{
    std::cout << "Part 1: " << std::endl;
    // part1(argv[1]);
    std::cout << "Part 2: " << std::endl;
    part2(argv[1]);
    return 0;
}