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

struct point {
    int x = 0;
    int y = 0;
    auto operator<=>(const point& p) const
    {
        return std::tie(x, y) <=> std::tie(p.x, p.y);
    };
};

class Matrix {
private:
    std::vector<std::string> data;

public:
    void read_file(const std::string& filename)
    {
        std::vector<std::string> lines;
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            data.push_back({ line });
        }
    }

    void print() const
    {
        for (const auto& line : data) {
            std::cout << line << '\n';
        }
    }

    bool in_bounds(const point& p) const noexcept
    {
        return p.y >= 0 && p.y < data.size() && p.x >= 0 && p.x < data[p.y].size();
    }

    int height() const noexcept { return data.size(); }
    int width(int i) const noexcept
    {
        if (i < data.size() && i >= 0)
            return data[i].size();
        return 0;
    }
    int width()
    {
        return std::accumulate(data.begin(), data.end(), 0, [](int acc, const std::string& s) {
            return std::max(acc, (int)s.size());
        });
    }

    char get(const point& p, char default_value = 0) const
    {
        if (!in_bounds(p))
            return default_value;

        return data[p.y][p.x];
    }

    void for_each(std::function<bool(point, char)> func)
    {
        for (int y = 0; y < height(); ++y) {
            for (int x = 0; x < width(y); ++x) {
                func({ x, y }, get({ x, y }));
            }
        }
    }
};

struct guard {
    char direction = 0; // ^, v, <, >
    point pos;
    guard operator++()
    {
        switch (direction) {
        case '^':
            return { direction, { pos.x, pos.y - 1 } };
        case 'v':
            return { direction, { pos.x, pos.y + 1 } };
        case '<':
            return { direction, { pos.x - 1, pos.y } };
        case '>':
            return { direction, { pos.x + 1, pos.y } };
        default:
            std::cerr << "Invalid direction: " << direction << std::endl;
            std::abort();
        }
    }
    void turn_right()
    {
        switch (direction) {
        case '^':
            direction = '>';
            break;
        case 'v':
            direction = '<';
            break;
        case '<':
            direction = '^';
            break;
        case '>':
            direction = 'v';
            break;
        }
    }
};

int main(int arvc, char* argv[])
{
    if (arvc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    Matrix m;
    m.read_file(argv[1]);
    // m.print();

    // find the guard
    guard g;
    m.for_each([&g](point p, char c) {
        if (c == '^' || c == 'v' || c == '<' || c == '>') {
            g.direction = c;
            g.pos = p;
            return false;
        }
        return true;
    });

    std::printf("Found guard at (%d, %d)\n", g.pos.x, g.pos.y);
    std::set<point> visited;
    visited.insert(g.pos);
    for (;;) {
        std::printf("Guard at (%d, %d)\n", g.pos.x, g.pos.y);
        guard next = ++g;
        char c = m.get(next.pos);
        if (c == 0) {
            break;
        }
        if (c == '#') {
            std::cout << "Turning right at (" << next.pos.x << ", " << next.pos.y << ")\n";
            g.turn_right();
        } else {
            g = next;
            visited.insert(g.pos);
        }
    }

    std::cout << visited.size() << '\n';

    return 0;
}
// !84