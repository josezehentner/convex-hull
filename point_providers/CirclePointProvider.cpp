#include "CirclePointProvider.h"

#include <cmath>
#include <vector>

CirclePointProvider::CirclePointProvider(int count, long width, long height, int margin)
    : m_count(count), m_width(width), m_height(height), m_margin(margin) {}

std::vector<Point> CirclePointProvider::getPoints() {
    std::vector<Point> points;
    if (m_count == 0) {
        return points;
    }

    points.reserve(m_count);

    const float cx = m_height * 0.5f;
    const float cy = m_height * 0.5f;
    const float r  = 0.45f * m_height;
    const float two_pi = 2 * M_PI;

    for (std::size_t i = 0; i < m_count; ++i) {
        float t = two_pi * static_cast<float>(i) / static_cast<float>(m_count);
        Point p{};
        p.x = cx + r * std::cos(t);
        p.y = cy + r * std::sin(t);
        points.push_back(p);
    }
    return points;
}