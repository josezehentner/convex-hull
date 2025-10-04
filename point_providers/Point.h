#ifndef POINT_H
#define POINT_H

struct Point {
    float x;
    float y;
};

// Comparison operators for Point to use in std::set
inline bool operator<(const Point& a, const Point& b) {
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

inline bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}
#endif //POINT_H
