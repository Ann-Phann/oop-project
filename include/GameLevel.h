#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Cannon.h"
#include "Block.h"
#include "Ball.h"
#include "Scoreboard.h"

class GameLevel : public GameObject {
private:
    int currentLevel;

    Cannon cannon;
    sf::Clock clock;
    std::vector<Block> blocks;
    //Block block;
    std::vector<Ball> balls;
    Scoreboard scoreboard;

public:
    GameLevel();

    //generate blocks for the current level
    void generateBlocks();

    void update(sf::RenderWindow &window) override;
    void render(sf::RenderTarget& target) const override;
    void shootCannon();
    void reflectBall(Ball& ball);

    int getCurrentLevel() const;
};

#endif // GAMELEVEL_H
