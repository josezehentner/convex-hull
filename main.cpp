#include <iostream>
#include "visualization/App.h"
#include "point_providers/RandomPointProvider.h"
#include "point_providers/FromFilePointProvider.h"
#include "algorithms/AndrewAlgorithm.h"


int main() {
    std::cout << "Choose mode:\n1. Visualization\n2. Performance\n> ";
    int mode;
    std::cin >> mode;

    if (mode == 1) {
        std::string filename;
        std::cout << "Enter = show whole algorithm" << std::endl;
        std::cout << "Space = step through algorithm" << std::endl;
        std::cout << "Esc = Quit visualization" << std::endl;
        std::cout << "R = Reset algorithm" << std::endl;
        std::cout << "Enter filename (../point_files/square.txt): "; //TODO: Change to a better selection system
        std::cin >> filename;

        // consumes points from file and stores them in a vector
        FromFilePointProvider provider(filename);
        std::vector<Point> points = provider.getPoints();

        // right now the visualizer consumes points and algorithm, so it's currently designed to be controlled
        // by main in the console, if we want to switch to gui control later this design here won't work
        auto algo = std::make_unique<AndrewAlgorithm>(points);
        App app(1200, 800, 60, points, std::move(algo));
        app.run();
    } else {
        //TODO: Performance mode
    }

    return 0;
}
