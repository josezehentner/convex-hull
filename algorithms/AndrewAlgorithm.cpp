#include "AndrewAlgorithm.h"


// Complete implementation not finished
AndrewAlgorithm::AndrewAlgorithm(const std::vector<Point>& points) {
    reset(points);
}

void AndrewAlgorithm::reset(const std::vector<Point>& points) {
    m_points = points;
    m_hull.clear();
    m_upper.clear();
    m_lower.clear();
    m_index = 0;
    m_finished = false;
    m_phase = Phase::UPPER;

    std::sort(m_points.begin(), m_points.end(), [](const Point& a, const Point& b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });
}


// Cross product (orientation test)
float AndrewAlgorithm::cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Add point to chain with convexity check
void AndrewAlgorithm::addPointToChain(std::vector<Point>& chain, const Point& p) {
    while (chain.size() >= 2 && cross(chain[chain.size()-2], chain.back(), p) <= 0) {
        chain.pop_back();
    }
    chain.push_back(p);
}

// If the step is
bool AndrewAlgorithm::step() {
    if (m_finished) return false;

    if (m_phase == Phase::UPPER) {
        if (m_index < m_points.size()) {
            addPointToChain(m_upper, m_points[m_index++]);
            return true;
        }
        // switch to LOWER phase
        m_phase = Phase::LOWER;
        m_index = m_points.size() - 1;
        return true; // switch to lower convex hull
    }

    if (m_phase == Phase::LOWER) {
        if (m_index < m_points.size()) {
            addPointToChain(m_lower, m_points[m_index--]);
            return true;
        }
        // Merge results into m_hull
        m_hull = m_upper;
        // append lower hull, skipping first and last to avoid duplicates
        for (size_t i = 1; i + 1 < m_lower.size(); i++) {
            m_hull.push_back(m_lower[i]);
        }
        m_phase = Phase::DONE;
        m_finished = true;
        return false;
    }

    return false;
}

bool AndrewAlgorithm::isFinished() const
{
    return m_finished;
}

// Get current hull (for visualization)
std::vector<Point> AndrewAlgorithm::getCurrentHull() {
    if (m_phase == Phase::UPPER) {
        return m_upper;
    } else if (m_phase == Phase::LOWER) {
        std::vector<Point> current = m_upper;
        // append partial lower
        for (size_t i = 0; i < m_lower.size(); i++) {
            current.push_back(m_lower[i]);
        }
        return current;
    } else {
        return m_hull; // final
    }
}

std::vector<Point> AndrewAlgorithm::runCompleteAlgorithm(const std::vector<Point>& points) {
    reset(points);
    while (step()) {}
    return m_hull;
}
