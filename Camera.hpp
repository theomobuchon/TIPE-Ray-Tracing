//
// Created by nolan on 14/10/2025.
//

#ifndef TIPE_RAY_TRACING_CAMERA_HPP
#define TIPE_RAY_TRACING_CAMERA_HPP

#include "Hittable.hpp"

class Camera {
public:
    Camera(double ratio, int im_width, const Point3 &center, const Vec3 &look_direction);
    Camera &operator=(const Camera &camera);
    void render(std::ofstream &fout, const Hittable &world);

    Point3 center; // Center of the camera
    Vec3 look_direction; // The direction in which the calera is oriented
    Vec3 up = Vec3(0, 1, 0); // The vertical for the camera
    double v_fov = 90; // field of view (in degrees)

    double ratio; // The ration of the image rendered
    int im_width; // The width of the image rendered
    int samples_per_pixel = 100; // The number of rays for each pixel
    int max_depth = 50; // The maximal number of collisions for each rays

    double defocus_angle = 0; // Variation angle of rays through each pixel of the image
    double focus_dist = 10; // The distance from camera where the focus is perfect

    bool parallelism = false; // To switch on/off the parallelism

protected:
    void initialize();
    [[nodiscard]] static Color ray_color(const Ray &ray, int depth, const Hittable &world);
    [[nodiscard]] Ray getRay(int x, int y) const;
    [[nodiscard]] static Vec3 sample_square();
    [[nodiscard]] Vec3 random_in_defocus_disk() const;
    [[nodiscard]] Color partial_color(const Hittable &world, int i, int j, int nb_iterations) const;

    double m_im_height{};
    Vec3 m_u, m_v, m_w;
    Point3 m_pix00;
    Vec3 m_du_viewport;
    Vec3 m_dv_viewport;
    Vec3 m_u_defocus_disk;
    Vec3 m_v_defocus_disk;

};

#endif //TIPE_RAY_TRACING_CAMERA_HPP