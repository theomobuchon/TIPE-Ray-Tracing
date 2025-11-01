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
#include <memory>

constexpr double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degree) {
    return degree*pi/180.0;
}

#endif //TIPE_RAY_TRACING_RAYTRACER_HPP