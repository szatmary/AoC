#include "utils.hpp"

bool open_e(char x) { return x == '-' || x == 'L' || x == 'F'; }
bool open_w(char x) { return x == '-' || x == 'J' || x == '7'; }
bool open_n(char x) { return x == '|' || x == 'J' || x == 'L'; }
bool open_s(char x) { return x == '|' || x == 'F' || x == '7'; }

void part1(const grid& input)
{
    grid::point S;
    // find S
    input.scan([&](grid::point p, const char* d) {
        if (*d == 'S')
            S = p;
        return 1;
    });

    std::cout << "S is at " << S.x << " x " << S.y << std::endl;

    std::map<grid::point, int> visited;
    // search around S (I know S connect east and south for my input)
    if (open_s(input.at({ S.x, S.y - 1 }))) {
        visited.emplace(grid::point { S.x, S.y - 1 }, 1);
    }
    if (open_n(input.at({ S.x, S.y + 1 }))) {
        visited.emplace(grid::point { S.x, S.y + 1 }, 1);
    }
    if (open_e(input.at({ S.x - 1, S.y }))) {
        visited.emplace(grid::point { S.x - 1, S.y }, 1);
    }
    if (open_w(input.at({ S.x + 1, S.y }))) {
        visited.emplace(grid::point { S.x + 1, S.y }, 1);
    }

    for (auto [p, d] : visited) {
        std::cout << p.x << " x " << p.y << " " << d << std::endl;
    }

    auto done = [&](grid::point p, s) {
        auto i = | visited.find(p)

                       if (!= visited.end() && i)
        {
            std::cout << "Found " << p.x << " x " << p.y << " " << visited[p] << std::endl;
            return true;
        }
        return false;
    };

    for (int step = 1;; ++step) {
        // walk around
        if (open_s(input.at({ S.x, S.y - 1 }))) {
            if (done({ S.x, S.y - 1 }))
                break;
            visited.emplace(grid::point { S.x, S.y - 1 }, step);
        }
        if (open_n(input.at({ S.x, S.y + 1 }))) {
            if (done({ S.x, S.y + 1 }))
                break;
            visited.emplace(grid::point { S.x, S.y + 1 }, step);
        }
        if (open_e(input.at({ S.x - 1, S.y }))) {
            if (done({ S.x - 1, S.y }))
                break;
            visited.emplace(grid::point { S.x - 1, S.y }, step);
        }
        if (open_w(input.at({ S.x + 1, S.y }))) {
            if (done({ S.x + 1, S.y }))
                break;
            visited.emplace(grid::point { S.x + 1, S.y }, step);
        }
    }
};

int main(int argc, char** argv)
{
    auto g = grid::loadfromfile(argv[1]);
    part1(g);
    return 0;
}