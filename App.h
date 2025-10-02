#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>

class App {
public:
    App();
    void run();

private:
    sf::RenderWindow window;

    void processEvents();
    void update();
    void render();
};



#endif //APP_H
