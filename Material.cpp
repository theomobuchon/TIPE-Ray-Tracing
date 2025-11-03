//
// Created by nolan on 03/11/2025.
//
#include "Material.hpp"

Lambertian::Lambertian(const Color &albedo): m_albedo(albedo) {}

bool Lambertian::scatter(const Ray &r_in, Hit_record &rec, Color &attenuation, Ray &scattered) const {
    Vec3 scatter_direction = rec.m_normal + random_in_unit_sphere();
    if (scatter_direction.near_zero()) {
        scatter_direction = rec.m_normal;
    }
    scattered = Ray(rec.m_p, scatter_direction);
    attenuation = m_albedo;

    return true;
}

Metal::Metal(const Color &albedo, const double fuzz): m_albedo(albedo), m_fuzz(fuzz < 1. ? fuzz : 1.) {}

bool Metal::scatter(const Ray &r_in, Hit_record &rec, Color &attenuation, Ray &scattered) const {
    Vec3 reflected = reflect(r_in.direction(), rec.m_normal);
    reflected = normalisate(reflected) + m_fuzz * random_in_unit_sphere();
    scattered = Ray(rec.m_p, reflected);
    attenuation = m_albedo;
    return p_scal(rec.m_normal, reflected) > 0;
}

