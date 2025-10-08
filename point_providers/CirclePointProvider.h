#pragma once
#include <vector>
#include <cmath>
#include "Point.h"
#include "IPointProvider.h"

class CirclePointProvider : public IPointProvider {
public:
    CirclePointProvider(int count, int width, int height, int margin = 50);
    std::vector<Point> getPoints() override;

private:
    int m_count;
    int m_width;
    int m_height;
    int m_margin;
};
