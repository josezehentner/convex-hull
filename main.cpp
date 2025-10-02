#include <iostream>
#include "App.h"
#include "point_providers/RandomPointProvider.h"
#include "point_providers/PresetPointProvider.h"


int main() {
    std::cout << "Choose mode:\n1. Visualization\n2. Performance\n> ";
    int mode;
    std::cin >> mode;

    if (mode == 1) {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;

        PresetPointProvider provider(filename);
        std::vector<Point> points = provider.getPoints();

        App app(1200, 800, 60, points);
        app.run();
    } else {
        //TODO: Performance mode
    }

    return 0;
}
