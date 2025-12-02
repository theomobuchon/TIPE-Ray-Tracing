//
// Created by nolan on 22/11/2025.
//

#include "BVH_node.hpp"
#include <algorithm>
#include <assert.h>

#include "Raytracer.hpp"
#include <iostream>

BVH_node::BVH_node(Hittable_list h_list): BVH_node(h_list.m_objects, 0, h_list.m_objects.size()) {}

BVH_node::BVH_node(std::vector<std::shared_ptr<Hittable>> &objects, size_t start, size_t end) {
    const int axis = random_int(0, 2);

    const auto comparator = box_y_compare;//(axis == 0) ? box_x_compare
                                   //: (axis == 1) ? box_y_compare
                                   //: box_z_compare;

    const size_t span = end - start;

    if (span == 1) {
        m_left = objects[start];
        m_right = objects[start];
    } else if (span == 2) {
        m_left = objects[start];
        m_right = objects[start + 1];
    } else {
        std::sort(std::begin(objects) + start, std::begin(objects) + end, comparator);
        auto mid = start + span / 2;
        m_left = make_shared<BVH_node>(objects, start, mid);
        m_right = make_shared<BVH_node>(objects, mid, end);
    }

    m_bbox = AABB(m_left->bounding_box(), m_right->bounding_box());
}

bool BVH_node::hit(const Ray &ray, const Interval int_valid, Hit_record &rec) const {
    if (!m_bbox.hit(ray, int_valid)) {
        return false;
    }

    const bool hit_left = m_left->hit(ray, int_valid, rec);
    const bool hit_right = m_right->hit(ray, Interval(int_valid.min(), hit_left ? rec.m_t : int_valid.max()), rec);

    return hit_left || hit_right;
}

AABB BVH_node::bounding_box() const {
    return m_bbox;
}

bool BVH_node::box_compare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b, const int axis_index) {
    const auto a_interval = a->bounding_box().axis_interval(axis_index);
    const auto b_interval = b->bounding_box().axis_interval(axis_index);
    return a_interval.min() <= b_interval.min();
}

bool BVH_node::box_x_compare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b) {
    assert(a != nullptr);
    return box_compare(a, b, 0);
}

bool BVH_node::box_y_compare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b) {
    static int i = 0;
    cout << i++ << endl;
    assert(a != nullptr);
    return box_compare(a, b, 1);
}

bool BVH_node::box_z_compare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b) {
    assert(a != nullptr);
    return box_compare(a, b, 2);
}
