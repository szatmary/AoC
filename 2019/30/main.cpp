#include "util.hpp"
int main(int argc, char* argv[])
{
    auto lines = ReadFile("input.txt");
    SparceMatrix<int> m;

    auto w1 = split(lines[0], ",");
    int x = 0, y = 0;
    for (auto& s : w1) {
        auto d = s[0];
        auto l = std::stoi(s.substr(1));
        for (int i = 0; i < l; ++i) {
            switch (d) {
            case 'R':
                for (int i = 0; i < l; i++) {
                    m.set(x, y, m.get(x, y) + 1);
                    x++;
                }
                break;
            case 'L':
                for (int i = 0; i < l; i++) {
                    m.set(x, y, m.get(x, y) + 1);
                    x--;
                }
                break;
            case 'U':
                for (int i = 0; i < l; i++) {
                    m.set(x, y, m.get(x, y) + 1);
                    y++;
                }
                break;
            case 'D':
                for (int i = 0; i < l; i++) {
                    m.set(x, y, m.get(x, y) + 1);
                    y--;
                }
                break;
            }
            m.set(x, y, 1);
        }
    }
}