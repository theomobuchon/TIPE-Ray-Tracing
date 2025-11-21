//
// Created by nolan on 03/11/2025.
//
#include "Material.hpp"
#include <cmath>

using namespace std;

bool Material::scatter(const Ray &r_in, Hit_record &rec, Color &attenuation, Ray &scattered) const {
    return false;
}

Color Material::emitted() const {
    return {0, 0, 0};
}

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
    reflected = normalised(reflected) + m_fuzz * random_in_unit_sphere();
    scattered = Ray(rec.m_p, reflected);
    attenuation = m_albedo;
    return p_scal(rec.m_normal, reflected) > 0;
}

Dielectric::Dielectric(const double refractive_index): m_refractive_index(refractive_index) {}

bool Dielectric::scatter(const Ray &r_in, Hit_record &rec, Color &attenuation, Ray &scattered) const {
    attenuation = Color(1.0, 1.0, 1.0);
    const double effective_refractive_index = rec.m_front_face ? 1./m_refractive_index : m_refractive_index;

    const Vec3 unit_direction = normalised(r_in.direction());
    const double cos_teta = fmin(p_scal(unit_direction, rec.m_normal), 1.);
    const double sin_teta = sqrt(1. - cos_teta * cos_teta);
    const bool cannot_refract = effective_refractive_index * sin_teta > 1.;

    Vec3 direction;
    if (cannot_refract) direction = reflect(unit_direction, rec.m_normal);
    else direction = refract(unit_direction, rec.m_normal, effective_refractive_index);

    scattered = Ray(rec.m_p, direction);
    return true;
}

Diffuse_light::Diffuse_light(const Color &ambient): m_color(ambient) {}

Color Diffuse_light::emitted() const {
    return m_color;
}
