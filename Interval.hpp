//
// Created by nolan on 01/11/2025.
//

#ifndef TIPE_RAY_TRACING_INTERVAL_HPP
#define TIPE_RAY_TRACING_INTERVAL_HPP

class Interval {
public:
    Interval();
    Interval(double min, double max);
    Interval(const Interval &i1, const Interval &i2);
    Interval &operator=(const Interval &interval);
    [[nodiscard]] Interval expand(double delta) const;
    [[nodiscard]] double min() const;
    [[nodiscard]] double max() const;
    [[nodiscard]] bool contains(double value) const;
    [[nodiscard]] bool surrounds(double value) const;
    [[nodiscard]] double clamp(double value) const;
    [[nodiscard]] double size() const;
    void setMin(double min);
    void setMax(double max);

    static const Interval empty, universe;

protected:
    double m_min;
    double m_max;
};

#endif //TIPE_RAY_TRACING_INTERVAL_HPP