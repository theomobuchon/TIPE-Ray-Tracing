//
// Created by nolan on 14/10/2025.
//

#include "Camera.hpp"

#include <future>
#include "Raytracer.hpp"
#include "Interval.hpp"
#include "Material.hpp"
#include "Image.hpp"
#include <iostream>
#include <mutex>
#include <thread>
#include <memory>

using namespace std;

mutex mtx;

Camera::Camera(const double ratio, const int im_width, const Point3 &center, const Vec3 &look_direction): center(center), look_direction(look_direction), ratio(ratio), im_width(im_width) {}

void Camera::initialize() {
    m_w = -normalised(look_direction);
    m_u = normalised(p_vect(up, m_w));
    m_v = p_vect(m_w, m_u);

    m_im_height = static_cast<int>(im_width / ratio);
    const auto theta = degrees_to_radians(v_fov);
    const auto h = tan(theta / 2);
    const auto viewport_height = 2 * h * focus_dist;
    const auto viewport_width = viewport_height / (m_im_height/static_cast<double>(im_width));

    const auto u_viewport = viewport_width * m_u;
    const auto v_viewport = viewport_height * -m_v;
    const auto origin_viewport = center - u_viewport/2 - v_viewport/2 - focus_dist*m_w;

    m_du_viewport = u_viewport / im_width;
    m_dv_viewport = v_viewport / m_im_height;
    m_pix00 = origin_viewport + 0.5*m_du_viewport + 0.5*m_dv_viewport;

    const auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
    m_u_defocus_disk = defocus_radius * m_u;
    m_v_defocus_disk = defocus_radius * m_v;

    show_progression(true);
}

Color Camera::ray_color(const Ray &ray, const int depth, const Hittable &world) const {
    if (depth <= 0) { return {0, 0, 0};}

    Hit_record rec;
    if (!world.hit(ray, Interval(0.001, infinite), rec)) {
        return background(ray.direction());
    }

    Ray scattered_ray;
    Color attenuation;
    Color emitted = rec.m_material->emitted();

    if (!rec.m_material->scatter(ray, rec, attenuation, scattered_ray)) {
        return emitted;
    }

    return emitted + attenuation * ray_color(scattered_ray, depth - 1, world);
}

Camera &Camera::operator=(const Camera &camera) = default;

Ray Camera::getRay(const int x, const int y) const {
    const auto offset = sample_square();
    const auto pixel_targeted = m_pix00 + (x + offset.x()) * m_du_viewport + (y + offset.y()) * m_dv_viewport;
    const auto ray_origin = (defocus_angle <= 0) ? center : random_in_defocus_disk();
    return {ray_origin,  pixel_targeted - ray_origin};
}

void Camera::partial_render(Image &image, const Hittable &world, const int start_i, const int end_i, const int start_j, const int end_j) const {
    for (int j = start_j; j < end_j; j++) {
        for (int i = start_i; i < end_i; i++) {
            auto color = Color(0, 0, 0);
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                Ray ray = getRay(i, j);
                color += ray_color(ray, max_depth, world);
            }
            {
                lock_guard<mutex> lock(mtx);
                image.write_color(i, j, color / samples_per_pixel);
                show_progression();
            }

        }
    }
}


void Camera::show_progression(const bool reset) const {
    static int count = 0;
    if (reset) count = 0;
    else if (++count % 1000 == 0) clog << "Processed pixels : " << count << " / " << im_width * m_im_height << endl;
}

Image Camera::render(const Hittable &world) {
    initialize();
    Image image(im_width, m_im_height);

    if (!parallelism) {
        partial_render(image, world, 0, im_width, 0, m_im_height);
    }
    else {
        vector<thread> threads;
        const int nb_thread = static_cast<int>(thread::hardware_concurrency());
        const int part_i = im_width / nb_thread;
        for (int k = 0; k < nb_thread; k++) {
            threads.emplace_back(&Camera::partial_render, this, ref(image), ref(world), k*part_i, (k+1)*part_i, 0, m_im_height);
        }
        partial_render(image, world, nb_thread*part_i, im_width, 0, m_im_height);

        for (int k = 0; k < nb_thread; k++) {
            threads[k].join();
        }
    }

    return image;
}

Vec3 Camera::sample_square() {
    return {random_double() - 0.5, random_double() - 0.5, 0};
}

Vec3 Camera::random_in_defocus_disk() const {
    const auto p = random_in_unit_disk();
    return center + p.x() * m_u_defocus_disk + p.y() * m_v_defocus_disk;
}
