//
// Created by nolan on 31/10/2025.
//

#include "Hittable.hpp"

void Hit_record::set_sens_normal(const Ray &ray, const Vec3 &normal_sortant) {
    m_front_face = p_scal(ray.direction(), normal_sortant) < 0.;
    m_normal = m_front_face ? normal_sortant : -1*normal_sortant;
}

