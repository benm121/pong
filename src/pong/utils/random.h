#pragma once
#include <random>

namespace rnd {

inline int randInt(int min, int max) {
    static std::random_device rd;
    static std::minstd_rand gen(rd());
    static std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

inline float randFloat(float min, float max) {
    static std::random_device rd;
    static std::minstd_rand gen(rd());
    static std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

inline bool flipCoin(void) {
    return randInt(0, 1);
}


} // namespace rnd

