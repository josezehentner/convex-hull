#include "SquarePointProvider.h"
#include <algorithm>

SquarePointProvider::SquarePointProvider(int count, int width, int height, int margin)
    : m_count(count), m_width(width), m_height(height), m_margin(margin) {}

std::vector<Point> SquarePointProvider::getPoints() {
    std::vector<Point> points;
    points.reserve(m_count);

    float left = static_cast<float>(m_margin);
    float right = static_cast<float>(m_width - m_margin);
    float top = static_cast<float>(m_margin);
    float bottom = static_cast<float>(m_height - m_margin);

    float perimeter = 2.0f * ((right - left) + (bottom - top));
    float step = perimeter / m_count;

    float accumulated = 0.0f;
    for (int i = 0; i < m_count; i++) {
        float d = accumulated;
        Point p;

        if (d < (right - left)) {
            // top edge
            p = {left + d, top};
        } else if (d < (right - left) + (bottom - top)) {
            // right edge
            d -= (right - left);
            p = {right, top + d};
        } else if (d < 2 * (right - left) + (bottom - top)) {
            // bottom edge
            d -= (right - left + bottom - top);
            p = {right - d, bottom};
        } else {
            // left edge
            d -= 2 * (right - left) + (bottom - top);
            p = {left, bottom - d};
        }

        points.push_back(p);
        accumulated += step;
    }

    return points;
}
