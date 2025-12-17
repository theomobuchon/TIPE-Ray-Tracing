//
// Created by nolan on 01/11/2025.
//

#ifndef TIPE_RAY_TRACING_RAYTRACER_HPP
#define TIPE_RAY_TRACING_RAYTRACER_HPP

#include <cmath>
#include <random>

using namespace std;

inline constexpr double infinite = std::numeric_limits<double>::infinity();
inline constexpr double pi = 3.1415926535897932385;

inline double degrees_to_radians(const double degree) {
    return degree*pi/180.0;
}

inline random_device rd;
inline mt19937 engine(rd());

inline uniform_real_distribution uniform_distribution(0., 1.);

inline double random_double_uniform() {
    return uniform_distribution(engine);
}

inline double random_double_uniform(const double min, const double max) {
    return min + random_double_uniform() * (max - min);
}

inline uniform_int_distribution uniform_distribution_int(0, 1);

inline int random_int(const int min, const int max) {
    return min + uniform_distribution_int(engine) * (max - min);
}

inline int random_sign() {
    return random_double_uniform() <= 1./2 ? 1 : -1;
}

inline normal_distribution gaussian_distribution(0., 1.);

inline double random_double_gaussian() {
    return gaussian_distribution(engine);
}

inline double random_double_gaussian(const double mean, const double std_deviation) {
    return gaussian_distribution(engine)*sqrt(std_deviation) + mean;
}

#endif //TIPE_RAY_TRACING_RAYTRACER_HPP
