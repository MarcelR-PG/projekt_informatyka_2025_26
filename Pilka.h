#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Paletka.h"

class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float startX, float startY, float startVx, float startVy, float r)
        : x(startX), y(startY), vx(startVx), vy(startVy), radius(r)
    {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
    }

    void move() { x += vx; y += vy; shape.setPosition(x, y); }
    void bounceX() { vx = -vx; }
    void bounceY() { vy = -vy; }

    void collideWalls(float width, float height) {
        if (x - radius <= 0.f) { x = radius; bounceX(); }
        if (x + radius >= width) { x = width - radius; bounceX(); }
        if (y - radius <= 0.f) { y = radius; bounceY(); }
        shape.setPosition(x, y);
    }

    bool collidePaddle(const Paletka& p) {
        float palX = p.getX();
        float palY = p.getY();
        float palW = p.getSzerokosc();
        float palH = p.getWysokosc();

        bool wZakresieX = (x >= palX - palW / 2.f) && (x <= palX + palW / 2.f);
        bool wZakresieY = ((y + radius) >= (palY - palH / 2.f)) &&
            ((y - radius) < (palY - palH / 2.f));

        if (wZakresieX && wZakresieY) {
            vy = -std::abs(vy);
            y = (palY - palH / 2.f) - radius;
            shape.setPosition(x, y);
            return true;
        }
        return false;
    }

    void draw(sf::RenderTarget& target) { target.draw(shape); }

    void reset(sf::Vector2f pos, sf::Vector2f vel)
    {
        x = pos.x;
        y = pos.y;
        vx = vel.x;
        vy = vel.y;
        shape.setPosition(x, y);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getRadius() const { return radius; }
};
