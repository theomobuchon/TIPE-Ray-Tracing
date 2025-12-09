//
// Created by nolan on 09/12/2025.
//

#ifndef TIPE_RAY_TRACING_IMAGE_HPP
#define TIPE_RAY_TRACING_IMAGE_HPP

#include "Vec3.hpp"
#include <vector>

class Image {
public:
    Image(int im_width, int im_height);
    void write_color(int i, int j, const Color &color);
    void write_result(std::ofstream &fout) const;

protected:
    const int m_im_width; // The width of the image rendered
    const int m_im_height; // The ration of the image rendered
    std::vector<std::vector<Color>> m_pixels;
};


#endif //TIPE_RAY_TRACING_IMAGE_HPP