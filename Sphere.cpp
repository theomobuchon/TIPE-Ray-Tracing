//
// Created by nolan on 31/10/2025.
//

#include "Sphere.hpp"

Sphere::Sphere(const Point3 &center, const double radius) : m_center(center), m_radius(radius) {
}

Sphere &Sphere::operator=(const Sphere &sphere) = default;

bool Sphere::hit(const Ray &ray, const Interval int_valid, Hit_record &rec) const {
    const Vec3 oc = m_center - ray.origin();
    const double a = ray.direction().squaredNorm();
    const double h = p_scal(oc, ray.direction());
    const double c = oc.squaredNorm() - m_radius * m_radius;
    double discr = h * h - a * c;
    if (discr < 0) {
        return false;
    }

    double sqrtdiscr = sqrt(discr);
    double racine = (h - sqrtdiscr) / a;
    if (not int_valid.surrounds(racine)) {
        racine = (h + sqrtdiscr) / a;
        if (not int_valid.surrounds(racine)) {
            return false;
        }
    }

    rec.m_t = racine;
    rec.m_p = ray.at(racine);
    rec.m_normal = (rec.m_p - m_center) / m_radius;

    return true;
}

