//
// Created by nolan on 01/11/2025.
//

#ifndef TIPE_RAY_TRACING_RAYTRACER_HPP
#define TIPE_RAY_TRACING_RAYTRACER_HPP

#include "Vec3.cpp"
#include "Ray.cpp"
#include "Interval.cpp"
#include <fstream>
#include <cmath>
#include <random>
#include <ctime>
#include <memory>

using namespace std;

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