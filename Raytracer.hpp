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
inline uniform_real_distribution<> alea(0, 1);

inline double random_double() {
    return alea(engine);
}

inline int random_sign() {
    return alea(engine) <= 1/2 ? 1 : -1;
}

inline double random_double(const double min, const double max) {
    return min + (max-min)*random_double();
}

#endif //TIPE_RAY_TRACING_RAYTRACER_HPP