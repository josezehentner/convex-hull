#include <gtest/gtest.h>
#include <fstream>
#include "algorithms/AndrewAlgorithm.h"
#include "algorithms/QuickhullAlgorithm.h"
#include "point_providers/FromFilePointProvider.h"
#include "point_providers/RandomPointProvider.h"

static std::vector<Point> loadPoints(const std::string& path) {
    FromFilePointProvider prov(path);
    return prov.getPoints();
}

static std::vector<Point> randomPoints(const int count) {
    RandomPointProvider prov(count, 1200, 800);
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

TEST(Integration, Random) {
    auto pts = randomPoints(100000);
    auto a = AndrewAlgorithm(pts).runCompleteAlgorithm(pts);
    auto q = QuickHullAlgorithm(pts).runCompleteAlgorithm(pts);
    std::sort(a.begin(), a.end(), sortxy);
    std::sort(q.begin(), q.end(), sortxy);
    ASSERT_EQ(a, q);
}