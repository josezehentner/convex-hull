#ifndef ANDREWALGORITHM_H
#define ANDREWALGORITHM_H

#include "IAlgorithm.h"
#include <algorithm>

class AndrewAlgorithm : public IAlgorithm {
public:
    explicit AndrewAlgorithm(const std::vector<Point>& points);

    bool step() override;
    std::vector<Point> getCurrentHull() override;
    void reset(const std::vector<Point>& points) override;
    bool isFinished() const override;
    std::vector<Point> runCompleteAlgorithm(const std::vector<Point>& points) override;

private:
    enum class Phase { UPPER, LOWER, DONE }; // Phases of the algo

    std::vector<Point> m_points;
    std::vector<Point> m_upper;
    std::vector<Point> m_lower;
    std::vector<Point> m_hull;

    size_t m_index;
    bool m_finished;
    Phase m_phase;

    static float CrossProduct(const Point& O, const Point& A, const Point& B);
    void addPointToChain(std::vector<Point>& chain, const Point& p);
};

#endif //ANDREWALGORITHM_H
