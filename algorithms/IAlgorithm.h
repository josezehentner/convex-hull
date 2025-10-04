#ifndef IALGORITHM_H
#define IALGORITHM_H

#include <vector>
#include "point_providers/Point.h"
class IAlgorithm {
public:
    virtual ~IAlgorithm() = default;

    virtual bool step() = 0;
    virtual bool stepBack() = 0;
    virtual std::vector<Point> runCompleteAlgorithm(const std::vector<Point>& points) = 0;
    virtual std::vector<Point> getCurrentHull() = 0;
    virtual bool isFinished() const = 0;
    virtual void reset(const std::vector<Point>& points) = 0;
};

#endif //IALGORITHM_H
