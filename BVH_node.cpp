#include "BVH_node.hpp"
#include <algorithm>
#include <iostream>

using namespace std;


//=== FONCTIONS UTILITAIRES ===

// Calcule la boîte englobante de tous les objets entre start et end
AABB BVH_node::bounding_box_of_objects(
    const vector<shared_ptr<Hittable>>& objects,
    const size_t start,
    const size_t end
) {
    // Commence avec la boîte du premier objet
    AABB temp_box = objects[start]->bounding_box();
    
    // Fusionne avec toutes les autres boîtes
    for (size_t i = start + 1; i < end; i++) {
        temp_box = AABB(temp_box, objects[i]->bounding_box());
    }
    
    return temp_box;
}

// Compare deux objets selon leur position sur un axe donné
bool BVH_node::box_compare(
    const shared_ptr<Hittable>& a,
    const shared_ptr<Hittable>& b,
    int axis
) {
    auto a_axis_interval = a->bounding_box().axis_interval(axis);
    auto b_axis_interval = b->bounding_box().axis_interval(axis);
    
    // Compare les positions minimales sur cet axe
    return a_axis_interval.min() < b_axis_interval.min();
}

// Comparateurs spécifiques pour std::sort
bool BVH_node::box_x_compare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b) {
    return box_compare(a, b, 0);
}

bool BVH_node::box_y_compare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b) {
    return box_compare(a, b, 1);
}

bool BVH_node::box_z_compare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b) {
    return box_compare(a, b, 2);
}


// === CONSTRUCTEUR - ALGORITHME RÉCURSIF DE CONSTRUCTION DU BVH ===

BVH_node::BVH_node(
    vector<shared_ptr<Hittable>> objects,
    size_t start,
    size_t end
) {

    const size_t object_span = end - start;


    // === CAS DE BASE : 1 ou 2 objets ===
    

    if (object_span == 1) {
        left = right = objects[start];
        bbox = objects[start]->bounding_box();
        return;
    }

    if (object_span == 2) {
        left = objects[start];
        right = objects[start + 1];
        bbox = AABB(objects[start]->bounding_box(), AABB(objects[start + 1]->bounding_box()));
        return;
    }


    // === CAS RÉCURSIF : Plus de 2 objets ===


    int axis = 0;  // Par défaut X

    const float extent_x = bbox.axis_interval(0).size();  // Taille selon X
    const float extent_y = bbox.axis_interval(1).size();  // Taille selon Y
    const float extent_z = bbox.axis_interval(2).size();  // Taille selon Z
    
    // Trouver l'axe avec la plus grande étendue
    if (extent_y > extent_x && extent_y > extent_z) {
        axis = 1;  // Y est le plus étendu
    } else if (extent_z > extent_x) {
        axis = 2;  // Z est le plus étendu
    }

    const auto comparator = (axis == 0) ? box_x_compare
                    : (axis == 1) ? box_y_compare
                                  : box_z_compare;

    sort(objects.begin() + start, objects.begin() + end, comparator);

    auto mid = start + object_span / 2;

    left = make_shared<BVH_node>(objects, start, mid);
    right = make_shared<BVH_node>(objects, mid, end);
    bbox = AABB(left->bounding_box(), right->bounding_box());

}


// === MÉTHODE HIT - PARCOURS DE L'ARBRE BVH ===


bool BVH_node::hit(const Ray& ray, const Interval ray_t, Hit_record& rec) const {
    if (!bbox.hit(ray, ray_t)) {
        return false;
    }

    const bool hit_left = left->hit(ray, ray_t, rec);

    const Interval right_interval = hit_left
        ? Interval(ray_t.min(), rec.m_t)
        : ray_t;

    const bool hit_right = right->hit(ray, right_interval, rec);

    return hit_left || hit_right;
}


// === MÉTHODE BOUNDING_BOX - Retourne la boîte englobante du nœud ===


AABB BVH_node::bounding_box() const {
    return bbox;
}
