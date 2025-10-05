#include "Performance.h"
#include <iostream>
#include <chrono>
#include "../algorithms/AndrewAlgorithm.h"
#include "../algorithms/QuickHullAlgorithm.h"

void Performance::runAlgorithms(const std::vector<Point>& points) {
    if (points.empty()) {
        std::cerr << "No points to process.\n";
        return;
    }

    std::cout << "\nRunning performance test with " << points.size() << " points...\n";
    std::cout << "--------------------------------------------------------\n";

    auto startA = std::chrono::high_resolution_clock::now();
    AndrewAlgorithm andrew(points);
    auto hullA = andrew.runCompleteAlgorithm(points);
    auto endA = std::chrono::high_resolution_clock::now();
    auto durationA = std::chrono::duration_cast<std::chrono::nanoseconds>(endA - startA).count();

    auto startQ = std::chrono::high_resolution_clock::now();
    QuickHullAlgorithm quick(points);
    auto hullQ = quick.runCompleteAlgorithm(points);
    auto endQ = std::chrono::high_resolution_clock::now();
    auto durationQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endQ - startQ).count();

    std::cout << "Algorithm            Runtime (ms)   Hull Size\n";
    std::cout << "--------------------------------------------------------\n";
    std::cout << "Andrew's Algorithm   " << durationA << " ns\t\t" << hullA.size() << '\n';
    std::cout << "QuickHull Algorithm  " << durationQ << " ns\t\t" << hullQ.size() << '\n';
    std::cout << "--------------------------------------------------------\n";

    if (hullA.size() != hullQ.size()) {
        std::cout << "Warning: Hull sizes differ! ("
                  << hullA.size() << " vs " << hullQ.size() << ")\n";
    } else {
        std::cout << "Hull sizes match. Both algorithms produced consistent results.\n";
    }
}
