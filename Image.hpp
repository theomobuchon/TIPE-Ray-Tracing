//
// Created by nolan on 09/12/2025.
//

#ifndef TIPE_RAY_TRACING_IMAGE_HPP
#define TIPE_RAY_TRACING_IMAGE_HPP

#include <vector>

class Image {
public:
    Image();

protected:
    const double m_ratio; // The ration of the image rendered
    const int m_im_width; // The width of the image rendered
    std::vector<std::vector<int>> m_pixels;
};


#endif //TIPE_RAY_TRACING_IMAGE_HPP