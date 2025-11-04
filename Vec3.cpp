#include "Vec3.hpp"
#include <iostream>
#include <cmath>
#include "Interval.hpp"
#include "Raytracer.hpp"

using namespace std;

Vec3::Vec3(): m_x(0.0), m_y(0.0), m_z(0.0) {

};

Vec3::Vec3(const double x, const double y, const double z): m_x(x), m_y(y), m_z(z) {

};

Vec3 &Vec3::operator+=(const Vec3 &other) {
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;

    return *this;
}

Vec3 &Vec3::operator-=(const Vec3 &other) {
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;

    return *this;
}

Vec3 &Vec3::operator*=(double lamb) {
    m_x *= lamb;
    m_y *= lamb;
    m_z *= lamb;

    return *this;
}

Vec3 &Vec3::operator/=(double lamb) {
    if (lamb == 0) {
        cout << "Erreur : division d'un vec3 par 0" << endl;
    }
    m_x /= lamb;
    m_y /= lamb;
    m_z /= lamb;

    return *this;
}

Vec3 &Vec3::operator=(const Vec3 &other) = default;

bool Vec3::operator==(const Vec3 &other) const {
    return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
}

Vec3 Vec3::operator-() const {
    return -1*(*this);
}

double Vec3::squaredNorm() const {
    return m_x * m_x + m_y * m_y + m_z * m_z;
}

double Vec3::norm() const {
    return sqrt(squaredNorm());
}

double Vec3::p_scal(const Vec3 &e) const {
    return m_x*e.m_x + m_y*e.m_y + m_z*e.m_z;
}

void Vec3::p_vect(const Vec3 &e) {
    const double x = m_y*e.m_z - e.m_y*m_z;
    const double y = e.m_x*m_z - m_x*e.m_z;
    const double z = m_x*e.m_y - e.m_x*m_y;
    m_x = x;
    m_y = y;
    m_z = z;
}

void Vec3::afficher(ostream &os) const {
    os << "(" << m_x << ", " << m_y << ", " << m_z << ")";
}

void Vec3::normalize() {
    const double n = this -> norm();
    *this /= n;
}

double Vec3::x() const {
    return m_x;
}

double Vec3::y() const {
    return m_y;
}

double Vec3::z() const {
    return m_z;
}

bool Vec3::near_zero() const {
    constexpr auto s = 1e-8;
    return fabs(m_x) < s && fabs(m_y) < s && fabs(m_z) < s;
}


Vec3 Vec3::random() {
    return {random_double(), random_double(), random_double()};
}

Vec3 Vec3::random(double min, double max) {
    return {random_double(min, max), random_double(min, max), random_double(min, max)};
}

Vec3 operator+(const Vec3 &e1, const Vec3 &e2) {
    Vec3 e3(e1);
    e3 += e2;
    return e3;
}

Vec3 operator-(const Vec3 &e1, const Vec3 &e2) {
    Vec3 e3(e1);
    e3 -= e2;
    return e3;
}

Vec3 operator*(const Vec3 &e, const double lamb) {
    Vec3 e2(e);
    e2 *= lamb;
    return e2;
}

Vec3 operator*(const double lamb, const Vec3 &e) {
    return e*lamb;
}

Vec3 operator*(const Vec3 &e1, const Vec3 &e2) {
    return {e1.m_x * e2.m_x, e1.m_y * e2.m_y, e1.m_z * e2.m_z};
}

Vec3 operator/(const Vec3 &e, const double lamb) {
    Vec3 f(e);
    f /= lamb;
    return f;
}

double p_scal(const Vec3 &e1, const Vec3 &e2) {
    return e1.p_scal(e2);
}

Vec3 p_vect(const Vec3 &e1, const Vec3 &e2) {
    Vec3 e3(e1);
    e3.p_vect(e2);
    return e3;
}

Vec3 normalisate(const Vec3 &e) {
    Vec3 e2(e);
    e2.normalize();
    return e2;
}

ostream &operator<<(ostream &os, const Vec3 &e) {
    e.afficher(os);
    return os;
}

void write_color(std::ofstream &fout, const Color &color) {
    static const Interval intensity(0., 0.999);
    const double x = linear_to_gamma(color.x());
    const double y = linear_to_gamma(color.y());
    const double z = linear_to_gamma(color.z());
    const int rbyte = static_cast<int>(256 * intensity.clamp(x));
    const int gbyte = static_cast<int>(256 * intensity.clamp(y));
    const int bbyte = static_cast<int>(256 * intensity.clamp(z));
    fout << rbyte << " " << gbyte << " " << bbyte << std::endl;
}

inline Vec3 random_in_unit_sphere() {
    auto x = random_double(-1, 1);
    const auto y_max = sqrt(1 - x*x);
    auto y = random_double(-y_max, +y_max);
    auto z = sqrt(Interval(0, 1).clamp(1 - x*x - y*y));
    return {x, y, z};
}

inline Vec3 random_on_hemisphere(const Vec3 &normal) {
    Vec3 vec_in_unit_sphere = random_in_unit_sphere();
    if (p_scal(normal, vec_in_unit_sphere) > 0) return vec_in_unit_sphere;
    return -vec_in_unit_sphere;
}

inline double linear_to_gamma(double linear_component) {
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
