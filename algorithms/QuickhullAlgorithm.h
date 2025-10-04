
#ifndef QUICKHULLALGORITHM_H
#define QUICKHULLALGORITHM_H

#include "IAlgorithm.h"
#include <vector>
#include <deque>

class QuickHullAlgorithm : public IAlgorithm {
public:
    explicit QuickHullAlgorithm(const std::vector<Point>& points);

    bool step() override;
    std::vector<Point> getCurrentHull() override;
    void reset(const std::vector<Point>& points) override;
    bool isFinished() const override;
    std::vector<Point> runCompleteAlgorithm(const std::vector<Point>& points) override;

    // Additional methods for visualization
    Point getCurrentSegmentStart() const { return m_currentSegmentStart; }
    Point getCurrentSegmentEnd() const { return m_currentSegmentEnd; }
    std::vector<Point> getCurrentCandidates() const { return m_currentCandidates; }
    Point getCurrentFarthest() const { return m_currentFarthest; }
    bool hasCurrentSegment() const { return m_hasCurrentSegment; }

private:
    struct Task {
        Point a;
        Point b;
        std::vector<Point> set;
        int insertPos;
    };

    std::vector<Point> m_points;
    std::vector<Point> m_hull;
    std::deque<Task> m_tasks;
    bool m_finished;

    // Visualization state
    Point m_currentSegmentStart;
    Point m_currentSegmentEnd;
    std::vector<Point> m_currentCandidates;
    Point m_currentFarthest;
    bool m_hasCurrentSegment;

    static float cross(const Point& o, const Point& a, const Point& b);
    static float distanceToLine(const Point& a, const Point& b, const Point& p);
    void initialize();
    std::vector<Point> getPointsOnSide(const Point& a, const Point& b, const std::vector<Point>& points, bool left);
};

#endif //QUICKHULLALGORITHM_H