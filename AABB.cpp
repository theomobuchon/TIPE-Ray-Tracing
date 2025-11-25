//
// Created by nolan on 22/11/2025.
//

#include "AABB.hpp"

using namespace std;

AABB::AABB(const Interval &x, const Interval &y, const Interval &z): m_x(x), m_y(y), m_z(z) {}

AABB::AABB(const Point3 &a, const Point3 &b) {
    m_x = a.x() <= b.x() ? Interval(a.x(), b.x()) : Interval(b.x(), a.x());
    m_y = a.y() <= b.y() ? Interval(a.y(), b.y()) : Interval(b.y(), a.y());
    m_z = a.z() <= b.z() ? Interval(a.z(), b.z()) : Interval(b.z(), a.z());
}

AABB::AABB(const AABB &b1, const AABB &b2) {
    m_x = Interval(b1.m_x, b2.m_x);
    m_y = Interval(b1.m_y, b2.m_y);
    m_z = Interval(b1.m_z, b2.m_z);
}

const Interval & AABB::axis_interval(const int n) const {
    if (n == 0) {return m_x;}
    if (n == 1) {return m_y;}
    return m_z;
}

bool AABB::hit(const Ray &r, Interval ray_t) const {
    const Point3 &orig = r.origin();
    const Vec3 &dir = r.direction();

    for (int i = 0; i < 3; i++) {
        const Interval &axis = axis_interval(i);
        const double adinv = 1./dir[i];

        auto t0 = (axis.min() - orig[i]) * adinv;
        auto t1 = (axis.max() - orig[i]) * adinv;

        if (t0 > t1) {
            if (t0 > ray_t.min()) {ray_t.setMin(t0);}
            if (t1 < ray_t.max()) {ray_t.setMax(t1);}
        }
        else {
            if (t1 > ray_t.min()) {ray_t.setMin(t1);}
            if (t0 > ray_t.max()) {ray_t.setMax(t0);}
        }

        if (ray_t.max() <= ray_t.min()) {return false;}
    }

    return true;
}
