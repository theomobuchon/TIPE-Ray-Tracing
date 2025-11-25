//
// Created by nolan on 01/11/2025.
//

#ifndef TIPE_RAY_TRACING_HITTABLE_LIST_HPP
#define TIPE_RAY_TRACING_HITTABLE_LIST_HPP

#include <vector>
#include <memory>
#include "Hittable.hpp"
#include "Interval.hpp"
#include "Ray.hpp"

class BVH_node;

class Hittable_list final : public Hittable {
public:
    Hittable_list();
    explicit Hittable_list(const std::shared_ptr<Hittable> &object);
    Hittable_list &operator=(const Hittable_list &hittable_list);
    void add(const std::shared_ptr<Hittable> &object);
    void clear();
    bool hit(const Ray &ray, Interval int_valid, Hit_record &rec) const override;
    [[nodiscard]] AABB bounding_box() const override;

    friend BVH_node;

protected:
    std::vector<std::shared_ptr<Hittable>> m_objects;
    AABB m_bbox;
};


#endif //TIPE_RAY_TRACING_HITTABLE_LIST_HPP