#pragma once
#include <vector>

#include "IPointProvider.h"
#include "Point.h"

class LinePointProvider : public IPointProvider{
public:
    LinePointProvider(int count, int width, int height, int margin = 50);
    std::vector<Point> getPoints() override;

private:
    int m_count;
    int m_width;
    int m_height;
    int m_margin;
};
