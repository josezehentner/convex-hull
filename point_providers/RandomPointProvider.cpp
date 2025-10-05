#include "RandomPointProvider.h"
#include <iostream>

RandomPointProvider::RandomPointProvider(int count, int width, int height, int margin)
    : m_count(count), m_width(width), m_height(height), m_margin(margin) {}

std::vector<Point> RandomPointProvider::getPoints() {
    std::vector<Point> points;
    points.reserve(m_count);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution distX(m_margin, m_width - m_margin);
    std::uniform_int_distribution distY(m_margin, m_height - m_margin);

    for (int i = 0; i < m_count; i++) {
        int x = distX(rng);
        int y = distY(rng);
        points.push_back({static_cast<float>(x), static_cast<float>(y)});
    }
    return points;
}