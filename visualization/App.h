#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include "../point_providers/Point.h"
#include "../algorithms/IAlgorithm.h"
#include <functional>

class App {
public:
    App(unsigned int width,
        unsigned int height,
        unsigned int frameLimit,
        const std::vector<Point>& points,
        std::unique_ptr<IAlgorithm> algorithm);
    void run();

    void setAlgorithms(std::vector<std::string> names,
                   std::vector<std::function<std::unique_ptr<IAlgorithm>()>> makers,
                   int initialIndex = 0);

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

    std::vector<std::function<std::unique_ptr<IAlgorithm>()>> m_algoMakers;
    std::vector<std::string> m_algoNames;
    int m_algoIndex = 0;

    void selectAlgorithm(int idx);
};

#endif
