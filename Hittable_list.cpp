//
// Created by nolan on 01/11/2025.
//

#include "Hittable_list.hpp"

using namespace std;

Hittable_list::Hittable_list() = default;

Hittable_list::Hittable_list(const shared_ptr<Hittable> &object) {
    add(object);
}

Hittable_list &Hittable_list::operator=(const Hittable_list &hittable_list) = default;

void Hittable_list::add(const shared_ptr<Hittable> &object) {
    m_objects.push_back(object);
}

void Hittable_list::clear() {
    m_objects.clear();
}

bool Hittable_list::hit(const Ray &ray, Interval int_valid, Hit_record &rec) const {
    Hit_record tempRec = rec;
    auto hit_anything = false;
    auto closest = int_valid.max();

    for (const shared_ptr<Hittable> &object : m_objects) {
        if (object->hit(ray, Interval(int_valid.min(), closest), tempRec)) {
            hit_anything = true;
            closest = tempRec.m_t;
            rec = tempRec;
        }
    }

    return hit_anything;
}
