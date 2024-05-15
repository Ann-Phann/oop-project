#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <math.h>
#include <vector>
#include <iostream>
#include <memory>

#include "Ball.h"
#include "Cannon.h"
#include "Block.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class GameLevel 
{
private:

    //game objects
    Cannon* cannon;
    std::vector<std::vector<Block*>>blocks;
    std::vector<Ball*> balls;

    //private member data
    int levelNumber;
    bool isLevelCompleted;
    void initializeGameLevel();

public:
    //constructor and destructor
    GameLevel();
    ~GameLevel();

    void loadNewLevel(int level);
    void update();
    
};
#endif