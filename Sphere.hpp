//
// Created by nolan on 31/10/2025.
//

#ifndef TIPE_RAY_TRACING_SPHERE_HPP
#define TIPE_RAY_TRACING_SPHERE_HPP
#include "Raytracer.hpp"
#include "Hittable.hpp"


class Sphere: public Hittable {
public:
    Sphere(const Point3 &center, double radius);
    Sphere &operator=(const Sphere &sphere);
    bool hit(const Ray &ray, Interval int_valid, Hit_record &rec) const override;

protected:
    Point3 m_center;
    double m_radius;
};


#endif //TIPE_RAY_TRACING_SPHERE_HPP