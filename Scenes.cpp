//
// Created by nolan on 18/11/2025.
//

#include "Raytracer.hpp"
#include "Vec3.cpp"
#include "Ray.cpp"
#include "Camera.cpp"
#include "Sphere.cpp"
#include "Material.cpp"
#include "Hittable_list.cpp"
#include <memory>
#include <string>

string clean_string(const double d) {
    string s = to_string(d);
    s.erase(s.find_last_not_of('0') + 1, string::npos);
    return s;
}

Color degradated_background(const Vec3 &ray_direction) {
    const Vec3 unit_direction = normalised(ray_direction);
    const double a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}

int lambertianExample() {
    auto world = Hittable_list();

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    auto material = make_shared<Lambertian>(Color(0.5, 0., 0.5));
    world.add(make_shared<Sphere>(Point3(0, 0.5, 0.5), 0.5, material));

    double im_ratio = 1.;
    int im_width = 512;
    int im_height = im_width / static_cast<int>(im_ratio);
    Point3 cam_center = {0., 0.5, -2.};
    Vec3 cam_dir = Point3(0., 0., 1.);
    Camera cam(im_ratio, im_width, cam_center, cam_dir);

    cam.samples_per_pixel = 100;
    cam.max_depth = 10;

    cam.v_fov = 60;
    cam.up = Vec3(0,1,0);

    cam.defocus_angle = 0.;
    cam.focus_dist = 10.;

    cam.parallelism = false;

    cam.background = degradated_background;

    string im_title = "LambertianExample";
    string file_dir = "images/";
    string file_name = "im_rt_" + to_string(im_width) + "x" + to_string(im_height) + "_cc=" + cam_center.repr_string() \
                        + "_cd=" + cam_dir.repr_string() + "_cup=" + cam.up.repr_string() + "_spm=" + \
                        clean_string(cam.samples_per_pixel) + "_md=" + clean_string(cam.max_depth) + "_vfov=" + \
                        clean_string(cam.v_fov) + "_da=" + clean_string(cam.defocus_angle) + "_fd=" + \
                        clean_string(cam.focus_dist) + "_" + im_title + ".ppm";
    ofstream fout(file_dir + file_name);
    cout << file_dir + file_name << "\n";
    if (!fout) {cerr << "Erreur lors de l'ouverture du fichier !"; return 1;}

    cam.render(fout, world);

    return 0;
}

int metalExample() {
    auto world = Hittable_list();

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    auto c1 = Color(0.8, 0.8, 0.8);
    auto c2 = Color(0.2, 0.2, 0.2);
    auto material0 = make_shared<Metal>(c1, 0.);
    auto material1 = make_shared<Metal>(0.5 * c1 + 0.5 * c2, 0.4);
    auto material2 = make_shared<Metal>(c2, 0.8);
    world.add(make_shared<Sphere>(Point3(-1.3,0.65,0.5), 0.6, material0));
    world.add(make_shared<Sphere>(Point3(0.,0.65,0.5), 0.6, material1));
    world.add(make_shared<Sphere>(Point3(+1.3,0.65,0.5), 0.6, material2));

    double im_ratio = 1.;
    int im_width = 512;
    int im_height = im_width / static_cast<int>(im_ratio);
    Point3 cam_center = {0., 0.5, -2.};
    Vec3 cam_dir = Point3(0., 0., 1.);
    Camera cam(im_ratio, im_width, cam_center, cam_dir);

    cam.samples_per_pixel = 100;
    cam.max_depth = 10;

    cam.v_fov = 60;
    cam.up = Vec3(0,1,0);

    cam.defocus_angle = 0.;
    cam.focus_dist = 10.;

    cam.parallelism = false;

    cam.background = degradated_background;

    string im_title = "MetalExampleByFuzz(0.8-0.4-0.)";
    string file_dir = "images/";
    string file_name = "im_rt_" + to_string(im_width) + "x" + to_string(im_height) + "_cc=" + cam_center.repr_string() \
                        + "_cd=" + cam_dir.repr_string() + "_cup=" + cam.up.repr_string() + "_spm=" + \
                        clean_string(cam.samples_per_pixel) + "_md=" + clean_string(cam.max_depth) + "_vfov=" + \
                        clean_string(cam.v_fov) + "_da=" + clean_string(cam.defocus_angle) + "_fd=" + \
                        clean_string(cam.focus_dist) + "_" + im_title + ".ppm";
    ofstream fout(file_dir + file_name);
    cout << file_dir + file_name << "\n";
    if (!fout) {cerr << "Erreur lors de l'ouverture du fichier !"; return 1;}

    cam.render(fout, world);

    return 0;
}

int dielectricExample() {
    auto world = Hittable_list();

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    auto glass = make_shared<Dielectric>(1.5);
    auto air_in_glass = make_shared<Dielectric>(1./1.5);
    auto air_in_water = make_shared<Dielectric>(1./1.33);
    world.add(make_shared<Sphere>(Point3(-0.85,0.85,0.5), 0.8, glass));
    world.add(make_shared<Sphere>(Point3(-0.85,0.85,0.5), 0.6, air_in_glass));
    world.add(make_shared<Sphere>(Point3(+0.85,0.85,0.5), 0.8, air_in_water));

    double im_ratio = 1.;
    int im_width = 512;
    int im_height = im_width / static_cast<int>(im_ratio);
    Point3 cam_center = {0., 0.5, -2.};
    Vec3 cam_dir = Point3(0., 0., 1.);
    Camera cam(im_ratio, im_width, cam_center, cam_dir);

    cam.samples_per_pixel = 100;
    cam.max_depth = 10;

    cam.v_fov = 60;
    cam.up = Vec3(0,1,0);

    cam.defocus_angle = 0.;
    cam.focus_dist = 10.;

    cam.parallelism = false;

    cam.background = degradated_background;

    string im_title = "DielectricExamples(air_in_water-shield_of_glass)";
    string file_dir = "images/";
    string file_name = "im_rt_" + to_string(im_width) + "x" + to_string(im_height) + "_cc=" + cam_center.repr_string() \
                        + "_cd=" + cam_dir.repr_string() + "_cup=" + cam.up.repr_string() + "_spm=" + \
                        clean_string(cam.samples_per_pixel) + "_md=" + clean_string(cam.max_depth) + "_vfov=" + \
                        clean_string(cam.v_fov) + "_da=" + clean_string(cam.defocus_angle) + "_fd=" + \
                        clean_string(cam.focus_dist) + "_" + im_title + ".ppm";
    ofstream fout(file_dir + file_name);
    cout << file_dir + file_name << "\n";
    if (!fout) {cerr << "Erreur lors de l'ouverture du fichier !"; return 1;}

    cam.render(fout, world);

    return 0;
}

int sphere_field_demo() {
    auto world = Hittable_list();

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point3(4, 0.2, 0)).norm() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    double im_ratio = 1.;
    int im_width = 512;
    int im_height = im_width / static_cast<int>(im_ratio);
    Point3 cam_center = {13, 2., 3.};
    Vec3 cam_dir = Point3(-13., -2., -3.);
    Camera cam(im_ratio, im_width, cam_center, cam_dir);

    cam.samples_per_pixel = 250;
    cam.max_depth = 50;

    cam.v_fov = 20;
    cam.up = Vec3(0,1,0);

    cam.defocus_angle = 0.2;
    cam.focus_dist = 10.0;

    cam.parallelism = true;

    cam.background = degradated_background;

    string im_title = "Sphere_field_demo";
    string file_dir = "images/";
    string file_name = "im_rt_" + to_string(im_width) + "x" + to_string(im_height) + "_cc=" + cam_center.repr_string() \
                       + "_cd=" + cam_dir.repr_string() + "_cup=" + cam.up.repr_string() + "_spm=" + \
                       clean_string(cam.samples_per_pixel) + "_md=" + clean_string(cam.max_depth) + "_vfov=" + \
                       clean_string(cam.v_fov) + "_da=" + clean_string(cam.defocus_angle) + "_fd=" + \
                       clean_string(cam.focus_dist) + "_" + im_title + ".ppm";
    ofstream fout(file_dir + file_name);
    cout << file_dir + file_name << "\n";
    if (!fout) {cerr << "Erreur lors de l'ouverture du fichier !"; return 1;}

    cam.render(fout, world);

    return 0;
}

int testLight() {
    auto world = Hittable_list();

    auto shield_material = make_shared<Lambertian>(Color(0.2, 0.2, 0.));
    world.add(make_shared<Sphere>(Point3(0,0,0), 3, shield_material));

    auto material0 = make_shared<Lambertian>(Color(0.2, 0., 0.4));
    world.add(make_shared<Sphere>(Point3(0,0.65,0.5), 0.4, material0));

    auto light_material = make_shared<Diffuse_light>(Color(1.0, 1.0, 1.0));
    world.add(make_shared<Sphere>(Point3(1.2, 1., 0), 0.6, light_material));

    double im_ratio = 1.;
    int im_width = 512;
    int im_height = im_width / static_cast<int>(im_ratio);
    Point3 cam_center = {0., 0.5, -2.};
    Vec3 cam_dir = Point3(0., 0., 1.);
    Camera cam(im_ratio, im_width, cam_center, cam_dir);

    cam.samples_per_pixel = 500;
    cam.max_depth = 10;

    cam.v_fov = 60;
    cam.up = Vec3(0,1,0);

    cam.defocus_angle = 0.;
    cam.focus_dist = 10.;

    cam.parallelism = true;

    cam.background = degradated_background;

    string im_title = "LightExample";
    string file_dir = "images/";
    string file_name = "im_rt_" + to_string(im_width) + "x" + to_string(im_height) + "_cc=" + cam_center.repr_string() \
                        + "_cd=" + cam_dir.repr_string() + "_cup=" + cam.up.repr_string() + "_spm=" + \
                        clean_string(cam.samples_per_pixel) + "_md=" + clean_string(cam.max_depth) + "_vfov=" + \
                        clean_string(cam.v_fov) + "_da=" + clean_string(cam.defocus_angle) + "_fd=" + \
                        clean_string(cam.focus_dist) + "_" + im_title + ".ppm";
    ofstream fout(file_dir + file_name);
    cout << file_dir + file_name << "\n";
    if (!fout) {cerr << "Erreur lors de l'ouverture du fichier !"; return 1;}

    cam.render(fout, world);

    return 0;
}
