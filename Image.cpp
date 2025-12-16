//
// Created by nolan on 09/12/2025.
//

#include "Image.hpp"
#include "Interval.hpp"
#include <iostream>

using namespace std;

Image::Image(const int im_width, const int im_height) : m_im_width(im_width), m_im_height(im_height) {
    for (int i = 0; i < im_width; i++) {
        vector<Color> colors;
        for (int j = 0; j < im_height; j++) {
            colors.emplace_back();
        }
        m_pixels.emplace_back(colors);
    }
}

void Image::write_color(const int i, const int j, const Color &color){
    m_pixels.at(i).at(j) = color;
}

void Image::write_result(std::ofstream &fout) const {
    fout << "P3\n" << m_im_width << " " << m_im_height << "\n255\n";
    for (int j = 0; j < m_im_height; j++) {
        for (int i = 0; i < m_im_width; i++) {
            Color color = m_pixels.at(i).at(j);

            static const Interval intensity(0., 0.999);
            const double x = linear_to_gamma(color.x());
            const double y = linear_to_gamma(color.y());
            const double z = linear_to_gamma(color.z());

            const int red_byte = static_cast<int>(256 * intensity.clamp(x));
            const int green_byte = static_cast<int>(256 * intensity.clamp(y));
            const int blue_byte = static_cast<int>(256 * intensity.clamp(z));

            fout << red_byte << " " << green_byte << " " << blue_byte << std::endl;
        }
    }
}
