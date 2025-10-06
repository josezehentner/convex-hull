#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include "../point_providers/Point.h"
#include "../algorithms/IAlgorithm.h"

class App {
public:
    App(unsigned int width,
        unsigned int height,
        unsigned int frameLimit,
        const std::vector<Point>& points,
        std::unique_ptr<IAlgorithm> algorithm);
    void run();

private:
    sf::RenderWindow window;
    unsigned int m_frameLimit;
    std::vector<Point> m_points;
    std::unique_ptr<IAlgorithm> m_algorithm;
    bool m_autoPlay = false;
    int m_frameCounter = 0;

    sf::Font m_uiFont;
    bool m_fontLoaded = false;
    bool m_showHelp = true;

    void processEvents();
    void update();
    void render();

    void drawOverlay();
    void loadUiFont();
};

#endif
