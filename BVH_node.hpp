//
// Created by nolan on 22/11/2025.
//

#ifndef TIPE_RAY_TRACING_BVH_NODE_HPP
#define TIPE_RAY_TRACING_BVH_NODE_HPP

#include "AABB.hpp"
#include "Hittable.hpp"
#include "Hittable_list.hpp"
#include <memory>

class BVH_node: public Hittable{
public:
    explicit BVH_node (Hittable_list h_list);
    BVH_node (std::vector<std::shared_ptr<Hittable>> &objects, size_t start, size_t end);
    bool hit(const Ray &ray, Interval int_valid, Hit_record &rec) const override;
    [[nodiscard]] AABB bounding_box() const override;

protected:
    static bool box_compare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b, int axis_index);
    static bool box_x_compare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b);
    static bool box_y_compare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b);
    static bool box_z_compare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b);

    std::shared_ptr<Hittable> m_left, m_right;
    AABB m_bbox;
};


#endif //TIPE_RAY_TRACING_BVH_NODE_HPP