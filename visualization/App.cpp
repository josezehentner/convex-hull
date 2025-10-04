
#include "App.h"
#include "../algorithms/QuickHullAlgorithm.h"
#include "../algorithms/AndrewAlgorithm.h"
#include <map>

App::App(unsigned int w, unsigned int h, unsigned int frameLimit, const std::vector<Point>& points, std::unique_ptr<IAlgorithm> algorithm)
: window(sf::VideoMode({w, h}), "Convex Hull Visualisation"),
  m_frameLimit(frameLimit),
  m_points(points),
  m_algorithm(std::move(algorithm))
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
        if (event->is<sf::Event::KeyPressed>()) {
            auto key = event->getIf<sf::Event::KeyPressed>()->scancode;
            if (key == sf::Keyboard::Scan::Space) {
                m_algorithm->step();
            }
            if (key == sf::Keyboard::Scan::Enter) {
                m_autoPlay = !m_autoPlay;
            }
            if (key == sf::Keyboard::Scan::Escape) {
                window.close();
            }
            if (key == sf::Keyboard::Scan::R) {
                m_algorithm->reset(m_points);
            }
        }
    }
}

void App::update()
{
    if (m_autoPlay) {
        if (++m_frameCounter % 10 == 0) {
            m_algorithm->step();
        }
    }
}

void App::render()
{
    window.clear(sf::Color(25, 25, 35));

    AndrewAlgorithm* andrew = dynamic_cast<AndrewAlgorithm*>(m_algorithm.get());
    QuickHullAlgorithm* quickhull = dynamic_cast<QuickHullAlgorithm*>(m_algorithm.get());

    // Classify all points by their rendering role
    enum class PointRole {
        INACTIVE,       // Grey - eliminated/processed
        NORMAL,         // Light red - regular point
        CANDIDATE,      // Yellow - being considered
        FARTHEST,       // Green - farthest point found
        HULL,           // Blue - on the hull
        CURRENT         // Orange/Purple - current point being processed
    };

    std::map<Point, PointRole> pointRoles;

    // Initialize all points as NORMAL
    for (const Point& p : m_points) {
        pointRoles[p] = PointRole::NORMAL;
    }

    // Get algorithm-specific data
    std::vector<Point> hull = m_algorithm->getCurrentHull();
    bool finished = m_algorithm->isFinished();

    // Classify points based on algorithm state
    if (quickhull && quickhull->hasActiveSegments()) {
        std::set<Point> activePoints = quickhull->getActivePoints();
        bool isPreview = quickhull->isInPreviewPhase();

        // Mark inactive points
        for (const Point& p : m_points) {
            if (activePoints.find(p) == activePoints.end()) {
                pointRoles[p] = PointRole::INACTIVE;
            }
        }

        // Mark candidates
        auto candidates = quickhull->getCandidatePoints();

        for (const Point& p : candidates) {
            pointRoles[p] = PointRole::CANDIDATE;
        }
        // Mark farthest points (only in preview)
        if (isPreview) {
            auto farthest = quickhull->getFarthestPoints();
            for (const Point& p : farthest) {
                pointRoles[p] = PointRole::FARTHEST;
            }
        }
    }

    // Mark hull points (override previous classifications except CURRENT and FARTHEST)
    for (const Point& p : hull) {
        if (pointRoles[p] != PointRole::CURRENT && pointRoles[p] != PointRole::FARTHEST) {
            pointRoles[p] = PointRole::HULL;
        }
    }

    if (andrew && !andrew->isFinished()) {
        pointRoles[andrew->getCurrentPoint()] = PointRole::CANDIDATE;
    }

    // === RENDERING PHASE ===
    // 1. Draw hull edges first (background layer)
    if (hull.size() >= 2) {
        // Adjust loop bound only if AndrewAlgorithm is active and not finished
        size_t end = hull.size();
        if (andrew && !finished) {
            end = hull.size() - 1;  // don’t close the loop yet
        }

        for (size_t i = 0; i < end; i++) {
            size_t next = (i + 1) % hull.size();

            sf::VertexArray edge(sf::PrimitiveType::Lines, 2);
            edge[0].position = {hull[i].x, hull[i].y};
            edge[1].position = {hull[next].x, hull[next].y};

            sf::Color col = finished ? sf::Color(100, 150, 255)
                                     : sf::Color(120, 180, 255);
            edge[0].color = col;
            edge[1].color = col;

            window.draw(edge);
        }
    }

    // 2. Draw active segments (QuickHull only)
    if (quickhull && quickhull->hasActiveSegments()) {
        auto activeSegments = quickhull->getActiveSegments();
        for (const auto& [start, end] : activeSegments) {
            for (float offset = -1.5f; offset <= 1.5f; offset += 0.5f) {
                sf::VertexArray line(sf::PrimitiveType::Lines, 2);
                line[0].position = {start.x + offset, start.y};
                line[0].color = sf::Color(255, 100, 0, 180);
                line[1].position = {end.x + offset, end.y};
                line[1].color = sf::Color(255, 100, 0, 180);
                window.draw(line);
            }
        }
    }

    // 3. Draw all points based on their role (render each point ONCE)
    for (const auto& [point, role] : pointRoles) {
        sf::CircleShape shape;

        switch (role) {
            case PointRole::INACTIVE:
                shape.setRadius(3.5f);
                shape.setFillColor(sf::Color(80, 80, 80));
                shape.setOutlineColor(sf::Color(60, 60, 60));
                shape.setOutlineThickness(0.3f);
                shape.setPosition({point.x - 3.5f, point.y - 3.5f});
                break;

            case PointRole::NORMAL:
                shape.setRadius(3.5f);
                shape.setFillColor(sf::Color(200, 100, 100));
                shape.setOutlineColor(sf::Color(150, 50, 50));
                shape.setOutlineThickness(0.5f);
                shape.setPosition({point.x - 3.5f, point.y - 3.5f});
                break;

            case PointRole::CANDIDATE:
                shape.setRadius(5.5f);
                shape.setFillColor(sf::Color(255, 200, 0));
                shape.setOutlineColor(sf::Color(255, 255, 100));
                shape.setOutlineThickness(1.5f);
                shape.setPosition({point.x - 5.5f, point.y - 5.5f});
                break;

            case PointRole::FARTHEST:
                // Draw glow first
                {
                    sf::CircleShape glow(12.0f);
                    glow.setFillColor(sf::Color(0, 255, 100, 60));
                    glow.setPosition({point.x - 12.0f, point.y - 12.0f});
                    window.draw(glow);
                }
                shape.setRadius(7.0f);
                shape.setFillColor(sf::Color(0, 255, 100));
                shape.setOutlineColor(sf::Color(255, 255, 255));
                shape.setOutlineThickness(2.5f);
                shape.setPosition({point.x - 7.0f, point.y - 7.0f});
                break;

            case PointRole::HULL:
                shape.setRadius(5.0f);
                if (finished) {
                    shape.setFillColor(sf::Color(80, 130, 255));
                } else {
                    shape.setFillColor(sf::Color(100, 160, 255));
                }
                shape.setOutlineColor(sf::Color::White);
                shape.setOutlineThickness(1.5f);
                shape.setPosition({point.x - 5.0f, point.y - 5.0f});
                break;

            case PointRole::CURRENT:
                shape.setRadius(6.0f);
                shape.setOutlineColor(sf::Color::White);
                shape.setOutlineThickness(3.0f);
                shape.setPosition({point.x - 6.0f, point.y - 6.0f});
                break;
        }

        window.draw(shape);
    }

    window.display();
}