//
// Created by nolan on 01/11/2025.
//

#ifndef TIPE_RAY_TRACING_RAYTRACER_HPP
#define TIPE_RAY_TRACING_RAYTRACER_HPP

#include <fstream>
#include <cmath>
#include <random>

using namespace std;

constexpr double infinite = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degree) {
    return degree*pi/180.0;
}

inline double random_double() {
    return rand() / (RAND_MAX + 1.);
}

inline double random_double(const double min, const double max) {
    return min + (max-min)*random_double();
}

#endif //TIPE_RAY_TRACING_RAYTRACER_HPP