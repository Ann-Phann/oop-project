#include "../include/GameWindow.h"

GameWindow::GameWindow ()
{
    this->initializeVariables();
    this->initializeWindow();
    this->initializeBackground();
    this->initializeText();
    this->initializeLimitLine();
}

GameWindow::~GameWindow()
{
    delete this->window;
}

//privarte functions
void GameWindow::initializeVariables()
{
    this->window = nullptr;    
}

void GameWindow:: initializeWindow()
{
    this->videoMode.height = 1024;
    this->videoMode.width = 1280;
    this->window = new sf::RenderWindow(videoMode, "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void GameWindow::initializeBackground()
{
    // Load a sprite to display
    if(!backgroundTexture.loadFromFile("assets/images/blue.jpg"))
    {
        std::cout << "Failed to load background image!" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
    }
}

void GameWindow::initializeText()
{
    //Create Heading to display
    if (!font.loadFromFile("assets/fonts/font.ttf"))
    {
        std::cout << "Failed to load background image!" << std::endl;
    } else 
    {
        text.setFont(font);
        text.setString("ICE Smash");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);  
        text.setPosition(100, 20);
    }  
}

void GameWindow::initializeLimitLine()
{
    // initialize Limit Line
    this->limitLine.setSize(sf::Vector2f(1280.f, 10.f));
    this->limitLine.setFillColor(sf::Color::Red);
    this->limitLine.setPosition(0.f, 911.f); // Position gun on top of the base

}

//functions
void GameWindow::updateEvent()
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

void GameWindow::update()
{
    if(!window->isOpen()) return;
    
    this->updateEvent();

    // call the shootCannon function
    gameLevel.shootCannon();
    gameLevel.update(*this->window);


}

void GameWindow::render()
{
    //clear window (clear old frame)
    this->window->clear();

    //draw background
    this->window->draw(this->backgroundSprite);
    this->window->draw(this->text);
    this->window->draw(this->limitLine);

    //gameLevel.update(*this->window);
    gameLevel.render(*this->window);
    
    //display frame in window
    this->window->display();
}

//accessor
const bool GameWindow::running() const
{
    return this-> window->isOpen();
}