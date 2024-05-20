#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Cannon.h"
#include "Block.h"
#include "Ball.h"
#include "Scoreboard.h"
#include <array>
#include <algorithm> // For std::random_shuffle
#include "Constants.h"


class GameLevel : public GameObject {
private:

    int currentLevel;

    Cannon cannon;
    sf::Clock clock;
    //std::vector<Block> blocks;

    std::vector<Ball> balls;
    Scoreboard scoreboard;

    sf::Font fontLevel;
    sf::Text levelText;

public:
    GameLevel();
    ~GameLevel();

    std::array<std::array<Block*, COLS>, ROWS> blocks;


    //generate blocks for the current level
    void update(sf::RenderWindow &window) override;
    void render(sf::RenderTarget& target) const override;
    void shootCannon();

    void reflectBall(Ball& ball);
    
    //update new level
    void updateLevelText();
    //getter and setter
    int getCurrentLevel() const;
    void setCurrentLevel();

    void createNewRow();
    void updateBlockPositions();
    Cannon& getCannon(); // Getter for Cannon object

    //check win lose
    bool checkLoseCondition(float limitLineY) const;
    bool checkWinCondition() const;
};

#endif // GAMELEVEL_H