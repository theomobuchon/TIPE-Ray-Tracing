#include <chrono>
#include <iostream>
#include "Scenes.cpp"

using namespace std;

int test() {
    const auto start = chrono::high_resolution_clock::now();
    for (int i=0; i<1000000; i++) {
        random_double_uniform();
    }
    const auto inter = chrono::high_resolution_clock::now();
    for (int i=0; i<1000000; i++) {
        random_double_gaussian();
    }
    const auto end = chrono::high_resolution_clock::now();
    const auto duration_uniform = chrono::duration_cast<chrono::milliseconds>(inter - start);
    const auto duration_gaussian = chrono::duration_cast<chrono::milliseconds>(end - inter);
    cout << "Execution time for the uniform distribution : " << duration_uniform.count() << " milliseconds" << endl;
    cout << "Execution time for the gaussian distribution : " << duration_gaussian.count() << " milliseconds" << endl;

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
