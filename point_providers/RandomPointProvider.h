#ifndef RANDOMPOINTPROVIDER_H
#define RANDOMPOINTPROVIDER_H

#include "IPointProvider.h"
#include <random>

class RandomPointProvider : public IPointProvider {

public:
    RandomPointProvider(int count, long width, long height, int margin = 50);

    std::vector<Point> getPoints() override;

private:
    int m_count;
    long m_width;
    long m_height;
    int m_margin;
};

#endif //RANDOMPOINTPROVIDER_H
