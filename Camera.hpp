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
    Camera &operator=(const Camera &camera);
    void render(ofstream &fout, const Hittable &world);
    [[nodiscard]] Ray getRay(int x, int y) const;

    Point3 m_center;
    double m_ratio;
    int m_im_width;

protected:
    void initialize();
    [[nodiscard]] static Color ray_color(const Ray &ray, const Hittable &world) ;

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