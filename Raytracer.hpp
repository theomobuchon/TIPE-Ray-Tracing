//
// Created by nolan on 01/11/2025.
//

#ifndef TIPE_RAY_TRACING_RAYTRACER_HPP
#define TIPE_RAY_TRACING_RAYTRACER_HPP

#include <sstream>
#include <vector>
#include <limits>

inline constexpr float infinite = std::numeric_limits<float>::infinity();
inline constexpr float pi = 3.1415926535897932385f;

inline float degrees_to_radians(const float degree) {
    return degree*pi/180.0f;
}

inline std::vector<std::string> splitString(const std::string& str, const char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

#endif //TIPE_RAY_TRACING_RAYTRACER_HPP
