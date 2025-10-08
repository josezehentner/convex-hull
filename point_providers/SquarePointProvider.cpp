#include "SquarePointProvider.h"
#include <algorithm>
#include <cmath>

SquarePointProvider::SquarePointProvider(int count, long width, long height, int margin)
    : m_count(count), m_width(width), m_height(height), m_margin(margin) {}

std::vector<Point> SquarePointProvider::getPoints() {
    std::vector<Point> points;
    points.reserve(static_cast<size_t>(m_count));

    const float left   = static_cast<float>(m_margin);
    const float right  = static_cast<float>(m_height - m_margin);
    const float top    = static_cast<float>(m_margin);
    const float bottom = static_cast<float>(m_height - m_margin);

    const float Lh = right - left;
    const float Lv = bottom - top;

    auto push_int = [&](float xf, float yf) {
        const int xi = static_cast<int>(std::lround(xf));
        const int yi = static_cast<int>(std::lround(yf));
        points.push_back(Point{static_cast<float>(xi), static_cast<float>(yi)});
    };

    if (m_count <= 0 || Lh <= 0.0f || Lv <= 0.0f) {
        return points;
    }

    if (m_count <= 4) {
        const Point corners[4] = {
            {left,  top},
            {right, top},
            {right, bottom},
            {left,  bottom}
        };
        for (int i = 0; i < m_count; ++i) {
            push_int(corners[i].x, corners[i].y);
        }
        return points;
    }

    const int remaining = m_count - 4;

    const float P = 2.0f * (Lh + Lv);
    float want_top    = remaining * (Lh / P);
    float want_right  = remaining * (Lv / P);
    float want_bottom = remaining * (Lh / P);
    float want_left   = remaining * (Lv / P);

    int n_top    = static_cast<int>(std::floor(want_top));
    int n_right  = static_cast<int>(std::floor(want_right));
    int n_bottom = static_cast<int>(std::floor(want_bottom));
    int n_left   = static_cast<int>(std::floor(want_left));

    int assigned = n_top + n_right + n_bottom + n_left;
    int leftover = remaining - assigned;

    struct EdgeShare { float frac; int* n; };
    EdgeShare shares[4] = {
        {want_top    - std::floor(want_top),    &n_top},
        {want_right  - std::floor(want_right),  &n_right},
        {want_bottom - std::floor(want_bottom), &n_bottom},
        {want_left   - std::floor(want_left),   &n_left}
    };
    std::sort(std::begin(shares), std::end(shares),
              [](const EdgeShare& a, const EdgeShare& b){ return a.frac > b.frac; });
    for (int i = 0; i < leftover; ++i) {
        ++(*shares[i].n);
    }

    // Top edge
    push_int(left, top);
    for (int j = 1; j <= n_top; ++j) {
        float t = static_cast<float>(j) / static_cast<float>(n_top + 1);
        push_int(left + t * Lh, top);
    }
    push_int(right, top);

    // Right edge
    for (int j = 1; j <= n_right; ++j) {
        float t = static_cast<float>(j) / static_cast<float>(n_right + 1);
        push_int(right, top + t * Lv);
    }
    push_int(right, bottom);

    // Bottom edge
    for (int j = 1; j <= n_bottom; ++j) {
        float t = static_cast<float>(j) / static_cast<float>(n_bottom + 1);
        push_int(right - t * Lh, bottom);
    }
    push_int(left, bottom);

    // Left edge
    for (int j = 1; j <= n_left; ++j) {
        float t = static_cast<float>(j) / static_cast<float>(n_left + 1);
        push_int(left, bottom - t * Lv);
    }

    return points;
}
