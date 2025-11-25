//
// Created by nolan on 01/11/2025.
//

#include "Interval.hpp"
#include "Raytracer.hpp"

const Interval Interval::empty = Interval(+infinite, -infinite);
const Interval Interval::universe = Interval(-infinite, +infinite);

Interval::Interval(): m_min(+infinite), m_max(-infinite) {

}

Interval::Interval(double min, double max) : m_min(min), m_max(max) {

}

Interval::Interval(const Interval &i1, const Interval &i2) {
    m_min = i1.min() <= i2.min() ? i1.min() : i2.min();
    m_max = i1.max() >= i2.max() ? i1.max() : i2.max();
}

Interval &Interval::operator=(const Interval &interval) = default;

Interval Interval::expand(double delta) const {
    double pas = delta / 2;
    return {m_min - pas, m_max + pas};
}

double Interval::min() const {
    return m_min;
}

double Interval::max() const {
    return m_max;
}

double Interval::size() const {
    return m_max - m_min;
}

void Interval::setMin(const double min) {
    m_min = min;
}

void Interval::setMax(const double max) {
    m_max = max;
}

bool Interval::contains(const double value) const {
    return m_min <= value && value <= m_max;
}

bool Interval::surrounds(const double value) const {
    return m_min < value && value < m_max;
}

double Interval::clamp(const double value) const {
    if (value < m_min) return m_min;
    if (value > m_max) return m_max;
    return value;
}

