#include <iostream>
#include "visualization/App.h"
#include "point_providers/RandomPointProvider.h"
#include "point_providers/FromFilePointProvider.h"
#include "algorithms/AndrewAlgorithm.h"
#include "algorithms/QuickhullAlgorithm.h"


int main() {
    std::cout << "Choose mode:\n1. Visualization\n2. Performance\n> ";
    int mode;
    std::cin >> mode;

    if (mode == 1) {
        std::string filename;
        std::cout << "Enter = show whole algorithm" << std::endl;
        std::cout << "Space = step through algorithm" << std::endl;
        std::cout << "Esc = Quit visualization" << std::endl;
        std::cout << "R = Reset algorithm\n" << std::endl;
        std::cout << "Enter filename (./point_files/square.txt): " << std::endl; //TODO: Change to a better selection system
        std::cin >> filename;

        // consumes points from file and stores them in a vector
        FromFilePointProvider provider(filename);
        std::vector<Point> points = provider.getPoints();

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
        App app(1200, 800, 60, points, std::move(algo));
        app.run();
    } else {
        //TODO: Performance mode
    }

    return 0;
}
