#include "AndrewAlgorithm.h"


// Complete implementation not finished
AndrewAlgorithm::AndrewAlgorithm(const std::vector<Point>& points) {
    reset(points);
}

void AndrewAlgorithm::reset(const std::vector<Point>& points) {
    m_points = points;
    m_hull.clear();
    m_index = 0;
    m_finished = false;

    std::sort(m_points.begin(), m_points.end(), [](const Point& a, const Point& b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });
}

//TODO: Implement correct algorithm
bool AndrewAlgorithm::step() {
    if (m_finished) return false;

    if (m_index < m_points.size()) {
        m_hull.push_back(m_points[m_index++]);
        return true;
    }

    m_finished = true;
    return false;
}

std::vector<Point> AndrewAlgorithm::getCurrentHull() {
    return m_hull;
}

std::vector<Point> AndrewAlgorithm::runCompleteAlgorithm(const std::vector<Point>& points) {
    reset(points);
    while (step()) {}
    return m_hull;
}
