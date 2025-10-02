#ifndef RANDOMPOINTPROVIDER_H
#define RANDOMPOINTPROVIDER_H

#include "IPointProvider.h"
#include <random>

class RandomPointProvider : public IPointProvider {

public:
    RandomPointProvider(int count, int width, int height, int margin = 50);

    std::vector<Point> getPoints() override;

private:
    int m_count;
    int m_width;
    int m_height;
    int m_margin;
};

#endif //RANDOMPOINTPROVIDER_H
