#include "../include/GameWindow.h"

GameWindow::GameWindow() : gameLevel(nullptr), gameState(GameState::MENU), leftMouseClicked(false), menuMouseClicked(false)
{
    this->initializeVariables();
    this->initializeWindow();
    this->initializeBackground();
    this->initializeLimitLine();
    // Initialize the game level with initial rows if needed
        this->resetGameLevel();

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
    this->window = new sf::RenderWindow(videoMode, "Ice Smash!", sf::Style::Titlebar | sf::Style::Close);
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
                    menuMouseClicked = true;
                    leftMouseClicked = true;
                    clickClock.restart();
                }
                break;
        }
    }
}

void GameWindow::update()
{
    if(!window->isOpen()) return;
    
    this->updateEvent();

    switch (gameState) {
        case GameState::MENU:
            menuScreen.update(*window);
            if (menuMouseClicked) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (menuScreen.isPlayButtonClicked(mousePos)) {
                    resetGameLevel();  // Reset the game level when starting a new game
                    gameState = GameState::PLAYING;
                } else if (menuScreen.isHighScoresButtonClicked(mousePos)) {
                    gameState = GameState::HIGH_SCORES;
                } else if (menuScreen.isExitButtonClicked(mousePos)) {
                    window->close();
                }
                menuMouseClicked = false;
                leftMouseClicked = false;

            }
            break;
        case GameState::PLAYING:
            // Call the shootCannon function
            if (leftMouseClicked) {
                gameLevel->shootCannon();
            }
            

            // Update the game level
            gameLevel->update(*this->window);

            // Check win condition
            if (gameLevel->checkWinCondition()) {
                std::cout << "You win!" << std::endl;
                window->close();
                return;
            }

            // Check lose condition
             if (gameLevel->checkLoseCondition(limitLine.getPosition().y)) {
                gameState = GameState::GAME_OVER;
                return;
            }
            // Check if all balls have touched the bottom edge of the screen, only if the user has clicked and 5 seconds have passed
            if (leftMouseClicked && clickClock.getElapsedTime().asSeconds() >= 2.0f) {
                if (gameLevel->getCannon().checkBallsTouchBottom(window->getSize().y)) {
                    // Up the level
                    gameLevel->setCurrentLevel();
                    // Create a new row of blocks
                    gameLevel->createNewRow();
                    // Reload ammo or any other actions you want to perform
                    gameLevel->getCannon().reload(0);
                    leftMouseClicked = false; // Reset the flag after handling the condition
                }
            }
            break;
        case GameState::HIGH_SCORES:
            // Handle high scores screen logic
            break;
        case GameState::GAME_OVER:
            gameOver.update(*window);
            if (menuMouseClicked) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (gameOver.isBackToMenuButtonClicked(mousePos)) {
                    gameState = GameState::MENU;
                } else if (gameOver.isExitButtonClicked(mousePos)) {
                    window->close();
                }
                menuMouseClicked = false;
                leftMouseClicked = false;
            }
            break;
    }


}

void GameWindow::render()
{
    // Clear window (clear old frame)
    this->window->clear();

    switch (gameState) {
        case GameState::MENU:
            menuScreen.render(*this->window);
            break;
        case GameState::PLAYING:
            // Draw background
            this->window->draw(this->backgroundSprite);
            this->window->draw(this->text);
            this->window->draw(this->limitLine);

            // Render the game level
            gameLevel->render(*this->window);
            break;
        case GameState::HIGH_SCORES:
            // Render high scores screen
            break;
        case GameState::GAME_OVER:
            gameOver.render(*this->window);
            break;
    }

    // Display frame in window
    this->window->display();
}

//accessor
const bool GameWindow::running() const
{
    return this-> window->isOpen();
}


void GameWindow::resetGameLevel() {
    if (gameLevel != nullptr) {
        delete gameLevel;
    }
    gameLevel = new GameLevel();
    gameLevel->createNewRow();  // Ensure the first row of blocks is created
}