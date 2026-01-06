//
// Created by nolan on 16/12/2025.
//

#include "Rectangle.hpp"

Rectangle::Rectangle(const Point3 &origin, const Vec3 &u, const Vec3 &v, const std::shared_ptr<Material> &material): m_origin(origin), m_u(u), m_v(v), m_material(material) {
    m_normal = normalised(p_vect(u, v));
    m_bbox = AABB(origin + m_normal * 0.001, origin + u + v - m_normal * 0.001);
}

bool Rectangle::hit(const Ray &ray, Interval int_valid, Hit_record &rec) const {
    const Vec3 h = p_vect(ray.direction(), m_v);
    const double a = p_scal(m_u, h);
    if (a == 0) return false;

    const Vec3 s = ray.origin() - m_origin;
    const double u = p_scal(s, h)/a;
    if (u < 0 or u > 1) return false;

    const Vec3 q = p_vect(s, m_u);
    const double v = p_scal(ray.direction(), q) / a;
    if (v < 0 or v > 1) return false;

    rec.m_t = -p_scal(p_vect(s, m_v), m_u) / a;
    rec.m_p = m_origin + u * m_u + v * m_v;
    rec.set_sens_normal(ray, m_normal);
    rec.m_material = m_material;
    return int_valid.contains(rec.m_t);
}

AABB Rectangle::bounding_box() const {
    return m_bbox;
}
