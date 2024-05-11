#include "Game.h"

//constructor and destructor
Game::Game()
{
    this->initializeVariables();
    this->initializeWindow();
}

Game::~Game()
{
    delete this->window;
}

//functions
void Game::updateEvent()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
        }
    }
}

void Game::update()
{
    this->updateEvent();
    
}
void Game:: render()
{
    //clear window (clear old frame)
    this->window->clear();

    //display frame in window
    this->window->display();
}

//privarte functions
void Game:: initializeVariables()
{
    this->window = nullptr;
}

void Game:: initializeWindow()
{
    this->videoMode.height = 720;
    this->videoMode.width = 1280;
    this->window = new sf::RenderWindow(videoMode, "SFML works!", sf::Style::Titlebar | sf::Style::Close);
}

//accessor
const bool Game:: running() const
{
    return this-> window->isOpen();
}