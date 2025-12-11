#include "Brick.h"

// LUT – kolory dla ¿ycia 0–3
const std::array<sf::Color, 4> Brick::colorLUT = {
    sf::Color::Transparent, // 0 ¿ycia
    sf::Color::Yellow,      // 1 ¿ycie
    sf::Color::Magenta,     // 2 ¿ycia
    sf::Color::Red          // 3 ¿ycia
};

// Konstruktor standardowy
Brick::Brick(sf::Vector2f StartPo, sf::Vector2f rozmiar, int L)
    : PunktyZycia(L), jestZniszczony(false)
{
    this->setSize(rozmiar);
    this->setPosition(StartPo);
    this->setOutlineColor(sf::Color::White);
    this->setOutlineThickness(1.f);
    aktualizujKolor();
}

// Konstruktor do wczytywania stanu
Brick::Brick(sf::Vector2f StartPo, sf::Vector2f rozmiar, int L, bool destroyed)
    : PunktyZycia(L), jestZniszczony(destroyed)
{
    this->setSize(rozmiar);
    this->setPosition(StartPo);
    this->setOutlineColor(sf::Color::White);
    this->setOutlineThickness(1.f);
    aktualizujKolor();
}

void Brick::aktualizujKolor() {
    if (PunktyZycia < 0) PunktyZycia = 0;
    if (PunktyZycia > 3) PunktyZycia = 3;

    this->setFillColor(colorLUT[PunktyZycia]);
}

void Brick::trafienie() {
    if (jestZniszczony) return;

    PunktyZycia--;

    if (PunktyZycia <= 0) {
        jestZniszczony = true;
    }
    else {
        aktualizujKolor();
    }
}

bool Brick::czyZniszczony() const {
    return jestZniszczony;
}

void Brick::draw(sf::RenderTarget& w) {
    if (!jestZniszczony)
        w.draw(*this);
}
