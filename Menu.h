#pragma once
#include <SFML/Graphics.hpp>

#define MAX_LICZBA_POZIOMOW 4

class Menu
{
private:
    sf::Font font;
    sf::Text menu[MAX_LICZBA_POZIOMOW];
    int selectedItem = 0;

public:
    Menu(float width, float height);
    int getSelectedItem() { return selectedItem; }

    void przesunG();
    void przesunD();
    void draw(sf::RenderWindow& window);
};
