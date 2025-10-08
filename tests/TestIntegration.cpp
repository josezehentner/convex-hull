#include <gtest/gtest.h>
#include <fstream>
#include "algorithms/AndrewAlgorithm.h"
#include "algorithms/QuickhullAlgorithm.h"
#include "point_providers/CirclePointProvider.h"
#include "point_providers/FromFilePointProvider.h"
#include "point_providers/LinePointProvider.h"
#include "point_providers/RandomPointProvider.h"
#include "point_providers/SquarePointProvider.h"

static std::vector<Point> loadPoints(const std::string& path) {
    FromFilePointProvider prov(path);
    return prov.getPoints();
}

static std::vector<Point> randomPoints(const int count) {
    RandomPointProvider prov(count, 50000, 50000);
    return prov.getPoints();
}

static std::vector<Point> circlePoints(const int count) {
    CirclePointProvider prov(count, 50000, 50000);
    return prov.getPoints();
}

static std::vector<Point> linePoints(const int count) {
    LinePointProvider prov(count, 50000, 50000);
    return prov.getPoints();
}

static std::vector<Point> squarePoints(const int count) {
    SquarePointProvider prov(count, 50000, 50000);
    return prov.getPoints();
}



static auto sortxy = [](const Point& A, const Point& B){ return A.x < B.x || (A.x == B.x && A.y < B.y);};

TEST(Integration, Files) {
    std::vector<std::string> files = {
        "../../point_files/circle.txt",
        "../../point_files/line.txt",
        "../../point_files/random.txt",
        "../../point_files/random2.txt",
        "../../point_files/square.txt",
        "../../point_files/square2.txt",
        "../../point_files/test.txt",
        "../../point_files/triangle.txt",
    };
    for (const auto& f : files) {
        std::ifstream test(f);
        if (!test.good()) continue;
        auto pts = loadPoints(f);
        auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
        auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
        std::sort(a.begin(), a.end(), sortxy);
        std::sort(q.begin(), q.end(), sortxy);
        ASSERT_EQ(a, q);
    }
}

TEST(Integration, Random10) {
    auto pts = randomPoints(10);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);
    ASSERT_EQ(a, q);
}
TEST(Integration, Random100) {
    auto pts = randomPoints(100);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);
    ASSERT_EQ(a, q);
}
TEST(Integration, Random1000) {
    auto pts = randomPoints(1000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);
    ASSERT_EQ(a, q);
}
TEST(Integration, Random10000) {
    auto pts = randomPoints(10000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);
    ASSERT_EQ(a, q);
}
TEST(Integration, Random100000) {
    auto pts = randomPoints(100000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);
    ASSERT_EQ(a, q);
}
TEST(Integration, Random1000000) {
    auto pts = randomPoints(1000000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);
    ASSERT_EQ(a, q);
}

TEST(Integration, Line10) {
    auto pts = linePoints(10);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(2, a.size());
    ASSERT_EQ(2, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Line100) {
    auto pts = linePoints(100);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(2, a.size());
    ASSERT_EQ(2, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Line1000) {
    auto pts = linePoints(1000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(2, a.size());
    ASSERT_EQ(2, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Line10000) {
    auto pts = linePoints(10000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(2, a.size());
    ASSERT_EQ(2, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Line100000) {
    auto pts = linePoints(100000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(2, a.size());
    ASSERT_EQ(2, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Line1000000) {
    auto pts = linePoints(1000000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(2, a.size());
    ASSERT_EQ(2, q.size());
    ASSERT_EQ(a, q);
}

TEST(Integration, Square10) {
    auto pts = squarePoints(10);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(4, a.size());
    ASSERT_EQ(4, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Square100) {
    auto pts = squarePoints(100);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(4, a.size());
    ASSERT_EQ(4, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Square1000) {
    auto pts = squarePoints(1000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(4, a.size());
    ASSERT_EQ(4, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Square10000) {
    auto pts = squarePoints(10000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(4, a.size());
    ASSERT_EQ(4, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Square100000) {
    auto pts = squarePoints(100000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(4, a.size());
    ASSERT_EQ(4, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Square1000000) {
    auto pts = squarePoints(1000000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(4, a.size());
    ASSERT_EQ(4, q.size());
    ASSERT_EQ(a, q);
}

TEST(Integration, Circle10) {
    auto pts = circlePoints(10);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(10, a.size());
    ASSERT_EQ(10, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Circle100) {
    auto pts = circlePoints(100);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(100, a.size());
    ASSERT_EQ(100, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Circle1000) {
    auto pts = circlePoints(1000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(1000, a.size());
    ASSERT_EQ(1000, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Circle10000) {
    auto pts = circlePoints(10000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(10000, a.size());
    ASSERT_EQ(10000, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Circle100000) {
    auto pts = circlePoints(100000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(100000, a.size());
    ASSERT_EQ(100000, q.size());
    ASSERT_EQ(a, q);
}
TEST(Integration, Circle1000000) {
    auto pts = circlePoints(1000000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);

    ASSERT_EQ(1000000, a.size());
    ASSERT_EQ(1000000, q.size());
    ASSERT_EQ(a, q);
}