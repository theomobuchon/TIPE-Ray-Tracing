//
// Created by nolan on 31/10/2025.
//

#ifndef TIPE_RAY_TRACING_HITTABLE_HPP
#define TIPE_RAY_TRACING_HITTABLE_HPP

#include "Vec3.hpp"
#include "Ray.hpp"

class Hit_record {
public:
    Point3 m_p;
    Vec3 m_normal;
    double m_t;
    bool m_front_face;

    void set_sens_normal(const Ray &ray, const Vec3& normal_sortant);
};

class Hittable {
public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray &ray, Interval int_valid, Hit_record &rec) const = 0;
};


#endif //TIPE_RAY_TRACING_HITTABLE_HPP