#ifndef POINT_H
#define POINT_H

struct Point {
    float x;
    float y;

    Point() = default;
    Point(float xf, float yf) : x(xf), y(yf) {}
    Point(int xi, int yi) : x(static_cast<float>(xi)), y(static_cast<float>(yi)) {}
};

// Comparison operators for Point to use in std::set
inline bool operator<(const Point& a, const Point& b) {
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

inline bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}
#endif //POINT_H
