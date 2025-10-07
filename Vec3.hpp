#ifndef DEF_VEC3
#define DEF_VEC3

#include <iostream>

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
    double norme() const;
    void normalize();
    double p_scal(const Vec3 &e) const;
    void p_vect(const Vec3 &e);

    private:
    
    double m_x;
    double m_y;
    double m_z;
};

Vec3 operator+(const Vec3 &e1, const Vec3 &e2);
Vec3 operator-(const Vec3 &e1, const Vec3 &e2);
Vec3 operator*(const Vec3 &e, double lamb);
Vec3 operator*(double lamb, const Vec3 &e);
Vec3 operator/(const Vec3 &e, double lamb);
Vec3 p_vect(const Vec3 &e1, const Vec3 &e2);
double p_scal(const Vec3 &e1, const Vec3 &e2);
Vec3 normalisate(const Vec3 &e);
std::ostream &operator<<(std::ostream &os, const Vec3 &e);

#endif
