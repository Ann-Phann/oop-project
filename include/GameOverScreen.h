#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>

class GameOverScreen {
public:
    GameOverScreen();
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window) const;
    bool isBackToMenuButtonClicked(const sf::Vector2i& mousePos) const;
    bool isExitButtonClicked(const sf::Vector2i& mousePos) const;

private:
    sf::Font font;
    sf::Text gameOverText;
    sf::RectangleShape backToMenuButton;
    sf::Text backToMenuButtonText;
    sf::RectangleShape exitButton;
    sf::Text exitButtonText;
};

#endif // GAME_OVER_SCREEN_H
