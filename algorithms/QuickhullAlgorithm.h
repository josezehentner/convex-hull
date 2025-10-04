
#ifndef QUICKHULLALGORITHM_H
#define QUICKHULLALGORITHM_H

#include "IAlgorithm.h"
#include <vector>
#include <deque>
#include <set>

class QuickHullAlgorithm : public IAlgorithm {
public:
    explicit QuickHullAlgorithm(const std::vector<Point>& points);

    bool step() override;
    std::vector<Point> getCurrentHull() override;
    void reset(const std::vector<Point>& points) override;
    bool isFinished() const override;
    std::vector<Point> runCompleteAlgorithm(const std::vector<Point>& points) override;

    // Visualization methods
    std::vector<std::pair<Point, Point>> getActiveSegments() const;
    std::vector<Point> getCandidatePoints() const;
    std::vector<Point> getFarthestPoints() const;
    std::set<Point> getActivePoints() const;
    bool hasActiveSegments() const { return !m_currentLevelTasks.empty(); }
    bool isInPreviewPhase() const { return m_inPreviewPhase; }

private:
    enum class Phase { PREVIEW, COMMIT };

    struct Task {
        Point a;
        Point b;
        std::vector<Point> set;
        int insertPos;
    };

    std::vector<Point> m_points;
    std::vector<Point> m_hull;
    std::deque<Task> m_tasks;
    std::deque<Task> m_currentLevelTasks;
    bool m_finished;
    Phase m_phase;
    bool m_inPreviewPhase;

    // Visualization state
    std::vector<Point> m_currentFarthestPoints;
    std::set<Point> m_activePoints;
    std::deque<Task> m_pendingTasks; // Tasks waiting to be committed

    static float cross(const Point& o, const Point& a, const Point& b);
    static float distanceToLine(const Point& a, const Point& b, const Point& p);
    void initialize();
    std::vector<Point> getPointsOnSide(const Point& a, const Point& b, const std::vector<Point>& points, bool left);
    void updateActivePoints();
    void computePreview();
    void commitPreview();
};

#endif //QUICKHULLALGORITHM_H