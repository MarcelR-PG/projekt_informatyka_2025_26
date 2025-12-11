#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paletka.h"
#include "Pilka.h"
#include "brick.h"
#include "GameState.h"

// Klasa g³ówna gry — zarz¹dza logik¹, renderowaniem i obs³ug¹ wejœcia
class Game
{
public:
    Game();         // Konstruktor — tworzy okno, obiekty gry i cegie³ki
    void run();     // G³ówna pêtla gry
    void applyState(const GameState& state);    // Wczytywanie stanu zapisanej gry

private:
    void processEvents();       // Obs³uga zdarzeñ okna
    void update();              // Logika gry
    void render();              // Rysowanie sceny

private:
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;

    sf::RenderWindow m_window;      // G³ówne okno gry
    Paletka m_paletka;              // Obiekt paletki
    Pilka m_pilka;                  // Obiekt pi³ki
    std::vector<Brick> m_bricks;    // Tablica cegie³ek

    const int rows = 5;     
    const int cols = 10;
};
