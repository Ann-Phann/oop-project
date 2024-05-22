#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <SFML/Graphics.hpp>

/**
 * @brief The MenuScreen class represents the main menu screen of the game.
 *
 * This class handles the display and interaction with the main menu,
 * including rendering the menu and handling user input.
 */
class MenuScreen {
private:
    sf::Texture backgroundTexture;  // Texture for the background
    sf::Sprite backgroundSprite;    // Sprite for the background
    sf::Font font;                  // Font for the menu text
    sf::Text title;                 // Title text for the menu
    sf::Text playButton;            // Play button text
    sf::Text highScoresButton;      // High scores button text
    sf::Text exitButton;            // Exit button text

    sf::Color defaultColor;         // Default color for buttons
    sf::Color hoverColor;           // Hover color for buttons

    // Private functions
    void initializeText(sf::Text &text, const std::string &str, float x, float y); // Initializes text components

public:
    MenuScreen();

    // Other methods
    void update(sf::RenderWindow &window);            // Updates the menu screen
    void render(sf::RenderTarget& target) const;      // Renders the menu screen
    bool isPlayButtonClicked(sf::Vector2i mousePos) const;       // Checks if the play button is clicked
    bool isHighScoresButtonClicked(sf::Vector2i mousePos) const; // Checks if the high scores button is clicked
    bool isExitButtonClicked(sf::Vector2i mousePos) const;       // Checks if the exit button is clicked
};

#endif // MENUSCREEN_H
