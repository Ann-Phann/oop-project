#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * @brief The Menu class represents the main menu screen of the game.
 *
 * This class handles the display and interaction with the main menu,
 * including rendering the menu and handling user input.
 */
class Menu {
private:
    sf::Font font;                 // Font used for the menu text
    sf::Text title;                // Title text for the menu
    sf::RectangleShape startButton; // Start button shape
    sf::Text startButtonText;      // Text for the start button

    // Private functions
    void initializeMenu();         // Initializes the menu components

public:
    Menu();

    // Other methods
    void render(sf::RenderTarget& target) const; // Renders the menu
    bool handleInput(sf::RenderWindow& window);  // Handles input in the menu
};

#endif // MENU_H
