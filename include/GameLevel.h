#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <iostream>
#include <vector>
#include <array>
#include <algorithm> // For std::random_shuffle
#include "GameObject.h"
#include "Cannon.h"
#include "Block.h"
#include "Ball.h"
#include "Scoreboard.h"
#include "Constants.h"

/**
 * @brief The GameLevel class manages the game levels, including blocks, cannon, balls, and score.
 *
 * This class handles the creation, updating, rendering, and destruction of game levels.
 */
class GameLevel : public GameObject {
private:
    int currentLevel;                // The current game level
    Cannon cannon;                   // The cannon object
    sf::Clock clock;                 // Clock for timing shots
    std::vector<Ball> balls;         // Vector of balls in the game
    Scoreboard scoreboard;           // Scoreboard object
    sf::Font fontLevel;              // Font for level text
    sf::Text levelText;              // Text displaying the current level
    sf::Text numBallText;            // Text displaying the number of balls
    bool isMouseEnabled;             // Flag to enable/disable mouse input

    std::array<std::array<Block*, COLS>, ROWS> blocks; // 2D array of blocks

    // Private functions
    void updateLevelText();            // Updates the level text
    void updateNumBallText();          // Updates the number of balls text
    void updateBlockPositions();       // Updates positions of blocks
    void reflectBall(Ball& ball);      // Reflects the ball off the blocks

    // Function for bomb to destroy whole row
    void rowDestroy(std::array<std::array<Block*, COLS>, ROWS>& blocks, int row);

public:
    GameLevel();
    ~GameLevel();

    // Getter and setter
    int getCurrentLevel() const;         // Gets the current level
    void setCurrentLevel();              // Sets the current level
    Cannon& getCannon();                 // Getter for Cannon object
    int getTotalPoints();                // Gets the total points

    // Other methods
    void update(sf::RenderWindow &window) override; // Updates the game level
    void render(sf::RenderTarget& target) const override; // Renders the game level
    void shootCannon();                 // Shoots the cannon
    void createNewRow();                // Creates a new row of blocks
    bool checkLoseCondition(float limitLineY) const; // Checks if the game is lost
    bool checkWinCondition() const;                  // Checks if the game is won
};

#endif // GAMELEVEL_H
