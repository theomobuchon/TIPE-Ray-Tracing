#include <chrono>
#include <iostream>
#include "Scenes.cpp"

using namespace std;

int main() {
    const auto start = chrono::high_resolution_clock::now();

    int out;
    switch(2) {
        case 0: out = lambertianExample(); break;
        case 1: out = dielectricExample(); break;
        case 2: out = metalExample(); break;
        case 3: out = sphere_field_demo(); break;
        case 4: out = testLight(); break;
        default: out = 0;
    }

    const auto end = chrono::high_resolution_clock::now();
    const auto duration = chrono::duration_cast<chrono::seconds>(end - start);
    cout << "Execution time: " << duration.count() << " seconds" << endl;

    return out;
}
