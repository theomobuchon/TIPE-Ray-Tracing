#include "Raytracer.hpp"
#include "Vec3.cpp"
#include "Ray.cpp"
#include "Camera.cpp"
#include "Sphere.cpp"
#include "Material.cpp"
#include "Hittable_list.cpp"
#include <chrono>
#include <memory>

using namespace std;

int main() {
    Hittable_list world;

    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.8));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Dielectric>(1./1.33);
    auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.1);

    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5, material_center));
    world.add(make_shared<Sphere>(Point3(0, -100.5, 1), 100, material_ground));
    world.add(make_shared<Sphere>(Point3(1.2, 0, -1), 0.5, material_right));
    world.add(make_shared<Sphere>(Point3(-1.2, 0, -1), 0.5, material_left));

    ofstream fout("im_rt.ppm");
    constexpr int im_width = 1024;
    Camera cam(16./9., im_width, 1., Point3(0, 0, 1.), 100);
    cam.m_max_depth = 10;

    auto start = chrono::high_resolution_clock::now();
    cam.render(fout, world);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end - start);
    cout << "Execution time: " << duration.count() << " seconds" << endl;
}
