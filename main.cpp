#include <iostream>
#include "visualization/App.h"
#include "point_providers/RandomPointProvider.h"
#include "point_providers/FromFilePointProvider.h"
#include "algorithms/AndrewAlgorithm.h"
#include "algorithms/QuickhullAlgorithm.h"
#include "performance/Performance.h"

int main() {
    std::cout << "Choose mode:\n1. Visualization\n2. Performance\n> ";
    int mode;
    std::cin >> mode;
    int width {1200};
    int height {800};
    int fps {60};

    if (mode == 1) {
        std::string filename;

        std::cout << "Generate random points (1); or load points from a .txt file (2)?" << std::endl;
        int pointChoice{1};
        std::cin >> pointChoice;

        std::vector<Point> points;
        if (pointChoice == 1) {
            int nOfPoints;
            std::cout << "How many points do you want to create?" << std::endl;
            std::cin >> nOfPoints;
            RandomPointProvider provider(nOfPoints, width, height, 50);
            points = provider.getPoints();

        }
        else {
            // consumes points from file and stores them in a vector
            std::cout << "Enter filename (./point_files/square.txt): " << std::endl;
            std::cin >> filename;
            FromFilePointProvider provider(filename);
            points = provider.getPoints();
        }

        // getting algorithm choice
        int algorithmChoice{0};
        while (true) {
            std::cout << "Choose an algorithm:\n"
                      << "  (1) Andrew's\n"
                      << "  (2) Quickhull\n"
                      << "Your choice: ";

            if (std::cin >> algorithmChoice && (algorithmChoice == 1 || algorithmChoice == 2)) {
                break;
            }
            std::cout << "Your choice was invalid! Try again." << std::endl;
            std::cin.clear();  // reset fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
        }

        std::unique_ptr<IAlgorithm> algo;
        if (algorithmChoice == 1) {
            algo = std::make_unique<AndrewAlgorithm>(points);
        } else {
            algo = std::make_unique<QuickHullAlgorithm>(points);
        }
        std::cout << "-- APP CONTROL --" << std::endl;
        std::cout << "Enter = show whole algorithm" << std::endl;
        std::cout << "Space = step through algorithm" << std::endl;
        std::cout << "Esc = Quit visualization" << std::endl;
        std::cout << "R = Reset algorithm\n" << std::endl;

        App app(width, height, fps, points, std::move(algo));
        app.run();
    } else if (mode == 2) {
        Performance perf;
        perf.run();
    }

    return 0;
}
