//
// Created by nolan on 14/10/2025.
//

#ifndef TIPE_RAY_TRACING_CAMERA_HPP
#define TIPE_RAY_TRACING_CAMERA_HPP

#include "Raytracer.hpp"
#include "Hittable.hpp"

class Camera {
public:
    Camera(double ratio, int im_width, double focal_length);
    Camera(double ratio, int im_width, double focal_length, const Point3 &center);
    Camera(double ratio, int im_width, double focal_length, const Point3 &center, int sample_per_pixel);
    Camera &operator=(const Camera &camera);
    void render(ofstream &fout, const Hittable &world);

    Point3 m_center;
    double m_ratio;
    int m_im_width;
    bool antialiasing;
    int m_sample_per_pixel;

protected:
    void initialize();
    [[nodiscard]] static Color ray_color(const Ray &ray, const Hittable &world);
    [[nodiscard]] Ray getRay(int x, int y) const;
    [[nodiscard]] static Vec3 sample_square() ;

    int m_im_height{};
    double m_viewport_width{};
    double m_viewport_height{};
    double m_focal_length;
    Point3 m_origin_viewport;
    Point3 m_pix00;
    Vec3 m_u_viewport;
    Vec3 m_v_viewport;
    Vec3 m_du_viewport;
    Vec3 m_dv_viewport;

};

#endif //TIPE_RAY_TRACING_CAMERA_HPP