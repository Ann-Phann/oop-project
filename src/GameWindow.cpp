#include "../include/GameWindow.h"

GameWindow::GameWindow ()
{
    this->initializeVariables();
    this->initializeWindow();
    this->initializeBackground();
    this->initializeText();
    this->initializeLimitLine();
    // Initialize the game level with initial rows if needed
    gameLevel.createNewRow();
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
        std::cout << "Failed to load game name!" << std::endl;
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
            case sf::Event::MouseButtonPressed:
                if (this->ev.mouseButton.button == sf::Mouse::Left)
                {
                    leftMouseClicked = true;
                    clickClock.restart(); // Restart the clock
                }
                break;
        }
    }
}

void GameWindow::update()
{
    if(!window->isOpen()) return;
    
    this->updateEvent();

    // // Handle input for creating a new row when the space bar is pressed
    //  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    //         if (!spacePressed) {
    //             gameLevel.createNewRow();
    //             spacePressed = true; // Set flag to true when space is pressed
    //         }
    //     } else {
    //         spacePressed = false; // Reset flag when space is released
    //     }

    

    // call the shootCannon function
    gameLevel.shootCannon();
    // Handle input

    gameLevel.update(*this->window);
    
    // Check if all balls have touched the bottom edge of the screen, only if the user has clicked and 5 seconds have passed
    if (leftMouseClicked && clickClock.getElapsedTime().asSeconds() >= 1.0f) {
        if (gameLevel.getCannon().checkBallsTouchBottom(window->getSize().y)) {
            
            // Up the level
            gameLevel.setCurrentLevel();
            // Create a new row of blocks
            gameLevel.createNewRow();
            // Reload ammo or any other actions you want to perform
            gameLevel.getCannon().reload(0);
            leftMouseClicked = false; // Reset the flag after handling the condition
        }
    }

    //check win lose condition
        // Check win condition
    if (gameLevel.checkWinCondition()) {
        std::cout << "You win!" << std::endl;
        window->close();
        return;
    }

    // Check lose condition
    if (gameLevel.checkLoseCondition(limitLine.getPosition().y)) {
        std::cout << "You lose!" << std::endl;
        window->close();
        return;
    }


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