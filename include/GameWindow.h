#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameLevel.h"
#include "MenuScreen.h"
#include "GameOverScreen.h"

#include "Constants.h"

enum class GameState { MENU, PLAYING, HIGH_SCORES, GAME_OVER };


class GameWindow {
private:
       // Variables
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    sf::Font font;
    sf::Text text;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape limitLine;
    GameLevel* gameLevel; // GameLevel instance
    MenuScreen menuScreen; // MenuScreen instance
    GameState gameState; // Current game state
    GameOverScreen gameOver; // GameOver instance

    bool leftMouseClicked; // Flag to track left mouse button click in playing state
    bool menuMouseClicked; // Flag to track left mouse button click in menu state
    sf::Clock clickClock; // Clock to measure delay since user click


     //private functions
    void initializeVariables();
    void initializeWindow();
    void initializeBackground();

    //the red limit line
    void initializeLimitLine();

    // New function to reset the game level
    void resetGameLevel();

public:
    GameWindow();
    ~GameWindow();

    //functions
    void updateEvent();
    void update();
    void render();
    const bool running() const;

};

#endif // GAMEWINDOW_H
