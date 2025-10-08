#include <gtest/gtest.h>

#include "point_providers/CirclePointProvider.h"
#include "point_providers/Point.h"
#include "point_providers/RandomPointProvider.h"
#include "point_providers/FromFilePointProvider.h"
#include "point_providers/LinePointProvider.h"
#include "point_providers/SquarePointProvider.h"

TEST(PointOps, Equality) {
    Point a{0.0f, 0.0f};
    Point b{0.0f, 0.0f};
    EXPECT_EQ(a, b);
}

TEST(PointOps, OrderingPrimaryXThenY) {
    Point a{0.0f, 0.0f};
    Point b{0.0f, 1.0f};
    Point c{1.0f, 0.0f};

    EXPECT_TRUE(a < b);

    EXPECT_TRUE(b < c);
    EXPECT_TRUE(a < c);
}

TEST(PointOps, StrictWeakOrderingTransitivity) {
    Point p1{0.0f, 0.0f};
    Point p2{0.0f, 1.0f};
    Point p3{1.0f, 0.0f};

    ASSERT_TRUE(p1 < p2);
    ASSERT_TRUE(p2 < p3);
    EXPECT_TRUE(p1 < p3);

    EXPECT_FALSE(p2 < p1);
    EXPECT_FALSE(p3 < p2);
}

TEST(PointProvider, Random) {
    RandomPointProvider prov(100000, 1200, 800);
    std::vector<Point> points = prov.getPoints();

    ASSERT_EQ(100000, points.size());
}

TEST(PointProvider, Circle) {
    CirclePointProvider prov(100000, 1200, 800);
    std::vector<Point> points = prov.getPoints();

    ASSERT_EQ(100000, points.size());
}

TEST(PointProvider, Line) {
    LinePointProvider prov(100000, 1200, 800);
    std::vector<Point> points = prov.getPoints();

    ASSERT_EQ(100000, points.size());
}

TEST(PointProvider, Square) {
    SquarePointProvider prov(100000, 1200, 800);
    std::vector<Point> points = prov.getPoints();

    ASSERT_EQ(100000, points.size());
}

TEST(PointProvider, File) {
    FromFilePointProvider prov("../../point_files/circle.txt");
    std::vector<Point> points = prov.getPoints();

    ASSERT_EQ(32, points.size());
}