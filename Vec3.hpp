//
// Created by nolan on 30/09/2025.
//

#ifndef TIPE_RAY_TRACING_VEC3_HPP
#define TIPE_RAY_TRACING_VEC3_HPP

#include <fstream>
#include <string>
#include "Raytracer.hpp"

class Vec3
{
public:
    Vec3();
    Vec3(double x, double y, double z);
    Vec3 &operator+=(const Vec3 &other);
    Vec3 &operator-=(const Vec3 &other);
    Vec3 &operator*=(double lamb);
    Vec3 &operator/=(double lamb);
    Vec3 &operator=(const Vec3 &other);
    bool operator==(const Vec3 &other) const;
    Vec3 operator-() const;
    double operator[](int i) const;
    void afficher(std::ostream &os) const;
    [[nodiscard]] std::string repr_string() const;
    [[nodiscard]] double squaredNorm() const;
    [[nodiscard]] double norm() const;
    [[nodiscard]] double x() const;
    [[nodiscard]] double y() const;
    [[nodiscard]] double z() const;
    [[nodiscard]] bool near_zero() const;

    static Vec3 random();
    static Vec3 random(double min, double max);

protected:
    void normalize();
    [[nodiscard]] double p_scal(const Vec3 &e) const;
    void p_vect(const Vec3 &e);
    double m_x;
    double m_y;
    double m_z;

    friend Vec3 normalised(const Vec3 &e);
    friend Vec3 p_vect(const Vec3 &e1, const Vec3 &e2);
    friend double p_scal(const Vec3 &e1, const Vec3 &e2);
    friend Vec3 operator*(const Vec3 &e1, const Vec3 &e2);
};

Vec3 operator+(const Vec3 &e1, const Vec3 &e2);
Vec3 operator-(const Vec3 &e1, const Vec3 &e2);
Vec3 operator*(const Vec3 &e, double lamb);
Vec3 operator*(double lamb, const Vec3 &e);
Vec3 operator/(const Vec3 &e, double lamb);
std::ostream &operator<<(std::ostream &os, const Vec3 &e);

using Point3 = Vec3;
using Color = Vec3;


inline Vec3 random_in_unit_sphere() {
    const auto x = random_double_gaussian();
    const auto y = random_double_gaussian();
    const auto z = random_double_gaussian();
    return normalised(Vec3(x, y, z));
}

inline Vec3 random_on_hemisphere(const Vec3 &normal) {
    Vec3 vec_in_unit_sphere = random_in_unit_sphere();
    if (p_scal(normal, vec_in_unit_sphere) > 0) return vec_in_unit_sphere;
    return -vec_in_unit_sphere;
}

inline Vec3 random_in_unit_disk() {
    const auto x = random_double_gaussian();
    const auto y = random_double_gaussian();
    return normalised(Vec3(x, y, 0));
}

inline double linear_to_gamma(const double linear_component) {
    return sqrt(linear_component);
}

inline Vec3 reflect(const Vec3 &v, const Vec3 &n) {
    return v - 2*p_scal(v, n) * n;
}

inline Vec3 refract(const Vec3 &v, const Vec3 &n, const double eta) {
    const auto cos_teta = fmin(p_scal(-v, n), 1.);
    const Vec3 r_out_perp = eta * (v + cos_teta * n);
    const Vec3 r_out_parallel = -sqrt(fabs(1. - r_out_perp.squaredNorm()))*n;
    return r_out_perp + r_out_parallel;
}

#endif
