#include <gtest/gtest.h>
#include "algorithms/AndrewAlgorithm.h"

static std::vector<Point> runAndrew(const std::vector<Point>& pts) {
    AndrewAlgorithm alg(pts);
    return alg.runCompleteAlgorithm(pts);
}

TEST(AndrewBasics, Triangle) {
    std::vector<Point> pts{{0,0},{1,0},{0,1}};
    auto hull = runAndrew(pts);
    ASSERT_EQ(hull.size(), 3);
}

TEST(AndrewBasics, SquareWithCollinear) {
    std::vector<Point> pts{{0,0},{1,0},{1,1},{0,1},{0.5f,0},{0.5f,1}};
    auto hull = runAndrew(pts);
    ASSERT_EQ(hull.size(), 4);
}

TEST(AndrewEdgeCases, AllCollinear) {
    std::vector<Point> pts{{0,0},{1,0},{2,0},{-1,0}};
    auto hull = runAndrew(pts);
    ASSERT_GE(hull.size(), 2);
    // Endpoints must be present
    bool hasMin = false, hasMax = false;
    for (auto&p: hull) { if (p.x == -1 && p.y == 0) hasMin = true; if (p.x == 2 && p.y == 0) hasMax = true; }
    EXPECT_TRUE(hasMin && hasMax);
}
