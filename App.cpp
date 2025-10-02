#include "App.h"

App::App()
: window(sf::VideoMode({500, 500}), "SFML works!"), m_frameLimit(60)
{
    window.setFramerateLimit(m_frameLimit);
}

App::App(unsigned int width, unsigned int height, unsigned int frameLimit)
: window(sf::VideoMode({width, height}), "SFML works!"),
  m_frameLimit(frameLimit)
{
    window.setFramerateLimit(m_frameLimit);
}

App::App(unsigned int width, unsigned int height, unsigned int frameLimit, const std::vector<Point>& points)
: window(sf::VideoMode({width, height}), "SFML works!"),
  m_frameLimit(frameLimit),
  m_points(points)
{
    window.setFramerateLimit(m_frameLimit);
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

    for (const auto& p : m_points) {
        sf::CircleShape shape(3.0f); // radius
        shape.setFillColor(sf::Color::Red);
        shape.setPosition({p.x, p.y});
        window.draw(shape);
    }

    window.display();
}
