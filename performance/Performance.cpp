#include "Performance.h"
#include <iostream>
#include <chrono>
#include "../algorithms/AndrewAlgorithm.h"
#include "../algorithms/QuickhullAlgorithm.h"
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

static std::string key(int x, int y) {
    return std::to_string(x) + "," + std::to_string(y);
}

static bool lessXY(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

void printPointDiff(const std::vector<Point>& hullA,
                           const std::vector<Point>& hullQ) {
    std::vector<Point> a = hullA;
    std::vector<Point> q = hullQ;

    std::sort(a.begin(), a.end(), lessXY);
    std::sort(q.begin(), q.end(), lessXY);

    std::unordered_set<std::string> setA;
    std::unordered_set<std::string> setQ;
    setA.reserve(a.size() * 2);
    setQ.reserve(q.size() * 2);

    for (const auto& p : a) setA.insert(key(p.x, p.y));
    for (const auto& p : q) setQ.insert(key(p.x, p.y));

    const char* red = "\033[31m";
    const char* green = "\033[32m";
    const char* yellow = "\033[33m";
    const char* reset = "\033[0m";

    std::cout << "\nMissing in Q:\n";
    size_t miss_in_q = 0;
    for (const auto& p : a) {
        std::string k = key(p.x, p.y);
        if (setQ.find(k) == setQ.end()) {
            ++miss_in_q;
            std::cout << red << "[A only] " << reset << p.x << "," << p.y << "\n";
        }
    }

    std::cout << "\nMissing in A:\n";
    size_t miss_in_a = 0;
    for (const auto& p : q) {
        std::string k = key(p.x, p.y);
        if (setA.find(k) == setA.end()) {
            ++miss_in_a;
            std::cout << yellow << "[Q only] " << reset << p.x << "," << p.y << "\n";
        }
    }

    std::cout << "\nCommon points:\n";
    size_t common = 0;
    size_t i = 0, j = 0;
    while (i < a.size() && j < q.size()) {
        if (a[i].x == q[j].x && a[i].y == q[j].y) {
            ++common;
            std::cout << green << "[both] " << reset << a[i].x << "," << a[i].y << "\n";
            ++i;
            ++j;
        } else if (lessXY(a[i], q[j])) {
            ++i;
        } else {
            ++j;
        }
    }

    std::cout << "\nSummary:\n";
    std::cout << "A count: " << a.size() << "\n";
    std::cout << "Q count: " << q.size() << "\n";
    std::cout << "Common: " << common << "\n";
    std::cout << "Missing in Q: " << miss_in_q << "\n";
    std::cout << "Missing in A: " << miss_in_a << "\n";
}

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

        printPointDiff(hullA, hullQ);
    } else {
        std::cout << "Hull sizes match. Both algorithms produced consistent results.\n";
    }
}