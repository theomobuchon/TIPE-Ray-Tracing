//
// Created by nolan on 01/11/2025.
//

#include "Interval.hpp"

#include <iostream>

#include "Raytracer.hpp"

const Interval Interval::empty = Interval(+infinite, -infinite);
const Interval Interval::universe = Interval(-infinite, +infinite);

Interval::Interval(): m_min(+infinite), m_max(-infinite) {

}

Interval::Interval(const float min, const float max) : m_min(min), m_max(max) {
}

Interval::Interval(const Interval &i1, const Interval &i2) {
    m_min = i1.min() <= i2.min() ? i1.min() : i2.min();
    m_max = i1.max() >= i2.max() ? i1.max() : i2.max();
}

Interval &Interval::operator=(const Interval &interval) = default;

Interval Interval::expand(float delta) const {
    float pas = delta / 2;
    return {m_min - pas, m_max + pas};
}

float Interval::min() const {
    return m_min;
}

float Interval::max() const {
    return m_max;
}

float Interval::size() const {
    return m_max - m_min;
}

float Interval::center() const {
    return m_min + (m_max - m_min) / 2;
}

Interval Interval::merge(const Interval &i1, const Interval &i2) {
    const float min = i1.min() <= i2.min() ? i1.min() : i2.min();
    const float max = i1.max() >= i2.max() ? i1.max() : i2.max();
    return {min, max};
}

void Interval::setMin(const float min) {
    m_min = min;
}

void Interval::setMax(const float max) {
    m_max = max;
}

bool Interval::contains(const float value) const {
    return m_min <= value && value <= m_max;
}

bool Interval::surrounds(const float value) const {
    return m_min < value && value < m_max;
}

float Interval::clamp(const float value) const {
    if (value < m_min) return m_min;
    if (value > m_max) return m_max;
    return value;
}

