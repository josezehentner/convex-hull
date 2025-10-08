#include <iostream>
#include "visualization/App.h"
#include "point_providers/RandomPointProvider.h"
#include "point_providers/FromFilePointProvider.h"
#include "algorithms/AndrewAlgorithm.h"
#include "algorithms/QuickhullAlgorithm.h"
#include "performance/Performance.h"

void getPoints(int width, int height, int margin, std::vector<Point> &points) {
    std::cout << "Generate random points (1); or load points from a .txt file (2)?" << std::endl;
    int pointChoice{1};
    std::cin >> pointChoice;

    if (pointChoice == 1) {
        int nOfPoints;
        std::cout << "How many points do you want to create?" << std::endl;
        std::cin >> nOfPoints;

        if (log10(nOfPoints) >= 5) {
            width = width * static_cast<int>(pow(log10(nOfPoints), 2));
            height = width;
        }

        RandomPointProvider provider(nOfPoints, width, height, margin);
        points = provider.getPoints();
    }
    else {
        // consumes points from file and stores them in a vector
        while (points.empty()) {
            std::string filename;
            std::cout << "Enter filename (e.g., ../point_files/square.txt): " << std::endl;
            std::cin >> filename;
            FromFilePointProvider provider(filename);
            points = provider.getPoints();

            if (points.empty()) {
                std::cout << "File not found! Please try again." << std::endl;
            }
        }
    }
}

int main() {
    std::cout << "Choose mode:\n1. Visualization\n2. Performance\n> ";
    int mode;
    std::cin >> mode;
    int width {1200};
    int height {800};
    int fps {60};
    int margin {50};

    if (mode == 1) {
        std::vector<Point> points;
        getPoints(width, height, margin, points);

        std::unique_ptr<IAlgorithm> algo = std::make_unique<AndrewAlgorithm>(points);

        App app(width, height, fps, points, std::move(algo));

        app.setAlgorithms(
            {"Andrew", "QuickHull"},
            {
                [points]{ return std::make_unique<AndrewAlgorithm>(points); },
                [points]{ return std::make_unique<QuickHullAlgorithm>(points); }
            },
            0
        );


        app.run();
    } else if (mode == 2) {
        std::cout << "\n--- PERFORMANCE MODE ---\n";
        std::vector<Point> points;
        getPoints(width, height, margin, points);

        Performance::runAlgorithms(points);
    }

    return 0;
}
