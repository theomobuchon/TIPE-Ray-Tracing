//
// Created by nolan on 16/12/2025.
//

#ifndef TIPE_RAY_TRACING_RECTANGLE_HPP
#define TIPE_RAY_TRACING_RECTANGLE_HPP

#include "Hittable.hpp"

class Rectangle: public Hittable {
public:
    Rectangle(const Point3 &origin, const Vec3 &u, const Vec3 &v, const std::shared_ptr<Material>& material);
    Rectangle &operator=(const Rectangle &r) = default;
    bool hit(const Ray &ray, Interval int_valid, Hit_record &rec) const override;
    [[nodiscard]] AABB bounding_box() const override;

protected:
    Point3 m_origin;
    Vec3 m_u;
    Vec3 m_v;
    Vec3 m_normal;
    AABB m_bbox;
    std::shared_ptr<Material> m_material;
};


#endif //TIPE_RAY_TRACING_RECTANGLE_HPP