#include "utils.hpp"

// THIS IS ALL WRONG. THESE ARN NOT INSTRUCTIONS
// THEY ARE EXPRESSIONS. THEY NEED TO BE EVALUATED
// IN ORDER OF DEPENDENCY, NOT IN ORDER OF APPEARANCE
void part1(const std::string& s)
{
    std::map<std::string, uint16_t> wires;
    lines(s, [&](auto l) {
        auto [a, aok] = match(R"(^(?:([a-z]+)|(\d+)) -> ([a-z]+)$)", l);
        if (aok) {
            uint16_t v = 0;
            if (a[1].length() > 0)
                v = wires[a[1]];
            else if (a[2].length() > 0)
                v = std::stoi(a[2]);

            wires.emplace(a[3], v);
            std::cout << a[0] << std::endl;
            std::cout << a[1] << a[2] << " -> " << a[3] << std::endl
                      << std::endl;

            return;
        }
        auto [b, bok] = match(R"(^(?:([a-z]+)|(\d+)) ([A-Z]+) (?:([a-z]+)|(\d+)) -> ([a-z]+)$)", l);
        if (bok) {
            uint16_t v = 0, w = 0;
            if (b[1].length() > 0)
                v = wires[b[1]];
            else if (b[2].length() > 0)
                v = std::stoi(b[2]);

            if (b[4].length() > 0)
                w = wires[b[4]];
            else if (b[5].length() > 0)
                w = std::stoi(b[5]);

            auto op = b[3];
            auto dest = b[6];
            if (op == "AND")
                wires[dest] = v & w;
            else if (op == "OR")
                wires[dest] = v | w;
            else if (op == "LSHIFT")
                wires[dest] = v << w;
            else if (op == "RSHIFT")
                wires[dest] = v >> w;
            else
                std::cout << "unknown operator " << op << '\n';

            // if (dest == "a")
            //     std::cout << "GOT a = " << wires[b[4]] << '\n';
            std::cout << b[0] << std::endl;
            std::cout << b[1] << b[2] << " " << b[3] << " " << b[4] << b[5] << " -> " << b[6] << std::endl
                      << std::endl;
            return;
        }
        auto [c, cok] = match(R"(^NOT ([a-z]+) -> ([a-z]+)$)", l);
        if (cok) {
            auto v = wires[c[1]];
            wires[c[2]] = ~v;
            return;
        }
        std::cout << "skipping line " << l << std::endl;
    });

    std::cout << "WIRES:" << '\n';
    for (auto& [k, v] : wires) {
        std::cout << k << " = " << v << '\n';
    }
    std::cout << "a = " << wires["a"] << '\n';
}

int main(int argc, char** argv)
{
    part1(argv[1]);
    return 0;
}