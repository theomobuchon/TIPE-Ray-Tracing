//
// Created by nolan on 09/03/2026.
//

#ifndef TIPE_RAYTRACING_RANDOM_HPP
#define TIPE_RAYTRACING_RANDOM_HPP

#include <cmath>
#include <cstdint>

// Un générateur de nombres aléatoires
// Attention, passez TOUJOURS un RNG en paramètre par référence (non constante), sous peine d'avoir des valeurs aléatoires identiques d'une fonction à l'autre
struct RNG {
    unsigned int state{};
    bool has_spare = false;
    float spare{};

    unsigned int next_uint();

    float next_uniform();
    float next_uniform(float min, float max);

    float next_gaussian();
    float next_gaussian(float mean, float stddev);

    int next_int(int min, int max);
};

inline unsigned int RNG::next_uint() {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

inline float RNG::next_uniform() {
    return ((float)next_uint() + 1.0f) * (1.0f / 4294967296.0f);
}

inline float RNG::next_gaussian() {

    if (has_spare) {
        has_spare = false;
        return spare;
    }

    const float u1 = fmaxf(next_uniform(), 1e-7f);
    const float u2 = next_uniform();

    const float r = sqrtf(-2.0f * logf(u1));
    const float theta = 2.0f * 3.14159265359f * u2;

    spare = r * sinf(theta);
    has_spare = true;

    return r * cosf(theta);
}

inline int RNG::next_int(const int min, const int max) {
    const auto range = (unsigned int)(max - min + 1);
    const unsigned int limit = UINT32_MAX - (UINT32_MAX % range);

    unsigned int r;

    do {
        r = next_uint();
    } while (r >= limit);

    return min + (r % range);
}

inline float RNG::next_uniform(float min, float max) {
    return min + (max - min) * next_uniform();
}

inline float RNG::next_gaussian(const float mean, const float stddev) {
    return mean + stddev * next_gaussian();
}

inline unsigned int wang_hash(unsigned int seed) {
    seed = (seed ^ 61) ^ (seed >> 16);
    seed *= 9;
    seed = seed ^ (seed >> 4);
    seed *= 0x27d4eb2d;
    seed = seed ^ (seed >> 15);
    return seed;
}

#endif //TIPE_RAYTRACING_RANDOM_HPP