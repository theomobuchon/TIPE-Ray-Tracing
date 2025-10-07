#ifndef DEF_VEC3
#define DEF_VEC3

class Vec3
{
    public:

    Vec3()
    Vec3(double x, double y, double z);
    void operator+=(Vec3 other);
    void operator-=(Vec3 other);
    void operator*=(double lamb);
    void operator/=(double lamb);
    double norme();
    void normalize();
    double p_scal(Vec3 e);
    void p_vect(Vec3 e);

    private:
    
    double m_x;
    double m_y;
    double m_z;
};

Vec3 operator+(Vec3 e1, Vec3 e2);
Vec3 operator-(Vec3 e1, Vec3 e2);
Vec3 operator*(Vec3 e, double lamb);
Vec3 operator*(double lamb, Vec3 e);
Vec3 operator/(Vec3 e, double lamb);
Vec3 p_vect(Vec3 e1, Vec3 e2);
double p_scal(Vec3 e1, Vec3 e2);
Vec3 normalisate(Vec3 e);

#endif
