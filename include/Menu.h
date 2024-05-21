#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Menu {
private:
    sf::Font font;
    sf::Text title;
    sf::RectangleShape startButton;
    sf::Text startButtonText;

    void initializeMenu();

public:
    Menu();
    void render(sf::RenderTarget& target) const;
    bool handleInput(sf::RenderWindow& window);
};

#endif // MENU_H
