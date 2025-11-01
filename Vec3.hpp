//
// Created by nolan on 30/09/2025.
//

#ifndef TIPE_RAY_TRACING_VEC3_H
#define TIPE_RAY_TRACING_VEC3_H

#include <fstream>

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
    void afficher(std::ostream &os) const;
    [[nodiscard]] double squaredNorm() const;
    [[nodiscard]] double norm() const;
    [[nodiscard]] double x() const;
    [[nodiscard]] double y() const;
    [[nodiscard]] double z() const;

protected:
    void normalize();
    [[nodiscard]] double p_scal(const Vec3 &e) const;
    void p_vect(const Vec3 &e);
    double m_x;
    double m_y;
    double m_z;

    friend Vec3 normalisate(const Vec3 &e);
    friend Vec3 p_vect(const Vec3 &e1, const Vec3 &e2);
    friend double p_scal(const Vec3 &e1, const Vec3 &e2);
};

Vec3 operator+(const Vec3 &e1, const Vec3 &e2);
Vec3 operator-(const Vec3 &e1, const Vec3 &e2);
Vec3 operator*(const Vec3 &e, double lamb);
Vec3 operator*(double lamb, const Vec3 &e);
Vec3 operator/(const Vec3 &e, double lamb);
std::ostream &operator<<(std::ostream &os, const Vec3 &e);

using Point3 = Vec3;
using Color = Vec3;

void write_color(std::ofstream &fout, const Color &color);

#endif
