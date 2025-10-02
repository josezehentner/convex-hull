#include "App.h"

App::App()
: window(sf::VideoMode({500, 500}), "SFML works!")
{
    window.setFramerateLimit(60);
}

void App::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void App::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

void App::update()
{

}

void App::render()
{
    window.clear();
    window.display();
}
