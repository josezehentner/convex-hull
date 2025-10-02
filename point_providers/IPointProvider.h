#ifndef IPOINTPROVIDER_H
#define IPOINTPROVIDER_H

#include <vector>
#include "Point.h"

class IPointProvider {
public:
    virtual std::vector<Point> getPoints() = 0;
    virtual ~IPointProvider() = default;
};

#endif //IPOINTPROVIDER_H
