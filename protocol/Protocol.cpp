#include "Protocol.h"

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <sstream>

#include "point_providers/Point.h"

#include "point_providers/RandomPointProvider.h"
#include "point_providers/CirclePointProvider.h"
#include "point_providers/SquarePointProvider.h"
#include "point_providers/LinePointProvider.h"

#include "algorithms/AndrewAlgorithm.h"
#include "algorithms/QuickhullAlgorithm.h"

template <class F>
long long time_ns(F&& f) {
    auto t0 = std::chrono::high_resolution_clock::now();
    f();
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
}

inline std::string fmt2(double v) {
    std::ostringstream os;
    os.setf(std::ios::fixed);
    os << std::setprecision(2) << v;
    return os.str();
}

void Protocol::run() {
    struct ProviderSpec {
        std::string name;
        std::function<std::vector<Point>(int,long,long,int)> makePoints;
    };

    std::vector<ProviderSpec> providers = {
        {"random", [](int n, long w, long h, int m) {
            RandomPointProvider p(n, w, h, m);
            return p.getPoints();
        }},
        {"square", [](int n, long w, long h, int m) {
            SquarePointProvider p(n, w, h, m);
            return p.getPoints();
        }},
        {"line", [](int n, long w, long h, int m) {
            LinePointProvider p(n, w, h, m);
            return p.getPoints();
        }},
    {"circle", [](int n, long w, long h, int m) {
            CirclePointProvider p(n, w, h, m);
            return p.getPoints();
        }},
    };

    std::vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000};

    std::cout << "Pattern | Number of Points | Time Andrew | Multiple Andrew | Time Quickhull | Multiple Quickhull" << std::endl;
    std::cout << "---|---|---|---|---|---" << std::endl;

    for (const auto& prov : providers) {
        long long prevA = 0;
        long long prevQ = 0;
        bool first = true;

        for (int n : sizes) {
            const long width = LONG_MAX;
            const long height = LONG_MAX;
            int margin = 0;

            std::vector<Point> points = prov.makePoints(n, width, height, margin);
            if (points.empty()) {
                std::cout << prov.name << " | " << n << " | 0ns | NA | 0ns | NA" << std::endl;
                continue;
            }

            long long nsA = time_ns([&](){
                AndrewAlgorithm andrew(points);
                volatile auto hullA = andrew.runCompleteAlgorithm(points);
                (void)hullA;
            });

            long long nsQ = time_ns([&](){
                QuickHullAlgorithm quick(points);
                volatile auto hullQ = quick.runCompleteAlgorithm(points);
                (void)hullQ;
            });

            std::string multA = first ? "NA"
                                      : fmt2(static_cast<double>(nsA) / static_cast<double>(prevA));
            std::string multQ = first ? "NA"
                                      : fmt2(static_cast<double>(nsQ) / static_cast<double>(prevQ));

            std::cout
                << prov.name << " | "
                << n << " | "
                << nsA << "ns | "
                << multA << " | "
                << nsQ << "ns | "
                << multQ << std::endl;

            prevA = nsA;
            prevQ = nsQ;
            first = false;
        }
    }
}
