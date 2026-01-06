#include <chrono>
#include <iostream>
#include "Scenes.hpp"

using namespace std;

int test() {
    auto f = ofstream("../Bjj", ios::trunc);
    if (!f) {cerr << "Error when opening" << endl; return 1;}

    f << "tuest" << endl;
    return 0;
}

int main() {
    const auto start = chrono::high_resolution_clock::now();

    int out;
    switch(5) {
        case 0: out = lambertianExample(); break;
        case 1: out = dielectricExample(); break;
        case 2: out = metalExample(); break;
        case 3: out = sphere_field_demo(); break;
        case 4: out = testLight(); break;
        case 5: out = empty_cornel_box(); break;
        default: out = test();
    }

    const auto end = chrono::high_resolution_clock::now();
    const auto duration = chrono::duration_cast<chrono::seconds>(end - start);
    cout << "Execution time: " << duration.count() << " seconds" << endl;

    return out;
}
