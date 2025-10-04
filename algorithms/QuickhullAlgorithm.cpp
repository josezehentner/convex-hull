#include "QuickHullAlgorithm.h"
#include <algorithm>
#include <cmath>

QuickHullAlgorithm::QuickHullAlgorithm(const std::vector<Point>& points) {
    reset(points);
}

void QuickHullAlgorithm::reset(const std::vector<Point>& points) {
    m_points = points;
    m_hull.clear();
    m_tasks.clear();
    m_finished = false;

    if (m_points.size() < 3) {
        m_hull = m_points;
        m_finished = true;
        return;
    }

    initialize();
}

float QuickHullAlgorithm::cross(const Point& o, const Point& a, const Point& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

float QuickHullAlgorithm::distanceToLine(const Point& a, const Point& b, const Point& p) {
    return std::abs(cross(a, b, p));
}

std::vector<Point> QuickHullAlgorithm::getPointsOnSide(const Point& a, const Point& b,
                                                        const std::vector<Point>& points, bool left) {
    std::vector<Point> result;
    for (const auto& p : points) {
        float c = cross(a, b, p);
        if (left && c > 0) {
            result.push_back(p);
        } else if (!left && c < 0) {
            result.push_back(p);
        }
    }
    return result;
}

void QuickHullAlgorithm::initialize() {
    // Find leftmost and rightmost points
    auto minIt = std::min_element(m_points.begin(), m_points.end(),
        [](const Point& a, const Point& b) { return a.x < b.x; });
    auto maxIt = std::max_element(m_points.begin(), m_points.end(),
        [](const Point& a, const Point& b) { return a.x < b.x; });

    Point leftmost = *minIt;
    Point rightmost = *maxIt;

    m_hull.push_back(leftmost);
    m_hull.push_back(rightmost);

    // Split points into upper and lower sets
    std::vector<Point> upperSet = getPointsOnSide(leftmost, rightmost, m_points, true);
    std::vector<Point> lowerSet = getPointsOnSide(leftmost, rightmost, m_points, false);

    // Add tasks for upper and lower hulls
    if (!upperSet.empty()) {
        m_tasks.push_back({leftmost, rightmost, upperSet, 1});
    }
    if (!lowerSet.empty()) {
        m_tasks.push_back({rightmost, leftmost, lowerSet, (m_hull.size())});
    }

    if (m_tasks.empty()) {
        m_finished = true;
    }
}

bool QuickHullAlgorithm::step() {
    if (m_finished) return false;

    if (m_tasks.empty()) {
        m_finished = true;
        return false;
    }

    // Process one task
    Task task = m_tasks.front();
    m_tasks.pop_front();

    if (task.set.empty()) {
        return true;
    }

    // Find farthest point from line a-b
    float maxDist = 0;
    Point farthest;
    bool found = false;

    for (const auto& p : task.set) {
        float dist = distanceToLine(task.a, task.b, p);
        if (dist > maxDist) {
            maxDist = dist;
            farthest = p;
            found = true;
        }
    }

    if (!found) {
        return true;
    }

    // Insert farthest point into hull
    m_hull.insert(m_hull.begin() + task.insertPos, farthest);

    // Update insertion positions for remaining tasks
    for (auto& t : m_tasks) {
        if (t.insertPos >= task.insertPos) {
            t.insertPos++;
        }
    }

    // Find points outside triangles a-farthest and farthest-b
    std::vector<Point> leftSet = getPointsOnSide(task.a, farthest, task.set, true);
    std::vector<Point> rightSet = getPointsOnSide(farthest, task.b, task.set, true);

    // Add new tasks (process in reverse order for correct visualization)
    if (!rightSet.empty()) {
        m_tasks.push_front({farthest, task.b, rightSet, task.insertPos + 1});
    }
    if (!leftSet.empty()) {
        m_tasks.push_front({task.a, farthest, leftSet, task.insertPos});
    }

    return true;
}

bool QuickHullAlgorithm::isFinished() const {
    return m_finished;
}

std::vector<Point> QuickHullAlgorithm::getCurrentHull() {
    return m_hull;
}

std::vector<Point> QuickHullAlgorithm::runCompleteAlgorithm(const std::vector<Point>& points) {
    reset(points);
    while (step()) {}
    return m_hull;
}