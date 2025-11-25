//
// Created by nolan on 31/10/2025.
//

#include "Sphere.hpp"
#include <utility>
#include <cmath>
#include <memory>

using namespace std;

Sphere::Sphere(const Point3 &center, const double radius, shared_ptr<Material> material) : m_center(center), m_radius(radius), m_material(std::move(material)) {
    const auto r_vec = Vec3(m_radius, m_radius, m_radius);
    m_bbox = AABB(center - r_vec, m_center + r_vec);
}

Sphere &Sphere::operator=(const Sphere &sphere) = default;

bool Sphere::hit(const Ray &ray, const Interval int_valid, Hit_record &rec) const {
    const Vec3 oc = m_center - ray.origin();
    const double a = ray.direction().squaredNorm();
    const double h = p_scal(oc, ray.direction());
    const double c = oc.squaredNorm() - m_radius * m_radius;
    const double discr = h * h - a * c;
    if (discr < 0) {
        return false;
    }

    const double sqrtdiscr = sqrt(discr);
    double racine = (h - sqrtdiscr) / a;
    if (not int_valid.surrounds(racine)) {
        racine = (h + sqrtdiscr) / a;
        if (not int_valid.surrounds(racine)) {
            return false;
        }
    }

    rec.m_t = racine;
    rec.m_p = ray.at(racine);
    rec.set_sens_normal(ray, (rec.m_p - m_center) / m_radius);
    rec.m_material = m_material;

    return true;
}

AABB Sphere::bounding_box() const {
    return m_bbox;
}
