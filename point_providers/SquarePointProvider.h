#pragma once
#include <vector>
#include "Point.h"
#include "IPointProvider.h"

class SquarePointProvider : public IPointProvider {
public:
    SquarePointProvider(int count, long width, long height, int margin = 50);
    std::vector<Point> getPoints() override;

private:
    int m_count;
    long m_width;
    long m_height;
    int m_margin;
};
