//
// Created by nolan on 14/10/2025.
//

#include "Ray.hpp"
#include "Vec3.hpp"

Ray::Ray(): m_origin(Point3(0, 0, 0)), m_dir(Vec3(0, 0, 1)) {

};

Ray::Ray(const Point3 &origin, const Vec3 &direction): m_origin(origin), m_dir(direction) {

};

Ray &Ray::operator=(const Ray &ray) = default;

Vec3 Ray::at(double t) const {
    return m_origin + t * m_dir;
};

Vec3 Ray::origin() const {
    return m_origin;
}

Vec3 Ray::direction() const {
    return m_dir;
};
