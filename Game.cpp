#include "Game.h"
#include <iostream>
#include <algorithm>
#include <cmath>

Game::Game()
    : m_window({ (unsigned)WIDTH, (unsigned)HEIGHT }, "Arkanoid - SFML"),
    m_paletka(320.f, 440.f, 100.f, 20.f, 8.f),
    m_pilka(320.f, 200.f, 4.f, 3.f, 8.f)
{
    m_window.setFramerateLimit(60);

    sf::Vector2f brickSize(60.f, 20.f);
    const float startX = 10.f;
    const float startY = 20.f;
    const float spacingX = 2.f;
    const float spacingY = 2.f;

    for (int ry = 0; ry < rows; ry++)
        for (int cx = 0; cx < cols; cx++)
            m_bricks.emplace_back(
                sf::Vector2f(startX + cx * (brickSize.x + spacingX),
                    startY + ry * (brickSize.y + spacingY)),
                brickSize, 3);
}

void Game::applyState(const GameState& state)
{
    GameState s = state;
    s.apply(m_paletka, m_pilka, m_bricks);
}

static float clampf(float v, float lo, float hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

void Game::run()
{
    while (m_window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
        if (event.type == sf::Event::Closed)
            m_window.close();
}

void Game::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paletka.moveLeft();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paletka.moveRight();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
    {
        GameState snap(m_paletka, m_pilka, m_bricks);
        snap.saveToFile("zapis.txt");
        std::cout << "Gra zapisana!\n";
    }

    m_paletka.clampToBounds(WIDTH);
    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);
    m_pilka.collidePaddle(m_paletka);

    
    for (auto& br : m_bricks) // Detekcja kolizji pi³ka-cegie³ka
    {
        if (br.czyZniszczony())
            continue;

        // Pozycja i rozmiar cegie³ki
        sf::Vector2f pos = br.getPosition(); 
        sf::Vector2f size = br.getSize();
        float left = pos.x;
        float top = pos.y;
        float right = left + size.x;
        float bottom = top + size.y;

        // Pozycja pi³ki i promieñ
        float bx = m_pilka.getX();
        float by = m_pilka.getY();
        float r = m_pilka.getRadius();

        
        float closestX = clampf(bx, left, right);
        float closestY = clampf(by, top, bottom);

        float dx = bx - closestX;
        float dy = by - closestY;

        if ((dx * dx + dy * dy) <= (r * r))
        {
            // Kolizja wykryta — zdecyduj czy odbiæ po X czy Y
            if (std::abs(dx) > std::abs(dy))
                m_pilka.bounceX();
            else
                m_pilka.bounceY();

            br.trafienie();

            m_pilka.move();

            // Przerwij sprawdzanie, ¿eby nie trafiaæ wielu cegie³ jednoczeœnie
            break;
        }
    }

    if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT)
        m_window.close();
}

void Game::render()
{
    m_window.clear();
    for (auto& b : m_bricks) b.draw(m_window);
    m_paletka.draw(m_window);
    m_pilka.draw(m_window);
    m_window.display();
}
