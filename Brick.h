#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Brick : public sf::RectangleShape {
private:
    int PunktyZycia;
    bool jestZniszczony;

    static const std::array<sf::Color, 4> colorLUT;

public:
    // Konstruktor standardowy
    Brick(sf::Vector2f StartPo, sf::Vector2f rozmiar, int L);

    // Konstruktor do wczytywania stanu
    Brick(sf::Vector2f StartPo, sf::Vector2f rozmiar, int L, bool destroyed);

    void aktualizujKolor();
    void trafienie();
    bool czyZniszczony() const;

    void draw(sf::RenderTarget& w);
    int getHP() const { return PunktyZycia; }
    sf::Vector2f getPosition() const { return sf::RectangleShape::getPosition(); }
};
