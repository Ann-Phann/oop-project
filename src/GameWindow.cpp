#include "../include/GameWindow.h"

// Constructor
GameWindow::GameWindow() : gameLevel(nullptr), gameState(GameState::MENU), leftMouseClicked(false), menuMouseClicked(false) {
    this->initializeVariables();
    this->initializeWindow();
    this->initializeBackground();
    this->initializeLimitLine();
    this->resetGameLevel(); // Initialize the game level with initial rows if needed
}

// Destructor
GameWindow::~GameWindow() {
    delete this->window;
}

// Private functions

// Initializes the game variables
void GameWindow::initializeVariables() {
    this->window = nullptr;
}

// Initializes the game window
void GameWindow::initializeWindow() {
    this->videoMode.height = 1024;
    this->videoMode.width = 1280;
    this->window = new sf::RenderWindow(videoMode, "Ice Smash!", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

// Initializes the background
void GameWindow::initializeBackground() {
    if (!backgroundTexture.loadFromFile("assets/images/blue.jpg")) {
        std::cout << "Failed to load background image!" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
    }
}

// Initializes the red limit line
void GameWindow::initializeLimitLine() {
    this->limitLine.setSize(sf::Vector2f(1280.f, 10.f));
    this->limitLine.setFillColor(sf::Color::Red);
    this->limitLine.setPosition(0.f, 911.f);
}

// Resets the game level
void GameWindow::resetGameLevel() {
    if (gameLevel != nullptr) {
        delete gameLevel;
    }
    gameLevel = new GameLevel();
    gameLevel->createNewRow(); // Ensure the first row of blocks is created
}

// Public functions

// Updates and processes events
void GameWindow::updateEvent() {
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if (this->ev.mouseButton.button == sf::Mouse::Left) {
                    menuMouseClicked = true;
                    leftMouseClicked = true;
                    clickClock.restart();
                }
                break;
        }
    }
}

// Updates the game state
void GameWindow::update() {
    if (!window->isOpen()) return;

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
                gameWin.setTotalPoints(gameLevel->getTotalPoints());
                gameState = GameState::GAME_WIN;
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
        case GameState::GAME_WIN:
            gameWin.update(*window);
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

// Renders the game state
void GameWindow::render() {
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
        case GameState::GAME_WIN:
            gameWin.render(*this->window);
            break;
    }

    // Display frame in window
    this->window->display();
}

// Checks if the window is running
const bool GameWindow::running() const {
    return this->window->isOpen();
}
