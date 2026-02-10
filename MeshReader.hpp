//
// Created by nolan on 10/02/2026.
//

#ifndef TIPE_RAY_TRACING_MESHREADER_HPP
#define TIPE_RAY_TRACING_MESHREADER_HPP

#include <vector>
#include <array>
#include <string>
#include <memory>
#include "Vec3.hpp"
#include "Hittable.hpp"
#include "Material.hpp"

class MeshReader {
public:
    MeshReader(const std::string &source_file, const std::shared_ptr<Material>& material);
    [[nodiscard]] std::vector<std::shared_ptr<Hittable>> convert() const;

protected:
    std::vector<Vec3> m_points;
    std::vector<Vec3> m_normals;
    std::vector<std::array<int, 4>> m_triangles;
    std::shared_ptr<Material> m_material;
};

#endif //TIPE_RAY_TRACING_MESHREADER_HPP