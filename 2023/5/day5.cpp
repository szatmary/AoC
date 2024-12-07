#include "input.hpp"
// #include "example.hpp"
#include "utils.hpp"
#include <future>
// void applyX(std::map<uint64_t, uint64_t>& location, const std::vector<std::vector<uint64_t>>& g)
// {
//     int64_t val;
//     for (auto m : g) {
//         std::cout << m[0] << " " << m[1] << " " << m[2] << std::endl;
//         for (int i = 0; i < m[2]; ++i) {
//             auto source = m[0] + i;
//             auto iter = location.find(source);
//             auto val = iter == location.end() ? source : iter->second;
//             location.emplace(m[0] + i, val);
//         }
//     }
// }

// void applyY(std::vector<uint32_t>& location, const std::vector<std::vector<uint64_t>>& g)
// {
//     int64_t val;
//     for (auto m : g) {
//         std::cout << m[0] << " " << m[1] << " " << m[2] << std::endl;
//         for (int i = 0; i < m[2]; ++i) {
//             auto dest = m[1] + i;
//             location[dest] = m[0] + i;
//         }
//     }
// }

// void part1()
// {
//     std::vector<uint32_t> location;
//     std::cout << "init" << std::endl;
//     location.resize(4294967295);
//     for (size_t i = 0; i <= 4294967295; ++i) {
//         location[i] = i;
//     }
//     std::cout << "seed_to_soil" << std::endl;
//     applyY(location, seed_to_soil);
//     std::cout << "soil_to_fertilizer" << std::endl;
//     applyY(location, soil_to_fertilizer);
//     std::cout << "fertilizer_to_water" << std::endl;
//     applyY(location, fertilizer_to_water);
//     std::cout << "water_to_light" << std::endl;
//     applyY(location, water_to_light);
//     std::cout << "light_to_temperature" << std::endl;
//     applyY(location, light_to_temperature);
//     std::cout << "temperature_to_humidity" << std::endl;
//     applyY(location, temperature_to_humidity);
//     std::cout << "humidity_to_location" << std::endl;
//     applyY(location, humidity_to_location);

//     uint32_t low = 4294967295;
//     for (auto s : seeds) {
//         low = std::min(low, location[s]);
//     }
//     std::cout << "low: " << low << std::endl;
// }

// uint32_t XtoY(std::vector<std::vector<uint64_t>> g, uint64_t x)
// {
//     auto loc = std::vector<uint32_t>(4294967295, 0);
//     for (auto m : g) {
//         std::cout << m[0] << " " << m[1] << " " << m[2] << std::endl;
//         for (int i = 0; i < m[2]; ++i) {
//             auto dest = m[1] + i;
//             loc[dest] = m[0] + i;
//         }
//     }
//     return loc[x] == 0 ? x : loc[x];
// }

inline uint32_t XtoY(std::vector<std::vector<uint32_t>> g, uint32_t x)
{
    for (auto m : g) {
        auto start = m[1];
        auto end = m[1] + m[2];
        if (x >= start && x < end) {
            x = m[0] + (x - start);
            break;
        }
    }
    return x;
}

void part1()
{
    uint32_t lowest = 4294967295;
    for (uint32_t y : seeds) {
        y = XtoY(seed_to_soil, y);
        y = XtoY(soil_to_fertilizer, y);
        y = XtoY(fertilizer_to_water, y);
        y = XtoY(water_to_light, y);
        y = XtoY(light_to_temperature, y);
        y = XtoY(temperature_to_humidity, y);
        y = XtoY(humidity_to_location, y);
        lowest = std::min(lowest, y);
    }

    // uint32_t low = 4294967295;
    // for (auto s : seeds) {
    //     low = std::min(low, location[s]);
    // }
    std::cout << "part1 low: " << lowest << std::endl;
}

// struct run {
//     int64_t start;
//     int64_t delta;
//     struct run* next = nullptr;
//     uint32_t size()
//     {
//         if (next == nullptr) {
//             return 4294967295 - start;
//         }
//         return next->start - start;
//     }
//     int64_t end()
//     {
//         return start + size();
//     }
//     void cleave(int64_t x, int64_t d)
//     {
//         next = new run { x, delta + d, next };
//     }
// };

// inline void XtoY(std::vector<std::vector<uint32_t>> g, run* r)
// {
//     std::sort(g.begin(), g.end(), [](const std::vector<uint32_t>& a, const std::vector<uint32_t>& b) {
//         return a[0] > b[0];
//     });

//     for (auto m : g) {
//         auto start = static_cast<int64_t>(m[1]);
//         auto size = m[2];
//         auto delta = static_cast<int64_t>(m[0]) - static_cast<int64_t>(m[1]);
//         while (size > 0) {
//             if (r->end() >= start) {
//                 std::cout << "cleaving " << start << " " << delta << std::endl;
//                 r->cleave(start, delta);
//             }
//             size -= std::max(size, r->size());
//             r = r->next;
//         }
//     }
// }

// void part2()
// {
//     // std::vector<seed> s;
//     // for (int a = 0; a < seeds.size(); a += 2) {
//     //     s.push_back(seed { seeds[a], seeds[a], seeds[a] + seeds[a + 1] });
//     // }

//     auto r = new run { 0, 0 };

//     XtoY(seed_to_soil, r);
//     XtoY(soil_to_fertilizer, r);
//     // XtoY(fertilizer_to_water, r);
//     // XtoY(water_to_light, r);
//     // XtoY(light_to_temperature, r);
//     // XtoY(temperature_to_humidity, r);
//     // XtoY(humidity_to_location, r);

//     for (auto rr = r; rr != nullptr; rr = rr->next) {
//         std::cout << rr->start << " " << rr->end() << std::endl;
//     }
//     // std::sort(y.begin(), y.end(), [](const seed& a, const seed& b) {
//     //     return a.id < b.id;
//     // });
//     // for (auto r : y) {
//     //     std::cout << r.id << " " << r.start << "-" << r.size << std::endl;
//     // }
// }

void part2()
{
    std::vector<std::future<uint32_t>> lows;
    for (int i = 0; i < seeds.size(); i += 2) {
        uint32_t start = seeds[i];
        uint32_t len = seeds[i + 1];
        lows.push_back(std::async(std::launch::async, [i, start, len]() -> uint32_t {
            uint32_t end = start + len;
            uint32_t lowest = 4294967295;
            for (uint32_t s = 0; s < len; ++s) {
                if ((s & 0x3ffff) == 0) {
                    std::cout << i << ":\t" << s / static_cast<double>(len) << std::endl;
                }
                uint32_t y = start + s;
                y = XtoY(seed_to_soil, y);
                y = XtoY(soil_to_fertilizer, y);
                y = XtoY(fertilizer_to_water, y);
                y = XtoY(water_to_light, y);
                y = XtoY(light_to_temperature, y);
                y = XtoY(temperature_to_humidity, y);
                y = XtoY(humidity_to_location, y);
                lowest = std::min(lowest, y);
            }
            return lowest;
        }));
    }

    uint32_t lowest = 4294967295;
    for (auto& f : lows) {
        auto l = f.get();
        std::cout << l << std::endl;
        lowest = std::min(lowest, l);
    }

    std::cout << "part2 low: " << lowest << std::endl;
}

int main(int argc, char** argv)
{
    part1();
    part2();
    return 0;
}

// 157211394 part 1
// 50855035 part 2