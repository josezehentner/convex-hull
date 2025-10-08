#pragma once
#include <vector>
#include <cmath>
#include "Point.h"
#include "IPointProvider.h"

class CirclePointProvider : public IPointProvider {
public:
    CirclePointProvider(int count, long width, long height, int margin = 50);
    std::vector<Point> getPoints() override;

private:
    int m_count;
    long m_width;
    long m_height;
    int m_margin;
};
