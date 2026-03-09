//
// Created by nolan on 02/11/2025.
//

#ifndef TIPE_RAY_TRACING_MATERIAL_HPP
#define TIPE_RAY_TRACING_MATERIAL_HPP

#include "Hittable.hpp"

class Material {
public:
    virtual ~Material() = default;
    virtual bool scatter(const Ray &r_in, Hit_record &rec, Color &attenuation, Ray &scattered, RNG &rng) const;
    [[nodiscard]] virtual Color emitted() const;
};

class Lambertian final : public Material {
public:
    explicit Lambertian(const Color &albedo);

    bool scatter(const Ray &r_in, Hit_record &rec, Color &attenuation, Ray &scattered, RNG &rng) const override;

protected:
    Color m_albedo;
};

class Metal final : public Material {
public:
    Metal(const Color &albedo, float fuzz);

    bool scatter(const Ray &r_in, Hit_record &rec, Color &attenuation, Ray &scattered, RNG &rng) const override;

protected:
    Color m_albedo;
    float m_fuzz;
};

class Dielectric final : public Material {
public:
    explicit Dielectric(float refractive_index);

    bool scatter(const Ray &r_in, Hit_record &rec, Color &attenuation, Ray &scattered, RNG &rng) const override;

protected:
    float m_refractive_index;
};

class Diffuse_light final : public Material {
public:
    explicit Diffuse_light(const Color &ambient);

    [[nodiscard]] Color emitted() const override;

protected:
    Color m_color;
};

#endif //TIPE_RAY_TRACING_MATERIAL_HPP