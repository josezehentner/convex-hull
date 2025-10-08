#pragma once
#include <vector>

#include "IPointProvider.h"
#include "Point.h"

class LinePointProvider : public IPointProvider{
public:
    LinePointProvider(int count, long width, long height, int margin = 50);
    std::vector<Point> getPoints() override;

private:
    int m_count;
    long m_width;
    long m_height;
    int m_margin;
};
