#include <chrono>
#include <dinput.h>
#include <iostream>
#include "Scenes.hpp"

using namespace std;

int test() {
    string test = "123 // 12 214.98 // 1 199.96 // 23";
    vector<string> v = splitString(test, '/');
    cout << v[2] << endl;
    return 0;
}

int main() {
    const auto start = chrono::high_resolution_clock::now();

    int out;
    switch(2) {
        case 0: out = lambertianExample(); break;
        case 1: out = dielectricExample(); break;
        case 2: out = metalExample(); break;
        case 3: out = sphere_field_demo(); break;
        case 4: out = testLight(); break;
        case 5: out = empty_cornel_box(); break;
        case 6: out = test_mesh(); break;
        default: out = test();
    }

    const auto end = chrono::high_resolution_clock::now();
    const auto duration = chrono::duration_cast<chrono::seconds>(end - start);
    cout << "Execution time: " << duration.count() << " seconds" << endl;
    Beep(440, 2000);

    return out;
}
