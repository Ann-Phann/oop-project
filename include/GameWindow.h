#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameLevel.h"
#include "MenuScreen.h"
#include "GameOverScreen.h"
#include "GameWinScreen.h"
#include "Scoreboard.h"
#include "Constants.h"

enum class GameState { MENU, PLAYING, HIGH_SCORES, GAME_OVER, GAME_WIN };

/**
 * @brief The GameWindow class manages the main game window and game state transitions.
 *
 * This class handles the initialization of the window, event processing, game updates,
 * and rendering for different game states.
 */
class GameWindow {
private:
    // Variables
    sf::RenderWindow* window;             // Pointer to the SFML render window
    sf::VideoMode videoMode;              // Video mode for the window
    sf::Event ev;                         // Event for handling input
    sf::Font font;                        // Font for displaying text
    sf::Text text;                        // Text displayed in the window
    sf::Texture backgroundTexture;        // Texture for the background
    sf::Sprite backgroundSprite;          // Sprite for the background
    sf::RectangleShape limitLine;         // Red limit line
    GameLevel* gameLevel;                 // GameLevel instance
    MenuScreen menuScreen;                // MenuScreen instance
    GameState gameState;                  // Current game state
    GameOverScreen gameOver;              // GameOver instance
    GameWinScreen gameWin;                // GameWin instance
    std::string playerName;               // Player's name

    bool leftMouseClicked;                // Flag to track left mouse button click in playing state
    bool menuMouseClicked;                // Flag to track left mouse button click in menu state
    sf::Clock clickClock;                 // Clock to measure delay since user click

    // Private functions
    void initializeVariables();           // Initializes the game variables
    void initializeWindow();              // Initializes the game window
    void initializeBackground();          // Initializes the background
    void initializeLimitLine();           // Initializes the red limit line

    // New function to reset the game level
    void resetGameLevel();                // Resets the game level

public:
    GameWindow();
    ~GameWindow();

    // Other methods
    void updateEvent();                   // Updates and processes events
    void update();                        // Updates the game state
    void render();                        // Renders the game state
    const bool running() const;           // Checks if the window is running
};

#endif // GAMEWINDOW_H
