
#ifndef ANDREWALGORITHM_H
#define ANDREWALGORITHM_H

#include "IAlgorithm.h"
#include <algorithm>
#include <set>

class AndrewAlgorithm : public IAlgorithm {
public:
    explicit AndrewAlgorithm(const std::vector<Point>& points);

    bool step() override;
    std::vector<Point> getCurrentHull() override;
    void reset(const std::vector<Point>& points) override;
    bool isFinished() const override; // needed for render() in App.cpp only
    std::vector<Point> runCompleteAlgorithm(const std::vector<Point>& points) override;

    // Visualization methods
    Point getCurrentPoint() const { return m_currentPoint; }
    bool hasCurrentPoint() const { return m_hasCurrentPoint; }
    enum class Phase { UPPER, LOWER, DONE };
    Phase getPhase() const { return m_phase; }

private:
    std::vector<Point> m_points;
    std::vector<Point> m_upper;
    std::vector<Point> m_lower;
    std::vector<Point> m_hull;

    size_t m_index;
    bool m_finished;
    Phase m_phase;

    static float crossProduct(const Point& O, const Point& A, const Point& B);
    // Visualization state
    Point m_currentPoint;
    bool m_hasCurrentPoint;

    void addPointToChain(std::vector<Point>& chain, const Point& p);
};

#endif //ANDREWALGORITHM_H