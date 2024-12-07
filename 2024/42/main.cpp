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

class Matrix : public std::vector<std::string> {
public:
    void read_file(const std::string& filename)
    {
        std::vector<std::string> lines;
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            push_back({ line });
        }
    }

    char get(int x, int y) const
    {
        if (y >= size() || x >= (*this)[y].size() || x < 0 || y < 0) {
            return ' ';
        }

        return (*this)[y][x];
    }

    std::string get3(int x1, int y1, int x2, int y2, int x3, int y3) const
    {
        return std::string({ get(x1, y1), get(x2, y2), get(x3, y3) });
    }

    std::string get4(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) const
    {
        return std::string({ get(x1, y1), get(x2, y2), get(x3, y3), get(x4, y4) });
    }

    int find_xmas(int x, int y)
    {
        auto a = get4(x, y, x + 1, y + 0, x + 2, y + 0, x + 3, y + 0); // left to right
        auto b = get4(x, y, x + 0, y - 1, x + 0, y - 2, x + 0, y - 3); // bottom to top
        auto c = get4(x, y, x - 1, y - 1, x - 2, y - 2, x - 3, y - 3); // bottom to top left diag
        auto d = get4(x, y, x + 1, y - 1, x + 2, y - 2, x + 3, y - 3); // bottom to top right diag
        std::printf("%d %d '%s' '%s' '%s' '%s'\n", x, y, a.c_str(), b.c_str(), c.c_str(), d.c_str());
        return (a == "XMAS" ? 1 : 0)
            + (b == "XMAS" ? 1 : 0)
            + (c == "XMAS" ? 1 : 0)
            + (d == "XMAS" ? 1 : 0)
            + (a == "SAMX" ? 1 : 0)
            + (b == "SAMX" ? 1 : 0)
            + (c == "SAMX" ? 1 : 0)
            + (d == "SAMX" ? 1 : 0);
    }

    int find_x_mas(int x, int y)
    {
        auto a = get3(x - 1, y - 1, x - 0, y - 0, x + 1, y + 1);
        auto b = get3(x + 1, y - 1, x + 0, y + 0, x - 1, y + 1);
        return ((a == "MAS" || a == "SAM") && (b == "MAS" || b == "SAM")) ? 1 : 0;
    }
};

int main(int arvc, char* argv[])
{
    if (arvc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    Matrix matrix;
    matrix.read_file(argv[1]);
    int total = 0;
    for (int y = 0; y < matrix[0].size(); ++y) {
        for (int x = 0; x < matrix.size(); ++x) {
            auto found = matrix.find_x_mas(x, y);
            std::printf("%d %d %d\n", x, y, found);
            total += found;
        }
    }

    std::cout << total << std::endl;

    return 0;
}

// 2280 too low
// 2478 too low