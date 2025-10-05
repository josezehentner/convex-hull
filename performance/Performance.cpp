#include "Performance.h"
#include <iostream>
#include <chrono>
#include <limits>
#include <memory>

#include "../point_providers/FromFilePointProvider.h"
#include "../point_providers/RandomPointProvider.h"
#include "../algorithms/AndrewAlgorithm.h"
#include "../algorithms/QuickHullAlgorithm.h"

void Performance::run() {
    std::cout << "\n=== PERFORMANCE MODE ===\n";
    std::cout << "This mode benchmarks both algorithms without visualization.\n";

    // Create point provider (file or random)
    auto provider = createPointProvider();
    if (!provider) {
        std::cerr << "Error: Could not create point provider.\n";
        return;
    }

    // Get points
    std::vector<Point> points;
    try {
        points = provider->getPoints();
    } catch (const std::exception& e) {
        std::cerr << "Error generating or loading points: " << e.what() << std::endl;
        return;
    }

    if (points.empty()) {
        std::cerr << "No points available for benchmarking.\n";
        return;
    }

    runAlgorithms(points);
}

// ----------------------------------------------------------
// Choose between file and random provider
// ----------------------------------------------------------
std::unique_ptr<IPointProvider> Performance::createPointProvider() {
    std::cout << "\nChoose data source:\n";
    std::cout << "  (1) Load points from file\n";
    std::cout << "  (2) Generate random points\n> ";

    int choice = 0;
    while (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::cout << "Invalid input! Please enter 1 or 2: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (choice == 1) {
        std::string filename;
        std::cout << "Enter filename (e.g. ./point_files/square.txt): ";
        std::cin >> filename;
        return std::make_unique<FromFilePointProvider>(filename);
    }

    // Random point generation parameters
    int count = 0;
    std::cout << "Enter number of random points to generate: ";
    while (!(std::cin >> count) || count <= 0) {
        std::cout << "Invalid number! Please enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    const int width = 1200;
    const int height = 800;
    const int margin = 50;
    return std::make_unique<RandomPointProvider>(count, width, height, margin);
}

// ----------------------------------------------------------
// Benchmark both algorithms with chrono
// ----------------------------------------------------------
void Performance::runAlgorithms(const std::vector<Point>& points) {
    std::cout << "\nRunning benchmark with " << points.size() << " points...\n";
    std::cout << "--------------------------------------------------------\n";

    // === Andrew’s Algorithm ===
    auto startA = std::chrono::high_resolution_clock::now();
    AndrewAlgorithm andrew(points);
    auto hullA = andrew.runCompleteAlgorithm(points);
    auto endA = std::chrono::high_resolution_clock::now();
    auto durationA = std::chrono::duration_cast<std::chrono::milliseconds>(endA - startA).count();

    // === QuickHull Algorithm ===
    auto startQ = std::chrono::high_resolution_clock::now();
    QuickHullAlgorithm quick(points);
    auto hullQ = quick.runCompleteAlgorithm(points);
    auto endQ = std::chrono::high_resolution_clock::now();
    auto durationQ = std::chrono::duration_cast<std::chrono::milliseconds>(endQ - startQ).count();

    // === Print Results ===
    std::cout << "Algorithm            Runtime (ms)   Hull Size\n";
    std::cout << "--------------------------------------------------------\n";
    std::cout << "Andrew's Algorithm   " << durationA << " ms\t\t" << hullA.size() << '\n';
    std::cout << "QuickHull Algorithm  " << durationQ << " ms\t\t" << hullQ.size() << '\n';
    std::cout << "--------------------------------------------------------\n";

    if (hullA.size() != hullQ.size()) {
        std::cout << "Warning: Hull sizes differ! ("
                  << hullA.size() << " vs " << hullQ.size() << ")\n";
    } else {
        std::cout << "Hull sizes match. Both algorithms produced consistent results.\n";
    }

    std::cout << "Performance test completed.\n";
}