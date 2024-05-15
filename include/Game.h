#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Cannon.h"
#include "Ball.h"
#include "Block.h"
#include "NormalBlock.h"
#include "GameLevel.h"


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <sstream> // For string manipulation with float

/*
    Class acts as the game engine. Wrapper class
*/ 

class Game 
{
private:
    //variables
    //window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    bool endGame;

    //background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape limitLine;

    //instance of class Game Level
    GameLevel gamelevel;

    //game objects
    Cannon cannon;
    std::vector<Ball> balls;
    NormalBlock normalBlock;
    std::vector<Block*> blocks;

    //private functions
    void initializeVariables();
    void initializeWindow();
    void initializeBackground();
    void initializeText();

    //the red limit line
    void initializeLimitLine();

public:
    //constructor and destructor
    Game();
    virtual ~Game();

    //functions
    void updateEvent();
    void update(sf::Time dt);
    void render();

    //accessors: get variables from the class
    const bool running() const;

    void removeBock(Block* b);

    //functions for ball

};
#endif