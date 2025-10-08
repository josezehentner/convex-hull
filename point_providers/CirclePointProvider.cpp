#include "CirclePointProvider.h"
#include <cmath>

CirclePointProvider::CirclePointProvider(int count, int width, int height, int margin)
    : m_count(count), m_width(width), m_height(height), m_margin(margin) {}

std::vector<Point> CirclePointProvider::getPoints() {
    std::vector<Point> points;
    points.reserve(m_count);

    float cx = static_cast<float>(m_width) / 2.0f;
    float cy = static_cast<float>(m_height) / 2.0f;
    float radius = std::min(cx, cy) - static_cast<float>(m_margin);

    if (radius <= 0.0f) {
        return points;
    }

    const float twoPi = 2.0f * static_cast<float>(M_PI);
    for (int i = 0; i < m_count; i++) {
        float angle = (twoPi * i) / static_cast<float>(m_count);
        int x = static_cast<int>(std::round(cx + radius * std::cos(angle)));
        int y = static_cast<int>(std::round(cy + radius * std::sin(angle)));
        points.push_back(Point{static_cast<float>(x), static_cast<float>(y)});
    }

    return points;
}
