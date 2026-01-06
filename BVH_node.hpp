#ifndef TIPE_RAY_TRACING_BVH_NODE_HPP
#define TIPE_RAY_TRACING_BVH_NODE_HPP

#include "Hittable.hpp"
#include "AABB.hpp"
#include <vector>
#include <memory>

class BVH_node final : public Hittable {
public:
    // Constructeur : construit l'arbre BVH de manière récursive
    BVH_node(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end);

    // Constructeur explicite pour construire depuis toute la liste
    explicit BVH_node(std::vector<std::shared_ptr<Hittable>>& objects)
        : BVH_node(objects, 0, objects.size()) {}

    // Teste l'intersection avec un rayon
    bool hit(const Ray& ray, Interval ray_t, Hit_record& rec) const override;
    
    // Retourne la boîte englobante de ce nœud
    [[nodiscard]] AABB bounding_box() const override;

private:
    // Les deux enfants du nœud
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;
    
    // La boîte englobante du nœud
    AABB bbox;

    // === FONCTIONS UTILITAIRES ===
    
    // Calcule la boîte englobante d'un groupe d'objets
    static AABB bounding_box_of_objects(
        const std::vector<std::shared_ptr<Hittable>>& objects,
        size_t start, 
        size_t end
    );

    // Compare deux objets selon un axe (0=X, 1=Y, 2=Z)
    static bool box_compare(
        const std::shared_ptr<Hittable>& a,
        const std::shared_ptr<Hittable>& b,
        int axis
    );

    // Comparateurs spécifiques pour chaque axe (utilisés par std::sort)
    static bool box_x_compare(
        const std::shared_ptr<Hittable>& a, 
        const std::shared_ptr<Hittable>& b
    );

    static bool box_y_compare(
        const std::shared_ptr<Hittable>& a, 
        const std::shared_ptr<Hittable>& b
    );

    static bool box_z_compare(
        const std::shared_ptr<Hittable>& a, 
        const std::shared_ptr<Hittable>& b
    );
};

#endif
