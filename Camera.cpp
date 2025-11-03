//
// Created by nolan on 14/10/2025.
//

#include "Camera.hpp"
#include "Interval.cpp"
#include "Material.hpp"

using namespace std;

Camera::Camera(const double ratio, const int im_width, const double focal_length): m_center(Point3(0, 0, 0)), m_ratio(ratio), m_im_width(im_width), m_sample_per_pixel(10), m_max_depth(10), m_focal_length(focal_length) {
    initialize();
}

Camera::Camera(const double ratio, const int im_width, const double focal_length, const Point3 &center): m_center(center), m_ratio(ratio), m_im_width(im_width), m_sample_per_pixel(10), m_max_depth(10), m_focal_length(focal_length) {
    initialize();
}

Camera::Camera(const double ratio, const int im_width, const double focal_length, const Point3 &center, const int sample_per_pixel): m_center(center), m_ratio(ratio), m_im_width(im_width), m_sample_per_pixel(sample_per_pixel), m_max_depth(10), m_focal_length(focal_length) {
    initialize();
}

void Camera::initialize() {
    m_im_height = static_cast<int>(m_im_width / m_ratio);
    m_viewport_height = 2.0;
    m_viewport_width = m_viewport_height / (static_cast<double>(m_im_height)/static_cast<double>(m_im_width));
    m_u_viewport = Vec3(m_viewport_width, 0, 0);
    m_v_viewport = Vec3(0, -m_viewport_height, 0);
    m_origin_viewport = m_center - m_u_viewport/2 - m_v_viewport/2 + Vec3(0, 0, -m_focal_length);
    m_du_viewport = m_u_viewport / m_im_width;
    m_dv_viewport = m_v_viewport / m_im_height;
    m_pix00 = m_origin_viewport + 0.5*m_du_viewport + 0.5*m_dv_viewport;
}

Color Camera::ray_color(const Ray &ray, const int depth, const Hittable &world) {
    if (depth <= 0) return {0, 0, 0};

    if (Hit_record rec; world.hit(ray, Interval(0.001, infinite), rec)) {
        Ray scattered_ray;
        if (Color attenuation; rec.m_material->scatter(ray, rec, attenuation, scattered_ray)) {
            return attenuation * ray_color(scattered_ray, depth - 1, world);
        }
        return {0, 0, 0};
    }

    const Vec3 unit_direction = normalisate(ray.direction());
    const double a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}

Camera &Camera::operator=(const Camera &camera) = default;

Ray Camera::getRay(const int x, const int y) const {
    const auto offset = sample_square();
    const auto pixel_targeted = m_pix00 + (x + offset.x()) * m_du_viewport + (y + offset.y()) * m_dv_viewport;
    return {m_center,  pixel_targeted - m_center};
}

void Camera::render(ofstream &fout, const Hittable &world) {
    initialize();
    fout << "P3\n" << m_im_width << " " << m_im_height << "\n255\n";

    for (int j = 0; j < m_im_height; j++) {
        for (int i = 0; i < m_im_width; i++) {
            Color pixel_color;
            for (int sample = 0; sample < m_sample_per_pixel; sample++) {
                Ray ray = getRay(i, j);
                pixel_color += ray_color(ray, m_max_depth, world);
            }
            write_color(fout, pixel_color / m_sample_per_pixel);
        }
    }
}

Vec3 Camera::sample_square() {
    return {random_double() - 0.5, random_double() - 0.5, 0};
}
