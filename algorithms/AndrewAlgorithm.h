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
    std::vector<Point> runCompleteAlgorithm(const std::vector<Point>& points) override;

private:
    std::vector<Point> m_points;
    std::vector<Point> m_hull;
    size_t m_index;
    bool m_finished;
};

#endif //ANDREWALGORITHM_H
