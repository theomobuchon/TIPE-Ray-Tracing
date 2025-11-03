//
// Created by nolan on 02/11/2025.
//

#ifndef TIPE_RAY_TRACING_MATERIAL_HPP
#define TIPE_RAY_TRACING_MATERIAL_HPP

#include "Hittable.hpp"

class Material {
public:
    virtual ~Material() = default;
    virtual bool scatter(const Ray &r_in, Hit_record &rec, Color &attenuation, Ray &scattered) const = 0;

private:
    Color m_color;
};

class Lambertian final : public Material {
public:
    explicit Lambertian(const Color &albedo);

    bool scatter(const Ray &r_in, Hit_record &rec, Color &attenuation, Ray &scattered) const override;

protected:
    Color m_albedo;
};

class Metal final : public Material {
public:
    Metal(const Color &albedo, double fuzz);

    bool scatter(const Ray &r_in, Hit_record &rec, Color &attenuation, Ray &scattered) const override;

protected:
    Color m_albedo;
    double m_fuzz;
};

#endif //TIPE_RAY_TRACING_MATERIAL_HPP