//
// Created by nolan on 30/09/2025.
//

#ifndef TIPE_RAY_TRACING_VEC3_HPP
#define TIPE_RAY_TRACING_VEC3_HPP

#include <fstream>
#include <string>
#include "Random.hpp"

class Vec3
{
public:
    Vec3();
    Vec3(float x, float y, float z);
    Vec3 &operator+=(const Vec3 &other);
    Vec3 &operator-=(const Vec3 &other);
    Vec3 &operator*=(float lamb);
    Vec3 &operator/=(float lamb);
    Vec3 &operator=(const Vec3 &other);
    bool operator==(const Vec3 &other) const;
    Vec3 operator-() const;
    float operator[](int i) const;
    void afficher(std::ostream &os) const;
    [[nodiscard]] std::string repr_string() const;
    [[nodiscard]] float squaredNorm() const;
    [[nodiscard]] float norm() const;
    [[nodiscard]] float x() const;
    [[nodiscard]] float y() const;
    [[nodiscard]] float z() const;
    [[nodiscard]] bool near_zero() const;

    static Vec3 random(RNG &rng);
    static Vec3 random(float min, float max, RNG &rng);

protected:
    void normalize();
    [[nodiscard]] float p_scal(const Vec3 &e) const;
    void p_vect(const Vec3 &e);
    float m_x;
    float m_y;
    float m_z;

    friend Vec3 normalised(const Vec3 &e);
    friend Vec3 p_vect(const Vec3 &e1, const Vec3 &e2);
    friend float p_scal(const Vec3 &e1, const Vec3 &e2);
    friend Vec3 operator*(const Vec3 &e1, const Vec3 &e2);
};

Vec3 operator+(const Vec3 &e1, const Vec3 &e2);
Vec3 operator-(const Vec3 &e1, const Vec3 &e2);
Vec3 operator*(const Vec3 &e, float lamb);
Vec3 operator*(float lamb, const Vec3 &e);
Vec3 operator/(const Vec3 &e, float lamb);
std::ostream &operator<<(std::ostream &os, const Vec3 &e);

using Point3 = Vec3;
using Color = Vec3;


inline Vec3 random_in_unit_sphere(RNG rng) {
    const auto x = rng.next_gaussian();
    const auto y = rng.next_gaussian();
    const auto z = rng.next_gaussian();
    return normalised(Vec3(x, y, z));
}

inline Vec3 random_on_hemisphere(const Vec3 &normal, RNG rng) {
    Vec3 vec_in_unit_sphere = random_in_unit_sphere(rng);
    if (p_scal(normal, vec_in_unit_sphere) > 0) return vec_in_unit_sphere;
    return -vec_in_unit_sphere;
}

inline Vec3 random_in_unit_disk(RNG &rng) {
    const auto x = rng.next_gaussian();
    const auto y = rng.next_gaussian();
    return normalised(Vec3(x, y, 0));
}

inline float linear_to_gamma(const float linear_component) {
    return sqrtf(linear_component);
}

inline Vec3 reflect(const Vec3 &v, const Vec3 &n) {
    return v - 2*p_scal(v, n) * n;
}

inline Vec3 refract(const Vec3 &v, const Vec3 &n, const float eta) {
    const auto cos_teta = fminf(p_scal(-v, n), 1.);
    const Vec3 r_out_perp = eta * (v + cos_teta * n);
    const Vec3 r_out_parallel = -sqrtf(fabsf(1.f - r_out_perp.squaredNorm()))*n;
    return r_out_perp + r_out_parallel;
}

#endif
