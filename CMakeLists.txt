cmake_minimum_required(VERSION 4.0)
project(TIPE_Ray_Tracing)


include(FetchContent)
FETCHCONTENT_DECLARE(GLFW GIT_REPOSITORY https://github.com/glfw/glfw.git)
FETCHCONTENT_MAKEAVAILABLE(GLFW)
FETCHCONTENT_DECLARE(GLM GIT_REPOSITORY https://github.com/g-truc/glm)
FETCHCONTENT_MAKEAVAILABLE(GLM)

add_executable(TIPE_Ray_Tracing
        main.cpp
        Vec3.cpp
        Scenes.cpp
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
        Sphere.cpp
        Triangle.cpp)

target_include_directories(TIPE_Ray_Tracing PRIVATE C:/VulkanSDK/1.4.328.1)

find_package(Vulkan REQUIRED)
if (Vulkan_FOUND)
    include_directories(${Vulkan_INCLUDE_DIRS})
    link_directories(${Vulkan_LIBRARY_DIRS})
endif()

set(CMAKE_CXX_STANDARD 20)

target_link_libraries(TIPE_Ray_Tracing glfw ${Vulkan_LIBRARIES})
target_link_libraries(TIPE_Ray_Tracing glm ${Vulkan_LIBRARIES})
