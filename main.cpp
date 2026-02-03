#include <chrono>
#include <iostream>
#include "Scenes.hpp"

using namespace std;

int test() {
    for (int i=100; i>0; i--) {
        random_double_uniform();
    }
    return 0;
}

int main() {
    const auto start = chrono::high_resolution_clock::now();

    int out;
    switch(0) {
        case 0: out = lambertianExample(); break;
        case 1: out = dielectricExample(); break;
        case 2: out = metalExample(); break;
        case 3: out = sphere_field_demo(); break;
        case 4: out = testLight(); break;
        case 5: out = empty_cornel_box(); break;
        default: out = test();
    }

    const auto end = chrono::high_resolution_clock::now();
    const auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Execution time: " << duration.count() << " seconds" << endl;

    return out;
}
