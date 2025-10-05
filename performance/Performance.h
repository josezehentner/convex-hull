#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <vector>
#include "../point_providers/Point.h"

class Performance {
public:
    static void runAlgorithms(const std::vector<Point>& points);
};

#endif //PERFORMANCE_H
