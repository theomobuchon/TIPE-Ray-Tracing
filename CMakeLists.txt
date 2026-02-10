cmake_minimum_required(VERSION 4.0)
project(TIPE_RAYTRACING)

add_executable(TIPE_RAYTRACING
        main.cpp
        AABB.cpp
        BVH_node.cpp
        Camera.cpp
        Hittable.cpp
        Hittable_list.cpp
        Image.cpp
        Interval.cpp
        Material.cpp
        Ray.cpp
        Rectangle.cpp
        Scenes.cpp
        Sphere.cpp
        Triangle.cpp
        Vec3.cpp
        MeshReader.cpp
)

set(CMAKE_CXX_STANDARD 20)
