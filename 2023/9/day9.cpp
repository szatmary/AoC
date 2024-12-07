#include "utils.hpp"

std::vector<int> sub(const std::vector<int>& in)
{
    std::vector<int> nums;
    for (int i = 1; i < in.size(); ++i) {
        nums.push_back(in[i] - in[i - 1]);
    }
    return nums;
}

bool allzero(const std::vector<int>& nums)
{
    return std::all_of(nums.begin(), nums.end(), [](int i) { return i == 0; });
}

void part1(const std::string& file)
{
    int64_t t = 0;
    lines(file, [&](const std::string& line) {
        std::vector<int> nums;
        auto snums = split(line, R"(\s+)");
        std::transform(snums.begin(), snums.end(), std::back_inserter(nums), [](const std::string& s) {
            return std::stoi(s);
        });

        std::vector<std::vector<int>> tree;
        tree.push_back(nums);
        while (!allzero(tree.back())) {
            tree.push_back(sub(tree.back()));
        }

        tree.back().push_back(0);
        for (auto i = tree.rbegin() + 1; i != tree.rend(); ++i) {
            i->push_back((i - 1)->back() + i->back());
        }

        t += tree.front().back();
    });
    std::cout << "part 1: " << t << std::endl;

    // 906107234 too low
    // 1725987467 correct
}

void part2(const std::string& file)
{
    int64_t t = 0;
    lines(file, [&](const std::string& line) {
        std::vector<int> nums;
        auto snums = split(line, R"(\s+)");
        std::transform(snums.begin(), snums.end(), std::back_inserter(nums), [](const std::string& s) {
            return std::stoi(s);
        });

        std::vector<std::vector<int>> tree;
        tree.push_back(nums);
        while (!allzero(tree.back())) {
            tree.push_back(sub(tree.back()));
        }

        tree.back().push_back(0);
        for (auto i = tree.rbegin() + 1; i != tree.rend(); ++i) {
            i->push_back(i->front() - (i - 1)->back());
        }

        std::cout << "tree: " << std::endl;
        for (auto& v : tree) {
            for (auto& i : v) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
        t += tree.front().back();
    });
    std::cout << "part 2: " << t << std::endl;
    // 19697 too high
    // -19697 not correct
    // 971 ?
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input file>" << std::endl;
        return -1;
    }

    part1(argv[1]);
    part2(argv[1]);
    return 0;
}