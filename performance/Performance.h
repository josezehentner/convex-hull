#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <vector>
#include <memory>
#include <string>
#include "../point_providers/Point.h"
#include "../point_providers/IPointProvider.h"

class Performance {
public:
    Performance() = default;
    void run();

private:
    std::unique_ptr<IPointProvider> createPointProvider();
    void runAlgorithms(const std::vector<Point>& points);
};

#endif //PERFORMANCE_H
