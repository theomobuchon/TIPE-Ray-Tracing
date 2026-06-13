#include <chrono>
#include <dinput.h>
#include <iostream>
#include "Raytracer.hpp"
#include "Scenes.hpp"

using namespace std;

int test() {
    string test = "123 // 12 214.98 // 1 199.96 // 23";
    vector<string> v = splitString(test, '/');
    cout << v[2] << endl;
    return 0;
}

string convert_tab(vector<string> tab) {
    string ns = "";
    for (int i = 0; i < tab.size(); i++) {
        if (i < tab.size() - 1) ns += tab[i] + ";";
        else ns += tab[i];
    }
    return ns;
}

void send_data(string path, vector<string> data) {
    ofstream file(path);
    file << convert_tab(data);
    file.close();

    string command = "python ../send_data.py " + path;
    system(command.c_str());
}

int test_battery() {
    vector<string> battery;
    int nbs[28] = {1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000};
    for (int nb: nbs) {
        for (int i=2; i < 3; i++) {
            cout << nb << endl;
            const auto start = chrono::high_resolution_clock::now();

            float im_ratio = 1.;
            int im_width = 512;
            Point3 cam_center = {278, 278, -800};
            auto cam_dir = Point3(0., 0., 800);
            Camera cam(im_ratio, im_width, cam_center, cam_dir);
            bool BVH = true;
            bool para = true;

            lambertianCube(nb, BVH, cam, para);

            const auto end = chrono::high_resolution_clock::now();
            const auto total_duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << "Execution time: " << total_duration.count() << " milliseconds\n" << endl;

            string row = "lambertians cube," +
                            to_string(nb) + ","
                            + to_string(im_width) + "x" + to_string(static_cast<int>(im_width * im_ratio)) + ","
                            + to_string(cam.samples_per_pixel) + ","
                            + to_string(cam.max_depth) + ","
                            + (BVH ? "oui," : "non,")
                            + (para ? "CPU," : "Aucune,")
                            + to_string(total_duration.count() / 1000.f);
            battery.push_back(row);
        }
        send_data("../data.txt", battery);
        battery.clear();
    }

    return 0;
}

int classic(int c) {
    const auto start = chrono::high_resolution_clock::now();

    int out;
    switch(c) {
        case 0: out = lambertianExample(); break;
        case 1: out = dielectricExample(); break;
        case 2: out = metalExample(); break;
        case 3: out = sphere_field_demo(); break;
        case 4: out = testLight(); break;
        case 5: out = empty_cornel_box(); break;
        case 6: out = test_mesh(); break;
        case 7: out = lambertianCube(); break;
        default: out = test();
    }

    const auto end = chrono::high_resolution_clock::now();
    const auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
    Beep(440, 2000);

    return out;
}

int main() {
    bool est_classic = true;
    if (est_classic) return classic(0);
    else return test_battery();
}
