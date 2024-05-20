#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameLevel.h"

class GameWindow {
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    GameLevel gameLevel;

    //background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape limitLine;

    bool leftMouseClicked = false; // To track space key press state
        sf::Clock clickClock; // Clock to measure delay since user click


     //private functions
    void initializeVariables();
    void initializeWindow();
    void initializeBackground();
    void initializeText();

    //the red limit line
    void initializeLimitLine();

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
