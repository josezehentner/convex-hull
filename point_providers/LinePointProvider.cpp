#include "LinePointProvider.h"

LinePointProvider::LinePointProvider(int count, int width, int height, int margin)
    : m_count(count), m_width(width), m_height(height), m_margin(margin) {}

std::vector<Point> LinePointProvider::getPoints() {
    std::vector<Point> points;
    points.reserve(m_count);

    float y = static_cast<float>(m_height) / 2.0f;
    float startX = static_cast<float>(m_margin);
    float endX = static_cast<float>(m_width - m_margin);

    float dx = (endX - startX) / static_cast<float>(m_count - 1);

    for (int i = 0; i < m_count; i++) {
        float x = startX + dx * i;
        points.push_back({x, y});
    }

    return points;
}
