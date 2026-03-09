//
// Created by nolan on 06/01/2026.
//

#ifndef TIPE_RAY_TRACING_SCENES_HPP
#define TIPE_RAY_TRACING_SCENES_HPP
#include <string>
#include "Camera.hpp"

std::string clean_string(float d);
std::string name_file(const Camera& cam, const std::string &im_title);
Color degradated_background(const Vec3 &ray_direction);
Color white_background(const Vec3 &ray_direction);
int lambertianExample();
int metalExample();
int dielectricExample();
int sphere_field_demo();
int testLight();
int empty_cornel_box();
int test_mesh();

#endif //TIPE_RAY_TRACING_SCENES_HPP