#ifndef GAME_WIN_SCREEN_H
#define GAME_WIN_SCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @brief The GameWinScreen class represents the screen displayed when the player wins the game.
 *
 * This class handles displaying the win message, total points, and buttons for navigating back to the menu or exiting the game.
 */
class GameWinScreen {
private:
    sf::Font font;                       // Font used for the win screen text
    sf::Text winText;                    // "You Win" text
    sf::Text totalPointsText;            // Text displaying total points
    sf::RectangleShape backToMenuButton; // Button to go back to the menu
    sf::Text backToMenuButtonText;       // Text for the back to menu button
    sf::RectangleShape exitButton;       // Button to exit the game
    sf::Text exitButtonText;             // Text for the exit button
    sf::Texture backgroundTexture;       // Texture for the background
    sf::Sprite backgroundSprite;         // Sprite for the background

public:
    GameWinScreen();

    // Other methods
    void update(sf::RenderWindow& window);                // Updates the win screen
    void render(sf::RenderWindow& window) const;          // Renders the win screen
    bool isBackToMenuButtonClicked(const sf::Vector2i& mousePos) const; // Checks if the back to menu button is clicked
    bool isExitButtonClicked(const sf::Vector2i& mousePos) const;       // Checks if the exit button is clicked
    void setTotalPoints(int points);                      // Sets the total points
};

#endif // GAME_WIN_SCREEN_H
