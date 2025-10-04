#include "AndrewAlgorithm.h"
#include <iostream>

AndrewAlgorithm::AndrewAlgorithm(const std::vector<Point>& points) {
    AndrewAlgorithm::reset(points);
}

void AndrewAlgorithm::reset(const std::vector<Point>& points) {
    m_points = points;
    m_hull.clear();
    m_upper.clear();
    m_lower.clear();
    m_index = 0;
    m_finished = false;
    m_phase = Phase::UPPER;
    m_hasCurrentPoint = false;

    std::sort(m_points.begin(), m_points.end(), [](const Point& a, const Point& b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });
}


float AndrewAlgorithm::crossProduct(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

void AndrewAlgorithm::addPointToChain(std::vector<Point>& chain, const Point& p) {
    while (chain.size() >= 2 && crossProduct(chain[chain.size()-2], chain.back(), p) <= 0) {
        chain.pop_back();
    }
    chain.push_back(p);
}

bool AndrewAlgorithm::step() {
    if (m_finished) {
        m_hasCurrentPoint = false;
        return false;
    }

    if (m_phase == Phase::UPPER) {
        if (m_index < m_points.size()) {
            m_currentPoint = m_points[m_index];
            m_hasCurrentPoint = true;

            addPointToChain(m_upper, m_points[m_index++]);
            return true;
        }
        m_phase = Phase::LOWER;
        m_index = m_points.size() - 1;
        m_hasCurrentPoint = false;
        return true;
    }

    if (m_phase == Phase::LOWER) {
        if (m_index < m_points.size()) {
            m_currentPoint = m_points[m_index];
            m_hasCurrentPoint = true;

            addPointToChain(m_lower, m_points[m_index--]);
            return true;
        }
        m_hull = m_upper;
        for (size_t i = 1; i + 1 < m_lower.size(); i++) {
            m_hull.push_back(m_lower[i]);
        }
        m_phase = Phase::DONE;
        m_finished = true;
        m_hasCurrentPoint = false;
        return false;
    }

    return false;
}

bool AndrewAlgorithm::isFinished() const {
    return m_finished;
}

std::vector<Point> AndrewAlgorithm::getCurrentHull() {
    if (m_phase == Phase::UPPER) {
        return m_upper;
    }
    if (m_phase == Phase::LOWER) {
        std::vector<Point> current = m_upper;
        for (size_t i = 0; i < m_lower.size(); i++) {
            current.push_back(m_lower[i]);
        }
        return current;
    }
    return m_hull;
}

std::vector<Point> AndrewAlgorithm::runCompleteAlgorithm(const std::vector<Point>& points) {
    reset(points);
    while (step()) {}
    return m_hull;
}