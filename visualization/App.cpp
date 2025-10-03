#include "App.h"

//Default Ctor
App::App()
: window(sf::VideoMode({500, 500}), "SFML works!"), m_frameLimit(60)
{
    window.setFramerateLimit(m_frameLimit);
}

// Ctor needs points and algorithm
App::App(unsigned int w, unsigned int h, unsigned int frameLimit, const std::vector<Point>& points, std::unique_ptr<IAlgorithm> algorithm)
: window(sf::VideoMode({w, h}), "Convex Hull Visualisation"),
  m_frameLimit(frameLimit),
  m_points(points),
  m_algorithm(std::move(algorithm))
{
    window.setFramerateLimit(m_frameLimit);
    m_algorithm->step(); //Essential, otherwise the animation starts with the second spacebar stroke
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

// Eventlistener
void App::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        //TODO: Add event to reset algorithm
        if (event->is<sf::Event::KeyPressed>()) {
            auto key = event->getIf<sf::Event::KeyPressed>()->scancode;
            // Allows stepping through the algorithm with spacebar
            if (key == sf::Keyboard::Scan::Space) {
                m_algorithm->step();
            }
            // Shows complete algorithm with enter
            if (key == sf::Keyboard::Scan::Enter) {
                m_autoPlay = !m_autoPlay;
            }
            // Quit with escape
            if (key == sf::Keyboard::Scan::Escape) {
                window.close();
            }
            if (key == sf::Keyboard::Scan::R)
            {
                m_algorithm->reset(m_points);
                m_algorithm->step();
            }
        }
    }
}


// For animation
void App::update()
{
    if (m_autoPlay) {
        if (++m_frameCounter % 10 == 0) { // slow down steps
            m_algorithm->step();
        }
    }
}

void App::render()
{
    window.clear();

    // Draws points as small circles
    for (const Point& p : m_points) {
        sf::CircleShape shape(3.0f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition({p.x, p.y});
        window.draw(shape);
    }

    // Draws connection lines
    std::vector<Point> hull = m_algorithm->getCurrentHull();
    if (!hull.empty())
    {
        bool finished = m_algorithm->isFinished();

        size_t count = finished ? hull.size() + 1 : hull.size();
        sf::VertexArray lines(sf::PrimitiveType::LineStrip, count);

        for (size_t i = 0; i < hull.size(); i++) {
            lines[i].position = {hull[i].x, hull[i].y};
            lines[i].color = sf::Color::Blue;
        }

        if (finished) {
            lines[hull.size()].position = {hull[0].x, hull[0].y};
            lines[hull.size()].color = sf::Color::Blue;
        }

        window.draw(lines);
        window.display();
    }
}
