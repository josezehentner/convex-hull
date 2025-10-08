#include "algorithms/QuickhullAlgorithm.h"
#include <algorithm>
#include <cmath>

constexpr double EPS = 1e-9; // Small epsilon to handle floating-point precision errors

// Constructor: initialize the algorithm with a set of points
QuickHullAlgorithm::QuickHullAlgorithm(const std::vector<Point>& points) {
    reset(points);
}

// Reset the algorithm's internal state for a new convex hull computation
void QuickHullAlgorithm::reset(const std::vector<Point>& points) {
    // Copy input points
    m_points = points;

    // Clear all internal data structures
    m_hull.clear();
    m_tasks.clear();
    m_currentLevelTasks.clear();
    m_currentFarthestPoints.clear();
    m_activePoints.clear();
    m_pendingTasks.clear();

    // Reset flags
    m_finished = false;
    m_phase = Phase::PREVIEW;
    m_inPreviewPhase = false;

    // If there are fewer than 3 points, the hull is just the points themselves
    if (m_points.size() < 3) {
        m_hull = m_points;
        m_finished = true;
        return;
    }

    // Start main setup
    initialize();
    updateActivePoints();
}

// Compute 2D cross product (OA × OB). Positive if B is to the left of OA.
float QuickHullAlgorithm::cross(const Point& o, const Point& a, const Point& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// Compute perpendicular distance from point p to line segment AB using cross product magnitude
float QuickHullAlgorithm::distanceToLine(const Point& a, const Point& b, const Point& p) {
    return std::fabs(cross(a, b, p));
}

// Collect points that lie on one specific side (left or right) of a line AB
std::vector<Point> QuickHullAlgorithm::getPointsOnSide(const Point& a, const Point& b,
                                                        const std::vector<Point>& points, bool left) {
    std::vector<Point> result;
    for (const auto& p : points) {
        float c = cross(a, b, p);
        // Positive cross -> left side, negative -> right side
        if (left && c > EPS) {
            result.push_back(p);
        } else if (!left && c < -EPS) {
            result.push_back(p);
        }
    }
    return result;
}

// Initialization: find the two extreme points (leftmost and rightmost) and start recursive hull tasks
void QuickHullAlgorithm::initialize() {
    // Find the leftmost point (minimum x, then minimum y)
    auto minIt = std::min_element(m_points.begin(), m_points.end(),
        [](const Point& a, const Point& b) { return (a.x < b.x) || (a.x == b.x && a.y < b.y); });
    // Find the rightmost point (maximum x, then maximum y)
    auto maxIt = std::max_element(m_points.begin(), m_points.end(),
        [](const Point& a, const Point& b) { return (a.x < b.x) || (a.x == b.x && a.y < b.y); });

    Point leftmost = *minIt;
    Point rightmost = *maxIt;

    // Start the hull with the two extreme points
    m_hull.push_back(leftmost);
    m_hull.push_back(rightmost);

    // Split the remaining points into those above and below the line
    std::vector<Point> upperSet = getPointsOnSide(leftmost, rightmost, m_points, true);
    std::vector<Point> lowerSet = getPointsOnSide(leftmost, rightmost, m_points, false);

    // Each subset becomes a recursive task (upper and lower hull)
    if (!upperSet.empty()) {
        m_tasks.push_back({leftmost, rightmost, upperSet, 1});
    }
    if (!lowerSet.empty()) {
        m_tasks.push_back({rightmost, leftmost, lowerSet, static_cast<int>(m_hull.size())});
    }

    // If no subsets exist, the hull is just the two points
    if (m_tasks.empty()) {
        m_finished = true;
    }
}

// Update the collection of all currently active points (used for visualization/debug info)
void QuickHullAlgorithm::updateActivePoints() {
    m_activePoints.clear();

    // Include all points currently on the hull
    for (const auto& p : m_hull) {
        m_activePoints.insert(p);
    }

    // Include points currently being processed in queued tasks
    for (const auto& task : m_tasks) {
        for (const auto& p : task.set) {
            m_activePoints.insert(p);
        }
    }

    // Include points in the current preview level
    for (const auto& task : m_currentLevelTasks) {
        for (const auto& p : task.set) {
            m_activePoints.insert(p);
        }
    }
}

// Compute a "preview" step – find farthest points for each active task (for stepwise visualization)
void QuickHullAlgorithm::computePreview() {
    if (m_tasks.empty()) {
        // No more tasks -> algorithm is done
        m_finished = true;
        m_currentLevelTasks.clear();
        m_currentFarthestPoints.clear();
        m_inPreviewPhase = false;
        return;
    }

    // Copy current tasks into preview containers
    const size_t currentLevelSize = m_tasks.size();
    m_currentLevelTasks.clear();
    m_pendingTasks.clear();
    for (size_t i = 0; i < currentLevelSize; ++i) {
        m_currentLevelTasks.push_back(m_tasks[i]);
        m_pendingTasks.push_back(m_tasks[i]);
    }

    m_currentFarthestPoints.clear();

    // For each active task, find the farthest point from the segment AB
    for (const auto& task : m_currentLevelTasks) {
        float maxDist = 0.0f;
        bool found = false;
        Point farthest;

        // Iterate through all points in this subset
        for (const auto& p : task.set) {
            float c = cross(task.a, task.b, p);
            if (c > EPS) { // Point is on the left side
                float d = distanceToLine(task.a, task.b, p);
                if (d > maxDist) {
                    maxDist = d;
                    farthest = p;
                    found = true;
                }
            }
        }

        // Save farthest point for visualization
        if (found) {
            m_currentFarthestPoints.push_back(farthest);
        }
    }

    m_inPreviewPhase = true;
}

// Commit the results from the preview step (actually modify the hull and update tasks)
void QuickHullAlgorithm::commitPreview() {
    if (m_pendingTasks.empty()) {
        // Nothing to process
        m_inPreviewPhase = false;
        return;
    }

    std::deque<Task> nextLevelTasks; // Tasks for the next recursion level

    const size_t toProcess = m_pendingTasks.size();
    for (size_t i = 0; i < toProcess; ++i) {
        // Process one active task
        Task task = m_tasks.front();
        m_tasks.pop_front();

        // Find the farthest point from segment AB (strictly on left side)
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

        // If no points left of AB, nothing more to process on this branch
        if (idx < 0) {
            continue;
        }

        const Point farthest = task.set[idx]; // Farthest point from AB

        // Insert the farthest point into the hull at the correct position
        m_hull.insert(m_hull.begin() + task.insertPos, farthest);

        // Adjust insertion indices for all other tasks
        for (auto& t : m_tasks) {
            if (t.insertPos >= task.insertPos) t.insertPos++;
        }
        for (auto& t : nextLevelTasks) {
            if (t.insertPos >= task.insertPos) t.insertPos++;
        }

        // Split the remaining points into two subsets:
        //   s1 -> points to the left of (A, farthest)
        //   s2 -> points to the left of (farthest, B)
        std::vector<Point> s1;
        std::vector<Point> s2;
        s1.reserve(task.set.size());
        s2.reserve(task.set.size());

        for (const auto& q : task.set) {
            // Skip duplicates and endpoints
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

        // Schedule new tasks for both subsets
        if (!s1.empty()) {
            nextLevelTasks.push_back({task.a, farthest, std::move(s1), task.insertPos});
        }
        if (!s2.empty()) {
            nextLevelTasks.push_back({farthest, task.b, std::move(s2), task.insertPos + 1});
        }
    }

    // Append all generated next-level tasks
    for (const auto& task : nextLevelTasks) {
        m_tasks.push_back(task);
    }

    // Clear preview-related data
    m_pendingTasks.clear();
    m_currentLevelTasks.clear();
    m_currentFarthestPoints.clear();
    m_inPreviewPhase = false;

    // If no more tasks exist, hull is fully computed
    if (m_tasks.empty()) {
        m_finished = true;
    }

    updateActivePoints();
}

// Perform one step of the interactive algorithm (toggle between preview and commit)
bool QuickHullAlgorithm::step() {
    if (m_finished) {
        return false;
    }

    if (m_phase == Phase::PREVIEW) {
        // Preview step: find next farthest points without modifying hull
        computePreview();
        m_phase = Phase::COMMIT;
        return true;
    } else { // Commit phase
        // Actually add the farthest points and create new tasks
        commitPreview();
        m_phase = Phase::PREVIEW;
        updateActivePoints();
        return !m_finished;
    }
}

// Return all currently active segment pairs (edges under consideration)
std::vector<std::pair<Point, Point>> QuickHullAlgorithm::getActiveSegments() const {
    std::vector<std::pair<Point, Point>> segments;
    for (const auto& task : m_currentLevelTasks) {
        segments.push_back({task.a, task.b});
    }
    return segments;
}

// Return all candidate points currently being evaluated
std::vector<Point> QuickHullAlgorithm::getCandidatePoints() const {
    std::vector<Point> candidates;
    for (const auto& task : m_currentLevelTasks) {
        for (const auto& p : task.set) {
            candidates.push_back(p);
        }
    }
    return candidates;
}

// Return farthest points found in the current preview
std::vector<Point> QuickHullAlgorithm::getFarthestPoints() const {
    return m_currentFarthestPoints;
}

// Return all points considered "active" in the current state
std::set<Point> QuickHullAlgorithm::getActivePoints() const {
    return m_activePoints;
}

// Check if the convex hull computation is complete
bool QuickHullAlgorithm::isFinished() const {
    return m_finished;
}

// Return the current state of the hull (partial or complete)
std::vector<Point> QuickHullAlgorithm::getCurrentHull() {
    return m_hull;
}

// Compute the full convex hull non-interactively (direct recursive QuickHull)
std::vector<Point> QuickHullAlgorithm::runCompleteAlgorithm(const std::vector<Point>& points) {
    if (points.size() < 3) return points;

    auto lessXY = [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    };

    const auto minIt = std::min_element(points.begin(), points.end(), lessXY);
    const auto maxIt = std::max_element(points.begin(), points.end(), lessXY);

    const Point leftmost  = *minIt;
    const Point rightmost = *maxIt;

    const std::vector<Point> upperSet = getPointsOnSide(leftmost, rightmost, points, true);
    const std::vector<Point> lowerSet = getPointsOnSide(leftmost, rightmost, points, false);

    std::vector<Point> hull;
    hull.reserve(points.size());
    hull.push_back(leftmost);
    quickHull(upperSet, leftmost, rightmost, hull);
    hull.push_back(rightmost);
    quickHull(lowerSet, rightmost, leftmost, hull);

    return hull;
}


// Recursive function: process subset of points to find and add hull points
void QuickHullAlgorithm::quickHull(const std::vector<Point>& setAB,
                                   const Point& a, const Point& b,
                                   std::vector<Point>& hull) {
    if (setAB.empty()) return;

    // Find farthest exactly like before, scan the original setAB
    int   idx = -1;
    float maxDist = 0.0f;
    for (int i = 0; i < static_cast<int>(setAB.size()); ++i) {
        const float c = cross(a, b, setAB[i]);
        if (c > EPS) {
            const float d = distanceToLine(a, b, setAB[i]);
            if (d > maxDist) {
                maxDist = d;
                idx = i;
            }
        }
    }
    if (idx < 0) return;

    const Point p = setAB[idx];

    // Partition using the shared helper on the same base set
    std::vector<Point> s1 = getPointsOnSide(a, p, setAB, true);
    std::vector<Point> s2 = getPointsOnSide(p, b, setAB, true);

    // Keep the explicit exclusions, matches the original loop behavior
    auto dropEndpoints = [&](std::vector<Point>& s) {
        s.erase(std::remove_if(s.begin(), s.end(), [&](const Point& q) {
            return (q.x == p.x && q.y == p.y) ||
                   (q.x == a.x && q.y == a.y) ||
                   (q.x == b.x && q.y == b.y);
        }), s.end());
    };
    dropEndpoints(s1);
    dropEndpoints(s2);

    quickHull(s1, a, p, hull);
    hull.push_back(p);
    quickHull(s2, p, b, hull);
}
