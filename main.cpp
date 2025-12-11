#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Game.h"
#include "GameState.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu");
    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    menu.przesunG();

                if (event.key.code == sf::Keyboard::Down)
                    menu.przesunD();

                if (event.key.code == sf::Keyboard::Enter)
                {
                    if (menu.getSelectedItem() == 0)
                    {
                        window.close();
                        Game g;
                        g.run();
                        return 0;
                    }

                    if (menu.getSelectedItem() == 1)
                    {
                        Paletka p(0, 0, 0, 0, 0);
                        Pilka b(0, 0, 0, 0, 0);
                        std::vector<Brick> bricks;

                        GameState state(p, b, bricks);

                        if (state.loadFromFile("zapis.txt"))
                        {
                            window.close();
                            Game g;
                            g.applyState(state);
                            g.run();
                            return 0;
                        }
                        else
                        {
                            std::cout << "Brak zapisu!\n";
                        }
                    }

                    if (menu.getSelectedItem() == 3)
                        window.close();
                }
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}
