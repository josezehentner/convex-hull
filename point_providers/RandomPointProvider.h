#ifndef RANDOMPOINTPROVIDER_H
#define RANDOMPOINTPROVIDER_H

#include "IPointProvider.h"
#include <random>

class RandomPointProvider : public IPointProvider {
    int m_count;
    int m_width;
    int m_height;
    int m_margin;

public:
    RandomPointProvider(int count, int width, int height, int margin = 50);

    std::vector<Point> getPoints() override;
};

#endif //RANDOMPOINTPROVIDER_H
