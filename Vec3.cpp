#include "Vec3.hpp"
#include "Random.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Vec3::Vec3(): m_x(0.0), m_y(0.0), m_z(0.0) {

};

Vec3::Vec3(const float x, const float y, const float z): m_x(x), m_y(y), m_z(z) {

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

Vec3 &Vec3::operator*=(float lamb) {
    m_x *= lamb;
    m_y *= lamb;
    m_z *= lamb;

    return *this;
}

Vec3 &Vec3::operator/=(float lamb) {
    if (lamb == 0) {
        cout << "Erreur : division d'un Vec3 par 0" << endl;
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

float Vec3::operator[](int i) const {
    if (i == 0) {return m_x;}
    if (i == 1) {return m_y;}
    return m_z;
}

float Vec3::squaredNorm() const {
    return m_x * m_x + m_y * m_y + m_z * m_z;
}

float Vec3::norm() const {
    return sqrt(squaredNorm());
}

float Vec3::p_scal(const Vec3 &e) const {
    return m_x*e.m_x + m_y*e.m_y + m_z*e.m_z;
}

void Vec3::p_vect(const Vec3 &e) {
    const float x = m_y*e.m_z - e.m_y*m_z;
    const float y = e.m_x*m_z - m_x*e.m_z;
    const float z = m_x*e.m_y - e.m_x*m_y;
    m_x = x;
    m_y = y;
    m_z = z;
}

void Vec3::afficher(ostream &os) const {
    os << "(" << m_x << ", " << m_y << ", " << m_z << ")";
}

string Vec3::repr_string() const {
    string s_x = to_string(m_x);
    string s_y = to_string(m_y);
    string s_z = to_string(m_z);
    s_x.erase(s_x.find_last_not_of('0') + 1, string::npos);
    s_y.erase(s_y.find_last_not_of('0') + 1, string::npos);
    s_z.erase(s_z.find_last_not_of('0') + 1, string::npos);
    return "(" + s_x + "," + s_y + "," + s_z + ")";
}

void Vec3::normalize() {
    const float n = this -> norm();
    *this /= n;
}

float Vec3::x() const {
    return m_x;
}

float Vec3::y() const {
    return m_y;
}

float Vec3::z() const {
    return m_z;
}

bool Vec3::near_zero() const {
    constexpr auto s = 1e-8;
    return fabs(m_x) < s && fabs(m_y) < s && fabs(m_z) < s;
}


Vec3 Vec3::random(RNG &rng) {
    return {rng.next_uniform(), rng.next_uniform(), rng.next_uniform()};
}

Vec3 Vec3::random(const float min, const float max, RNG &rng) {
    return {rng.next_uniform(min, max), rng.next_uniform(min, max), rng.next_uniform(min, max)};
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

Vec3 operator*(const Vec3 &e, const float lamb) {
    Vec3 e2(e);
    e2 *= lamb;
    return e2;
}

Vec3 operator*(const float lamb, const Vec3 &e) {
    return e*lamb;
}

Vec3 operator*(const Vec3 &e1, const Vec3 &e2) {
    return {e1.m_x * e2.m_x, e1.m_y * e2.m_y, e1.m_z * e2.m_z};
}

Vec3 operator/(const Vec3 &e, const float lamb) {
    Vec3 f(e);
    f /= lamb;
    return f;
}

float p_scal(const Vec3 &e1, const Vec3 &e2) {
    return e1.p_scal(e2);
}

Vec3 p_vect(const Vec3 &e1, const Vec3 &e2) {
    Vec3 e3(e1);
    e3.p_vect(e2);
    return e3;
}

Vec3 normalised(const Vec3 &e) {
    Vec3 e2(e);
    e2.normalize();
    return e2;
}

ostream &operator<<(ostream &os, const Vec3 &e) {
    e.afficher(os);
    return os;
}
