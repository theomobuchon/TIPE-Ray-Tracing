//
// Created by nolan on 16/12/2025.
//

#include "Rectangle.hpp"
#include <algorithm>

Rectangle::Rectangle(const Point3 &origin, const Vec3 &u, const Vec3 &v, const std::shared_ptr<Material> &material): m_origin(origin), m_u(u), m_v(v), m_material(material) {
    m_normal = normalised(p_vect(u, v));
    const Point3 p0 = m_origin;
    const Point3 p1 = m_origin + m_u;
    const Point3 p2 = m_origin + m_v;
    const Point3 p3 = m_origin + m_u + m_v;

    Vec3 min_v(
        std::min({p0.x(), p1.x(), p2.x(), p3.x()}),
        std::min({p0.y(), p1.y(), p2.y(), p3.y()}),
        std::min({p0.z(), p1.z(), p2.z(), p3.z()})
    );

    Vec3 max_v(
        std::max({p0.x(), p1.x(), p2.x(), p3.x()}),
        std::max({p0.y(), p1.y(), p2.y(), p3.y()}),
        std::max({p0.z(), p1.z(), p2.z(), p3.z()})
    );

    constexpr float eps = 1e-4f;

    min_v -= Vec3(eps, eps, eps);
    max_v += Vec3(eps, eps, eps);

    m_bbox = AABB(min_v, max_v);
}

bool Rectangle::hit(const Ray &ray, const Interval int_valid, Hit_record &rec) const {
    const Vec3 h = p_vect(ray.direction(), m_v);
    const float a = p_scal(m_u, h);
    if (a == 0) return false;

    const Vec3 s = ray.origin() - m_origin;
    const float u = p_scal(s, h)/a;
    if (u < 0 or u > 1) return false;

    const Vec3 q = p_vect(s, m_u);
    const float v = p_scal(ray.direction(), q) / a;
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
