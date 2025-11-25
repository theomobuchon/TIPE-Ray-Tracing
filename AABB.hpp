//
// Created by nolan on 22/11/2025.
//

#ifndef TIPE_RAY_TRACING_AABB_HPP
#define TIPE_RAY_TRACING_AABB_HPP

#include "Interval.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"

// Axis-Aligned Bounding Box
class AABB {
public:
    AABB() = default; // Empty AABB
    AABB(const Interval &x, const Interval &y, const Interval &z); // AABB defined with intervals for coordinates
    AABB(const Point3 &a, const Point3 &b); // Create an AABB with two points corresponding to his extrema
    AABB(const AABB &b1, const AABB &b2);  // Create an AABB by merging two AABB
    [[nodiscard]] bool hit(const Ray &r, Interval ray_t) const;
    [[nodiscard]] const Interval &axis_interval(int n) const;

protected:
    Interval m_x, m_y, m_z;
};


#endif //TIPE_RAY_TRACING_AABB_HPP