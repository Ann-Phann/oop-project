#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/GameLevel.h"
#include "../include/Scoreboard.h"
#include "../include/Constants.h"
#include "../include/NormalBlock.h"
#include "../include/ExtraBallBlock.h"
#include "../include/DoubleStrengthBlock.h"
#include "../include/BombBlock.h"
#include "../include/GameObject.h"
#include "../include/Cannon.h"
#include "../include/Ball.h"
#include "../include/Block.h"
#include <vector>
#include <array>


void testUpLevel(GameLevel& gameLevel) {
    int initialLevel = gameLevel.getCurrentLevel();
    gameLevel.setCurrentLevel();
    int newLevel = gameLevel.getCurrentLevel();
    std::cout << "Test Up Level: " << ((newLevel == initialLevel + 1) ? "Passed" : "Failed") << std::endl;
}

void testAddScore(Scoreboard& scoreboard) {
    int initialScore = scoreboard.getScores();
    scoreboard.addScores(1);
    int newScore = scoreboard.getScores();
    std::cout << "Test Add Score: " << ((newScore == initialScore + 100) ? "Passed" : "Failed") << std::endl;
}


void testShowTotalPoints(Scoreboard& scoreboard) {
    int totalPoints = scoreboard.getScores();
    scoreboard.updatePoints();
    std::string pointsText = "Scores: " + std::to_string(totalPoints);
    std::cout << "Test Show Total Points: " << ((scoreboard.getScores() == totalPoints) ? "Passed" : "Failed") << std::endl;
}

int main() {
    // Create game objects
    GameLevel gameLevel;
    Scoreboard scoreboard;

    // Run the tests
    testUpLevel(gameLevel);
    testAddScore(scoreboard);
    testShowTotalPoints(scoreboard);

    return 0;
}

// Compile command:
// g++ -std=c++17 -Wall -I"D:\SFML\64\SFML-2.6.1-mingw-64-bit\SFML-2.6.1\include" -L"D:\SFML\64\SFML-2.6.1-mingw-64-bit\SFML-2.6.1\lib" -o test_game test/TestGame.cpp src/GameLevel.cpp src/Scoreboard.cpp src/Cannon.cpp src/Ball.cpp src/Block.cpp src/NormalBlock.cpp src/ExtraBallBlock.cpp src/DoubleStrengthBlock.cpp src/BombBlock.cpp src/GameObject.cpp -lsfml-graphics -lsfml-window -lsfml-system
// ./test_game