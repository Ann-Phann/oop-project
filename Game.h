#ifndef GAME_H
#define GAME_H
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

    //private functions
    void initializeVariables();
    void initializeWindow();

public:
    //constructor and destructor
    Game();
    virtual ~Game();

    //functions
    void updateEvent();
    void update();
    void render();

    //accessors
    const bool running() const;
};
#endif