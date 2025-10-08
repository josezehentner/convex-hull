#include "algorithms/QuickhullAlgorithm.h"
#include <algorithm>
#include <cmath>

constexpr float EPS = 1e-9;

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
    return std::fabs(cross(a, b, p));
}

std::vector<Point> QuickHullAlgorithm::getPointsOnSide(const Point& a, const Point& b,
                                                        const std::vector<Point>& points, bool left) {
    std::vector<Point> result;
    for (const auto& p : points) {
        float c = cross(a, b, p);
        if (left && c > EPS) {
            result.push_back(p);
        } else if (!left && c < -EPS) {
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
    const size_t currentLevelSize = m_tasks.size();
    m_currentLevelTasks.clear();
    m_pendingTasks.clear();
    for (size_t i = 0; i < currentLevelSize; ++i) {
        m_currentLevelTasks.push_back(m_tasks[i]);
        m_pendingTasks.push_back(m_tasks[i]);
    }

    m_currentFarthestPoints.clear();

    // Find farthest points for each task (preview only, don't modify hull)
    for (const auto& task : m_currentLevelTasks) {
        float maxDist = 0.0f;
        bool found = false;
        Point farthest;

        for (const auto& p : task.set) {
            float c = cross(task.a, task.b, p);
            if (c > EPS) {
                float d = distanceToLine(task.a, task.b, p);
                if (d > maxDist) {
                    maxDist = d;
                    farthest = p;
                    found = true;
                }
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
    const size_t toProcess = m_pendingTasks.size();
    for (size_t i = 0; i < toProcess; ++i) {
        Task task = m_tasks.front();
        m_tasks.pop_front();

        // Farthest strictly on the left of AB
        int idx = -1;
        float maxDist = 0.0f;
        for (int j = 0; j < static_cast<int>(task.set.size()); ++j) {
            float c = cross(task.a, task.b, task.set[j]);
            if (c > EPS) {
                float d = distanceToLine(task.a, task.b, task.set[j]);
                if (d > maxDist) {
                    maxDist = d;
                    idx = j;
                }
            }
        }
        if (idx < 0) {
            // Nothing left of AB, this branch is done
            continue;
        }

        const Point farthest = task.set[idx];

        // Actually insert into hull
        m_hull.insert(m_hull.begin() + task.insertPos, farthest);

        // Update insertion positions
        for (auto& t : m_tasks) {
            if (t.insertPos >= task.insertPos) t.insertPos++;
        }
        for (auto& t : nextLevelTasks) {
            if (t.insertPos >= task.insertPos) t.insertPos++;
        }

        std::vector<Point> s1;
        std::vector<Point> s2;
        s1.reserve(task.set.size());
        s2.reserve(task.set.size());

        for (const auto& q : task.set) {
            if ((q.x == farthest.x && q.y == farthest.y) ||
                (q.x == task.a.x && q.y == task.a.y) ||
                (q.x == task.b.x && q.y == task.b.y)) {
                continue;
            }
            if (cross(task.a, farthest, q) > EPS) {
                s1.push_back(q);
            } else if (cross(farthest, task.b, q) > EPS) {
                s2.push_back(q);
            }
        }

        if (!s1.empty()) {
            nextLevelTasks.push_back({task.a, farthest, std::move(s1), task.insertPos});
        }
        if (!s2.empty()) {
            nextLevelTasks.push_back({farthest, task.b, std::move(s2), task.insertPos + 1});
        }
    }

    for (const auto& task : nextLevelTasks) {
        m_tasks.push_back(task);
    }

    m_pendingTasks.clear();
    m_currentLevelTasks.clear();
    m_currentFarthestPoints.clear();
    m_inPreviewPhase = false;

    if (m_tasks.empty()) {
        m_finished = true;
    }

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
    if (points.size() < 3) return points;

    auto lessXY = [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    };

    auto minIt = std::min_element(points.begin(), points.end(), lessXY);
    auto maxIt = std::max_element(points.begin(), points.end(), lessXY);

    const Point leftmost = *minIt;
    const Point rightmost = *maxIt;

    std::vector<Point> upperSet;
    std::vector<Point> lowerSet;
    upperSet.reserve(points.size());
    lowerSet.reserve(points.size());

    for (const auto& p : points) {
        float c = cross(leftmost, rightmost, p);
        if (c > EPS) upperSet.push_back(p);
        else if (c < -EPS) lowerSet.push_back(p);
    }

    std::vector<Point> hull;
    hull.reserve(points.size());

    hull.push_back(leftmost);
    quickHull(upperSet, leftmost, rightmost, hull);
    hull.push_back(rightmost);
    quickHull(lowerSet, rightmost, leftmost, hull);

    return hull;
}

void QuickHullAlgorithm::quickHull(const std::vector<Point>& setAB,
                                   const Point& a, const Point& b,
                                   std::vector<Point>& hull) {
    if (setAB.empty()) {
        return;
    }

    float maxDist = 0.0f;
    int idx = -1;
    for (int i = 0; i < static_cast<int>(setAB.size()); ++i) {
        float c = cross(a, b, setAB[i]);
        if (c > EPS) { // Strictly left of AB
            float d = distanceToLine(a, b, setAB[i]);
            if (d > maxDist) {
                maxDist = d;
                idx = i;
            }
        }
    }

    // If nothing strictly left or only numerically collinear, stop
    if (idx < 0) return;

    const Point p = setAB[idx];

    std::vector<Point> s1;
    std::vector<Point> s2;
    s1.reserve(setAB.size());
    s2.reserve(setAB.size());

    for (int i = 0; i < static_cast<int>(setAB.size()); ++i) {
        const Point& q = setAB[i];
        if ((q.x == p.x && q.y == p.y) || (q.x == a.x && q.y == a.y) || (q.x == b.x && q.y == b.y))
            continue;

        if (cross(a, p, q) > EPS) {
            s1.push_back(q);
        } else if (cross(p, b, q) > EPS) {
            s2.push_back(q);
        }
    }

    quickHull(s1, a, p, hull);
    hull.push_back(p);
    quickHull(s2, p, b, hull);
}