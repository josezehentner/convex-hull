#pragma once
#include <vector>
#include "Point.h"
#include "IPointProvider.h"

class SquarePointProvider : public IPointProvider {
public:
    SquarePointProvider(int count, int width, int height, int margin = 50);
    std::vector<Point> getPoints() override;

private:
    int m_count;
    int m_width;
    int m_height;
    int m_margin;
};
