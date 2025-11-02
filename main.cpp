#include "Raytracer.hpp"
#include "Camera.cpp"
#include "Sphere.cpp"
#include "Hittable_list.cpp"
#include <chrono>

using namespace std;

int main() {
    Hittable_list world;
    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, 1), 100));
    world.add(make_shared<Sphere>(Point3(0.75, 0.5, -2), 0.5));

    ofstream fout("im_rt.ppm");
    constexpr int im_width = 1024;
    Camera cam(16./9., im_width, 1., Point3(0, 0, 0), 100);
    cam.antialiasing = true;

    auto start = chrono::high_resolution_clock::now();
    cam.render(fout, world);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end - start);
    cout << "Execution time: " << duration.count() << " seconds" << endl;
}
