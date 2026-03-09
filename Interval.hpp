//
// Created by nolan on 01/11/2025.
//

#ifndef TIPE_RAY_TRACING_INTERVAL_HPP
#define TIPE_RAY_TRACING_INTERVAL_HPP

class Interval {
public:
    Interval();
    Interval(float min, float max);
    Interval(const Interval &i1, const Interval &i2);
    Interval &operator=(const Interval &interval);
    [[nodiscard]] Interval expand(float delta) const;
    [[nodiscard]] float min() const;
    [[nodiscard]] float max() const;
    [[nodiscard]] bool contains(float value) const;
    [[nodiscard]] bool surrounds(float value) const;
    [[nodiscard]] float clamp(float value) const;
    [[nodiscard]] float size() const;
    [[nodiscard]] float center() const;
    static Interval merge(const Interval &i1, const Interval &i2);
    void setMin(float min);
    void setMax(float max);

    static const Interval empty, universe;

protected:
    float m_min;
    float m_max;
};

#endif //TIPE_RAY_TRACING_INTERVAL_HPP