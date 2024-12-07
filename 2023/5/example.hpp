#include <vector>
auto seeds = std::vector<uint32_t> {
    79,
    14,
    55,
    13,
};

auto seed_to_soil = std::vector<std::vector<uint32_t>> {
    {
        50,
        98,
        2,
    },
    {
        52,
        50,
        48,
    },
};
auto soil_to_fertilizer = std::vector<std::vector<uint32_t>> {
    {
        0,
        15,
        37,
    },
    {
        37,
        52,
        2,
    },
    {
        39,
        0,
        15,
    },

};
auto fertilizer_to_water = std::vector<std::vector<uint32_t>> {
    {
        49,
        53,
        8,
    },
    {
        0,
        11,
        42,
    },
    {
        42,
        0,
        7,
    },
    {
        57,
        7,
        4,
    },

};
auto water_to_light = std::vector<std::vector<uint32_t>> {
    {
        88,
        18,
        7,
    },
    {
        18,
        25,
        70,
    },

};
auto light_to_temperature = std::vector<std::vector<uint32_t>> {
    {
        45,
        77,
        23,
    },
    {
        81,
        45,
        19,
    },
    {
        68,
        64,
        13,
    },

};
auto temperature_to_humidity = std::vector<std::vector<uint32_t>> {
    {
        0,
        69,
        1,
    },
    {
        1,
        0,
        69,
    },

};
auto humidity_to_location = std::vector<std::vector<uint32_t>> {
    {
        60,
        56,
        37,
    },
    {
        56,
        93,
        4,
    },
};