#include "algorithms/QuickhullAlgorithm.h"
#include <algorithm>
#include <cmath>

QuickHullAlgorithm::QuickHullAlgorithm(const std::vector<Point>& points) {
    reset(points);
}

void QuickHullAlgorithm::reset(const std::vector<Point>& points) {
    m_points = points;
    m_hull.clear();
    m_tasks.clear();
    m_currentLevelTasks.clear();
    m_currentFarthestPoints.clear();
    m_activePoints.clear();
    m_pendingTasks.clear();
    m_finished = false;
    m_phase = Phase::PREVIEW;
    m_inPreviewPhase = false;

    if (m_points.size() < 3) {
        m_hull = m_points;
        m_finished = true;
        return;
    }

    initialize();
    updateActivePoints();
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
    auto minIt = std::min_element(m_points.begin(), m_points.end(),
        [](const Point& a, const Point& b) { return (a.x < b.x) || (a.x == b.x && a.y < b.y); });
    auto maxIt = std::max_element(m_points.begin(), m_points.end(),
        [](const Point& a, const Point& b) { return (a.x < b.x) || (a.x == b.x && a.y < b.y); });

    Point leftmost = *minIt;
    Point rightmost = *maxIt;

    m_hull.push_back(leftmost);
    m_hull.push_back(rightmost);

    std::vector<Point> upperSet = getPointsOnSide(leftmost, rightmost, m_points, true);
    std::vector<Point> lowerSet = getPointsOnSide(leftmost, rightmost, m_points, false);

    if (!upperSet.empty()) {
        m_tasks.push_back({leftmost, rightmost, upperSet, 1});
    }
    if (!lowerSet.empty()) {
        m_tasks.push_back({rightmost, leftmost, lowerSet, static_cast<int>(m_hull.size())});
    }

    if (m_tasks.empty()) {
        m_finished = true;
    }
}

void QuickHullAlgorithm::updateActivePoints() {
    m_activePoints.clear();

    for (const auto& p : m_hull) {
        m_activePoints.insert(p);
    }

    for (const auto& task : m_tasks) {
        for (const auto& p : task.set) {
            m_activePoints.insert(p);
        }
    }

    for (const auto& task : m_currentLevelTasks) {
        for (const auto& p : task.set) {
            m_activePoints.insert(p);
        }
    }
}

void QuickHullAlgorithm::computePreview() {
    if (m_tasks.empty()) {
        m_finished = true;
        m_currentLevelTasks.clear();
        m_currentFarthestPoints.clear();
        m_inPreviewPhase = false;
        return;
    }

    // Store current level tasks for visualization
    size_t currentLevelSize = m_tasks.size();
    m_currentLevelTasks.clear();
    m_pendingTasks.clear();

    for (size_t i = 0; i < currentLevelSize; i++) {
        m_currentLevelTasks.push_back(m_tasks[i]);
        m_pendingTasks.push_back(m_tasks[i]);
    }

    m_currentFarthestPoints.clear();

    // Find farthest points for each task (preview only, don't modify hull)
    for (const auto& task : m_currentLevelTasks) {
        if (task.set.empty()) {
            continue;
        }

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

        if (found) {
            m_currentFarthestPoints.push_back(farthest);
        }
    }

    m_inPreviewPhase = true;
}

void QuickHullAlgorithm::commitPreview() {
    if (m_pendingTasks.empty()) {
        m_inPreviewPhase = false;
        return;
    }

    std::deque<Task> nextLevelTasks;

    // Now actually process and modify the hull
    for (size_t i = 0; i < m_pendingTasks.size(); i++) {
        Task task = m_tasks.front();
        m_tasks.pop_front();

        if (task.set.empty()) {
            continue;
        }

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
            continue;
        }

        // Actually insert into hull
        m_hull.insert(m_hull.begin() + task.insertPos, farthest);

        // Update insertion positions
        for (auto& t : m_tasks) {
            if (t.insertPos >= task.insertPos) {
                t.insertPos++;
            }
        }
        for (auto& t : nextLevelTasks) {
            if (t.insertPos >= task.insertPos) {
                t.insertPos++;
            }
        }

        // Create new tasks
        std::vector<Point> leftSet = getPointsOnSide(task.a, farthest, task.set, true);
        std::vector<Point> rightSet = getPointsOnSide(farthest, task.b, task.set, true);

        if (!leftSet.empty()) {
            nextLevelTasks.push_back({task.a, farthest, leftSet, task.insertPos});
        }
        if (!rightSet.empty()) {
            nextLevelTasks.push_back({farthest, task.b, rightSet, task.insertPos + 1});
        }
    }

    for (const auto& task : nextLevelTasks) {
        m_tasks.push_back(task);
    }

    m_pendingTasks.clear();
    m_currentLevelTasks.clear();
    m_currentFarthestPoints.clear();
    m_inPreviewPhase = false;
    updateActivePoints();
}

bool QuickHullAlgorithm::step() {
    if (m_finished) {
        return false;
    }

    if (m_phase == Phase::PREVIEW) {
        computePreview();
        m_phase = Phase::COMMIT;
        return true;
    } else { // COMMIT
        commitPreview();
        m_phase = Phase::PREVIEW;
        updateActivePoints();
        return !m_finished;
    }
}

std::vector<std::pair<Point, Point>> QuickHullAlgorithm::getActiveSegments() const {
    std::vector<std::pair<Point, Point>> segments;
    for (const auto& task : m_currentLevelTasks) {
        segments.push_back({task.a, task.b});
    }
    return segments;
}

std::vector<Point> QuickHullAlgorithm::getCandidatePoints() const {
    std::vector<Point> candidates;
    for (const auto& task : m_currentLevelTasks) {
        for (const auto& p : task.set) {
            candidates.push_back(p);
        }
    }
    return candidates;
}

std::vector<Point> QuickHullAlgorithm::getFarthestPoints() const {
    return m_currentFarthestPoints;
}

std::set<Point> QuickHullAlgorithm::getActivePoints() const {
    return m_activePoints;
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