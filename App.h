#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include "Point.h"

class App {
public:
    App();
    App(unsigned int width, unsigned int height, unsigned int frameLimit);
    App(unsigned int width, unsigned int height, unsigned int frameLimit, const std::vector<Point>& points);
    void run();

private:
    sf::RenderWindow window;
    unsigned int m_frameLimit;
    std::vector<Point> m_points;

    void processEvents();
    void update();
    void render();
};

#endif //APP_H
