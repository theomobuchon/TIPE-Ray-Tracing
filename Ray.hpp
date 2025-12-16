//
// Created by nolan on 14/10/2025.
//

#ifndef TIPE_RAY_TRACING_GRAPHICS_HPP
#define TIPE_RAY_TRACING_GRAPHICS_HPP

#include "Vec3.hpp"

class Ray {
public:
    Ray();
    Ray(const Point3 &origin, const Vec3 &direction);
    Ray &operator=(const Ray &ray);
    [[nodiscard]] Point3 at(double t) const;
    [[nodiscard]] Point3 origin() const;
    [[nodiscard]] Vec3 direction() const;

protected:
    Point3 m_origin;
    Vec3 m_dir;
};


#endif //TIPE_RAY_TRACING_GRAPHICS_HPP