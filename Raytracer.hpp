//
// Created by nolan on 01/11/2025.
//

#ifndef TIPE_RAY_TRACING_RAYTRACER_HPP
#define TIPE_RAY_TRACING_RAYTRACER_HPP

#include <cmath>
#include <cstdint>

using namespace std;

inline constexpr double infinite = std::numeric_limits<double>::infinity();
inline constexpr double pi = 3.1415926535897932385;

inline double degrees_to_radians(const double degree) {
    return degree*pi/180.0;
}

inline thread_local uint64_t state = 0;

// Initialize RNG state for each thread
inline void seed_xorshift64(uint64_t seed) {
    if (seed == 0) seed = 88172645463325252ULL; // avoid zero state
    state = seed;
}

inline uint64_t xorshift64() {
    state ^= state << 13;
    state ^= state >> 7;
    state ^= state << 17;

    return state;
}

constexpr uint64_t MAX_UINT64 = UINT64_C(18446744073709551615);
constexpr uint64_t SHIFT_UINT64 = UINT64_C(9223372036854775808);

inline double random_double_uniform() {
    return xorshift64()/MAX_UINT64;
}

inline double random_double_uniform(const double min, const double max) {
    return min + random_double_uniform() * (max - min);
}
inline int random_int(const int min, const int max) {
    return static_cast<int>(random_double_uniform(min, max));
}

inline int random_sign() {
    return random_double_uniform() <= 1./2 ? 1 : -1;
}

inline double random_double_gaussian(const double mean, const double std_deviation) {
    const double u1 = random_double_uniform();
    const double u2 = random_double_uniform();
    const double z0 = sqrt(-2 * log(u1))*cos(2*pi*u2);

    return mean + std_deviation*z0;
}

inline double random_double_gaussian() {
    return random_double_gaussian(0, 1);
}

#endif //TIPE_RAY_TRACING_RAYTRACER_HPP
