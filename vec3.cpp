#include "vec3.hpp"
#include <iostream>
#include <math.h>

using namespace std;

Vec3::Vec3(): m_x(0.0), m_y(0.0), m_z(0.0);

Vec3::Vec3(double x, double y, double z): m_x(x), m_y(y), m_z(z);

void Vec3::operator+=(Vec3 other) {
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
}

void Vec3::operator-=(Vec3 other) {
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
}

void Vec3::operator*=(double other) {
    m_x *= other;
    m_y *= other;
    m_z *= other;
}

void Vec3::operator/=(double other) {
    if other == 0 {
        cout << "Erreur : division d'un vec3 par 0" << endl;
    }
    m_x /= other;
    m_y /= other;
    m_z /= other;
}

double Vec3::norme() {
    return sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

double Vec3::p_scal(Vec3 e) {
    return m_x*e.m_x + m_y*e.m_y + m_z*e.m_z;
}

void Vec3::p_vect(Vec3 e) {
    x = m_y*e.m_z - e.m_y*m_z;
    y = e.m_x*m_z - m_x*e.m_z;
    z = m_x*e.m_y - e.m_x*m_y;
    m_x = x;
    m_y = y;
    m_z = z;
}

void Vec3::normalize() {
    double n = *this.norme();
    *this /= n;
}

Vec3 operator+(Vec3 e1, Vec3 e2) {
    Vec3 e3(e1);
    e3 += e2;
    return e3;
}

Vec3 operator-(Vec3 e1, Vec3 e2) {
    Vec3 e3(e1);
    e3 -= e2;
    return e3;
}

Vec3 operator*(Vec3 e, double lamb) {
    Vec3 e2(e);
    e2 *= lamb;
    return e2;
}

Vec3 operator*(double lamb, Vec3 e) {
    return e*lamb;
}

Vec3 operator/(Vec3 e, double lamb) {
    Vec3 f(e);
    f /= lamb;
    return f;
}

double p_scal(Vec3 e1, Vec3 e2) {
    return e1.p_scal(e2);
}

Vec3 p_vect(Vec3 e1, Vec3 e2) {
    Vec3 e3(e1);
    e3.p_vect(e2);
    return e3;
}

Vec3 normalisate(Vec3 e) {
    Vec3 e2(e);
    e2.normalize()
    return e2
}

