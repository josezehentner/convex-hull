#include <gtest/gtest.h>
#include "algorithms/QuickhullAlgorithm.h"

static std::vector<Point> runQuick(const std::vector<Point>& pts) {
    QuickHullAlgorithm alg(pts);
    return alg.runCompleteAlgorithm(pts);
}

TEST(QuickHullBasics, Triangle) {
    std::vector<Point> pts{{0,0},{1,0},{0,1}};
    auto hull = runQuick(pts);
    ASSERT_EQ(hull.size(), 3);
}

TEST(QuickHullBasics, RotatedSquare) {
    std::vector<Point> pts{{0,1},{1,0},{0,-1},{-1,0}};
    auto hull = runQuick(pts);
    ASSERT_EQ(hull.size(), 4);
}
