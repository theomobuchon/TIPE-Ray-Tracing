//
// Created by nolan on 10/02/2026.
//
#include "MeshReader.hpp"
#include <iostream>
#include <sstream>
#include "Raytracer.hpp"
#include "Triangle.hpp"

using namespace std;

MeshReader::MeshReader(const std::string &source_file, const std::shared_ptr<Material> &material): m_material(material) {
    ifstream fin(source_file, ios::in);
    if (fin.is_open()) {
        string line;
        while (std::getline(fin, line)) {
            stringstream ss(line);
            string mode;
            ss >> mode;

            if (mode == "v") {
                float x, y, z;
                ss >> x >> y >> z;
                m_points.emplace_back(x, y, z);
            }

            if (mode == "vn") {
                float x, y, z;
                ss >> x >> y >> z;
                m_normals.emplace_back(x, y, z);
            }

            if (mode == "f") {
                array<int, 4> tr{};
                for (int i = 0; i < 3; i++) {
                    string som;
                    ss >> som;
                    vector<string> vs = splitString(som, '/');
                    tr[i] = std::stoi(vs[0])-1;
                    if (vs.size() > 1) tr[3] = std::stoi(vs[2])-1;
                }
                m_triangles.emplace_back(tr);
            }
        }
    }
    else {
        cout << source_file << endl;
        cout << "Could not open the mesh file" << endl;
    }
    fin.close();
}

vector<shared_ptr<Hittable>> MeshReader::convert() const {
    vector<shared_ptr<Hittable>> tr_list;
    tr_list.reserve(m_triangles.size());
    cout << m_normals.size() << endl;
    for (const auto tr_brack: m_triangles) {
        auto s1 = m_points[tr_brack[0]];
        auto s2 = m_points[tr_brack[1]];
        auto s3 = m_points[tr_brack[2]];
        auto n = m_normals[tr_brack[3]];
        tr_list.emplace_back(make_shared<Triangle>(s1, s2, s3, n, m_material));
    }
    return tr_list;
}
