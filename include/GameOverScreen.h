#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @brief The GameOverScreen class represents the game over screen displayed at the end of the game.
 *
 * This class handles displaying the game over message and providing buttons for navigating back to the menu or exiting the game.
 */
class GameOverScreen {
private:
    sf::Font font;                  // Font used for text
    sf::Text gameOverText;          // "Game Over" text
    sf::RectangleShape backToMenuButton; // Button to go back to the menu
    sf::Text backToMenuButtonText;  // Text for the back to menu button
    sf::RectangleShape exitButton;  // Button to exit the game
    sf::Text exitButtonText;        // Text for the exit button
    sf::Texture backgroundTexture;       // Texture for the background
    sf::Sprite backgroundSprite;         // Sprite for the background


public:
    GameOverScreen();

    // Other methods
    void update(sf::RenderWindow& window);                // Updates the game over screen
    void render(sf::RenderWindow& window) const;          // Renders the game over screen
    bool isBackToMenuButtonClicked(const sf::Vector2i& mousePos) const; // Checks if the back to menu button is clicked
    bool isExitButtonClicked(const sf::Vector2i& mousePos) const;       // Checks if the exit button is clicked
};

#endif // GAME_OVER_SCREEN_H
