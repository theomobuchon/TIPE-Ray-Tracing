#include "Raytracer.hpp"
#include "Vec3.cpp"
#include "Ray.cpp"
#include "Camera.cpp"
#include "Sphere.cpp"
#include "Material.cpp"
#include "Hittable_list.cpp"
#include <chrono>
#include <memory>
#include <string>

using namespace std;

string clean_string(const double d) {
    string s = to_string(d);
    s.erase(s.find_last_not_of('0') + 1, string::npos);
    return s;
}

int main() {
    auto world = Hittable_list();

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

/*Metal example
    auto c1 = Color(0., 0.5, 0.);
    auto c2 = Color(0., 0., 0.2);
    auto material0 = make_shared<Metal>(c1, 0.2);
    auto material2 = make_shared<Metal>(0.5 * c1 + 0.5 * c2, 0.6);
    auto material4 = make_shared<Metal>(c2, 1.);
    world.add(make_shared<Sphere>(Point3(-1.3,0.6,0.5), 0.6, material0));
    world.add(make_shared<Sphere>(Point3(0.,0.6,0.5), 0.6, material2));
    world.add(make_shared<Sphere>(Point3(+1.3,0.6,0.5), 0.6, material4));
*/

    auto glass = make_shared<Dielectric>(1.5);
    auto air_in_glass = make_shared<Dielectric>(1./1.5);
    auto air_in_water = make_shared<Dielectric>(1./1.33);
    world.add(make_shared<Sphere>(Point3(-0.85,0.85,0.5), 0.8, glass));
    world.add(make_shared<Sphere>(Point3(-0.85,0.85,0.5), 0.6, air_in_glass));
    world.add(make_shared<Sphere>(Point3(+0.85,0.85,0.5), 0.8, air_in_water));

    double im_ratio = 1.;
    int im_width = 512;
    int im_height = im_width / static_cast<int>(im_ratio);
    Point3 cam_center = {0, 3., -3.};
    Vec3 cam_dir = Point3(0., 0.8, 0.5) - cam_center;
    Camera cam(im_ratio, im_width, cam_center, cam_dir);

    cam.samples_per_pixel = 100;
    cam.max_depth = 10;

    cam.v_fov = 60;
    cam.up = Vec3(0,1,0);

    cam.defocus_angle = 0;
    cam.focus_dist = 10.0;

    cam.parallelism = false;

    string im_title = "DielectricExamples(air_in_water-shield_of_glass)";
    string file_dir = "images/";
    string file_name = "im_rt_" + to_string(im_width) + "x" + to_string(im_height) + "_cc=" + cam_center.repr_string() \
                        + "_cd=" + cam_dir.repr_string() + "_cup=" + cam.up.repr_string() + "_spm=" + \
                        clean_string(cam.samples_per_pixel) + "_md=" + clean_string(cam.max_depth) + "_vfov=" + \
                        clean_string(cam.v_fov) + "_da=" + clean_string(cam.defocus_angle) + "_fd=" + \
                        clean_string(cam.defocus_angle) + "_" + im_title + ".ppm";
    ofstream fout(file_dir + file_name);
    cout << file_dir + file_name << "\n";
    if (!fout) {cerr << "Erreur lors de l'ouverture du fichier !"; return 1;}

    auto start = chrono::high_resolution_clock::now();
    cam.render(fout, world);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end - start);
    cout << "Execution time: " << duration.count() << " seconds" << endl;
}
