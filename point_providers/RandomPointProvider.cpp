#include "RandomPointProvider.h"

RandomPointProvider::RandomPointProvider(int count, int width, int height, int margin)
    : m_count(count), m_width(width), m_height(height), m_margin(margin) {}

std::vector<Point> RandomPointProvider::getPoints() {
    std::vector<Point> points;
    points.reserve(m_count);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distX(m_margin, m_width - m_margin);
    std::uniform_real_distribution<float> distY(m_margin, m_height - m_margin);

    for (int i = 0; i < m_count; i++) {
        points.push_back({distX(rng), distY(rng)});
    }

    return points;
}