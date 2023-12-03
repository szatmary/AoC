#pragma once

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

void lines(const std::string& file, auto line)
{
    std::string l;
    std::ifstream f(file);
    while (std::getline(f, l)) {
        line(l);
    }
}

std::vector<std::string> split(const std::string& input, const std::string& regex)
{
    // passing -1 as the submatch index parameter performs splitting
    std::regex re(regex);
    std::sregex_token_iterator first { input.begin(), input.end(), re, -1 };
    return { first, {} };
}

class grid {
private:
    // don't forget data is indexed by y then x, not x then y!
    std::vector<std::string> _data;

public:
    struct point {
        int x;
        int y;
        auto operator<=>(const point& p) const
        {
            return std::tie(x, y) <=> std::tie(p.x, p.y);
        };
    };

    grid() = default;

    static grid loadfromfile(const std::string& file)
    {
        grid g;
        std::string l;
        std::ifstream f(file);
        while (std::getline(f, l)) {
            g._data.push_back(l);
        }
        return g;
    }

    int max_width() const noexcept
    {
        return std::max_element(_data.begin(), _data.end(), [](const auto& a, const auto& b) {
            return a.size() < b.size();
        })->size();
    }

    int min_width() const noexcept
    {
        return std::min_element(_data.begin(), _data.end(), [](const auto& a, const auto& b) {
            return a.size() < b.size();
        })->size();
    }

    bool is_const_width() const noexcept
    {
        return std::equal(_data.begin(), _data.end(), _data.begin() + 1, [](const auto& a, const auto& b) {
            return a.size() == b.size();
        });
    }

    int width() const noexcept { return max_width(); }
    int height() const noexcept { return _data.size(); }
    bool is_in_bounds(point p) const noexcept { return p.y >= 0 && p.y < _data.size() && p.x >= 0 && p.x < _data[p.y].size(); }
    char at(point p) const noexcept { return is_in_bounds(p) ? _data[p.y][p.x] : '\0'; }
    char operator[](point p) const noexcept { return at(p); }

    // scans left to right, top to bottom
    void scan(std::function<int(point p, const char*)> fn) const noexcept
    {
        for (int y = 0; y < _data.size(); ++y) {
            for (int x = 0; x < _data[y].size();) {
                auto step = fn({ x, y }, &_data[y][x]);
                if (step == -1) {
                    return; // bail out
                }
                step = std::max(step, 1);
                x += step;
            }
        }
    }

    // scan horizontally left to right
    void scan_horz(int x1, int x2, int y, std::function<void(int, int, const char*)> fn) const noexcept
    {
        if (x1 > x2) {
            // scan in reverse
            for (int i = x1; i >= x2; --i) {
                if (!is_in_bounds({ i, y }))
                    continue;
                fn(i, y, &_data[y][i]);
            }
        }

        for (int i = x1; i <= x2; ++i) {
            if (!is_in_bounds({ i, y }))
                continue;
            fn(i, y, &_data[y][i]);
        }
    }

    // scan vertically top to bottom
    void scan_vert(int x, int y1, int y2, std::function<void(int, int, const char*)> fn) const noexcept
    {
        if (y1 > y2) {
            // scan in reverse
            for (int i = y1; i >= y2; --i) {
                if (!is_in_bounds({ x, i }))
                    continue;
                fn(x, i, &_data[i][x]);
            }
        }

        for (int i = y1; i <= y2; ++i) {
            if (!is_in_bounds({ x, i }))
                continue;
            fn(x, i, &_data[i][x]);
        }
    }

    // scans the perimeter of a box
    void scan_bounding_box(point a, point b, std::function<void(int, int, const char*)> fn) const noexcept
    {
        // tttt
        // l..r
        // bbbb
        scan_horz(a.x, b.x, a.y, fn); // top
        scan_horz(a.x, b.x, b.y, fn); // bottom
        scan_vert(a.x, a.y + 1, b.y - 1, fn); // left
        scan_vert(b.x, a.y + 1, b.y - 1, fn); // right
    }

    // retuns a subgrid
    grid sub(point a, point b) const noexcept
    {
        grid g;
        for (int i = a.y; i <= b.y; ++i) {
            g._data.push_back(_data[i].substr(a.x, b.x - a.x + 1));
        }
        return g;
    }

    bool contains(std::function<bool(char c)> fn) const noexcept
    {
        bool found = false;
        scan([&](point p, const char* c) {
            if (fn(*c)) {
                found = true;
                return -1;
            }
            return 1;
        });
        return found;
    }

    bool contains(char c) const noexcept
    {
        return contains([&](char d) {
            return d == c;
        });
    }
};