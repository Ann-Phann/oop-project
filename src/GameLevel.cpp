#include "../include/GameLevel.h"
#include "../include/NormalBlock.h"
#include "../include/ExtraBallBlock.h"
#include "../include/DoubleStrengthBlock.h"




GameLevel::GameLevel() : currentLevel(1) {
       // Load font
    if (!fontLevel.loadFromFile("assets/fonts/scoreFont.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    } else {
    //Set properties for pointText
        levelText.setFont(fontLevel);
        levelText.setString("Level: 1");  // Set the level to 10
        levelText.setCharacterSize(25);
        levelText.setFillColor(sf::Color::White);
        levelText.setPosition(50.f, 961.f);  // Position it above the score
        
        std::cout << "Level text initialized" << std::endl;
    }
   // Create array
   for (auto& row : blocks) {
        for (auto& block : row) {
            block = nullptr;
        }
    }
}

GameLevel::~GameLevel() {
    // Delete the blocks
    for (auto& row : blocks) {
        for (auto& block : row) {
            delete block;
        }
    }
}

void GameLevel::update(sf::RenderWindow &window) {
    // Update the cannon
    cannon.update(window);

    //Update the balls
    for (auto& ball : cannon.balls) {
        ball->update(window);
        reflectBall(*ball);
    }

    //   // Update the blocks
    for (auto& row : blocks) {
        for (auto& block : row) {
            if (block) {
                block->update(window);
                if (block->getIsDestroyed()) {
                    scoreboard.addScores();
                    if (block->isExtraBall()) {
                            cannon.reload(1); // Add one more ball to ammo
                        }
                    delete block;
                    block = nullptr;
                }
            }
        }
    }

    // Update the scoreboard
    scoreboard.updatePoints();

    // Update the level text
    updateLevelText();
}

void GameLevel::createNewRow() {
    // Shift rows down
    for (int i = ROWS - 1; i > 0; --i) {
        for (int j = 0; j < COLS; ++j) {
            blocks[i][j] = blocks[i - 1][j];
        }
    }

    // Determine the number of new blocks based on the current level
    int minBlocks, maxBlocks;
    if (currentLevel < 3) {
        minBlocks = 2;
        maxBlocks = 3;
    } else if (currentLevel < 7) {
        minBlocks = 3;
        maxBlocks = 4;
    } else {
        minBlocks = 4;
        maxBlocks = 6;
    }

    // int numNewBlocks = minBlocks + rand() % (maxBlocks - minBlocks + 1);

    // // Initialize the new top row with null pointers
    // std::fill(blocks[0].begin(), blocks[0].end(), nullptr);

    // // Create a list of available column indices
    // std::vector<int> availableCols(COLS);
    // for (int i = 0; i < COLS; ++i) {
    //     availableCols[i] = i;
    // }
    // std::random_shuffle(availableCols.begin(), availableCols.end());

    // // Place one ExtraBallBlock
    // blocks[0][availableCols[0]] = new ExtraBallBlock(availableCols[0] * BLOCK_WIDTH, 0);

    // // Place the remaining NormalBlocks
    // for (int i = 1; i < numNewBlocks; ++i) {
    //     blocks[0][availableCols[i]] = new NormalBlock(availableCols[i] * BLOCK_WIDTH, 0, currentLevel);
    // }

    int numNewBlocks = minBlocks + rand() % (maxBlocks - minBlocks + 1);

    // Initialize the new top row with null pointers
    std::fill(blocks[0].begin(), blocks[0].end(), nullptr);

    // Create a list of available column indices
    std::vector<int> availableCols(COLS);
    for (int i = 0; i < COLS; ++i) {
        availableCols[i] = i;
    }
    std::random_shuffle(availableCols.begin(), availableCols.end());

    // Place one ExtraBallBlock if needed
    bool extraBallBlockAdded = false;
    if (rand() % 1 == 0) {
        blocks[0][availableCols.back()] = new ExtraBallBlock(availableCols.back() * BLOCK_WIDTH, 0);
        availableCols.pop_back();
        extraBallBlockAdded = true;
    }

    // Determine if a DoubleStrengthBlock should be added
    bool doubleStrengthBlockAdded = false;
    if (currentLevel >= 3 && (currentLevel - 3) % 5 == 0) {
        blocks[0][availableCols.back()] = new DoubleStrengthBlock(availableCols.back() * BLOCK_WIDTH, 0, currentLevel);
        availableCols.pop_back();
        doubleStrengthBlockAdded = true;
    }

    // Place the remaining NormalBlocks
    for (int i = 0; i < numNewBlocks - extraBallBlockAdded - doubleStrengthBlockAdded; ++i) {
        blocks[0][availableCols.back()] = new NormalBlock(availableCols.back() * BLOCK_WIDTH, 0, currentLevel);
        availableCols.pop_back();
    }

    updateBlockPositions();
}

void GameLevel::updateBlockPositions() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (blocks[i][j]) {
                blocks[i][j]->setPosition(j * BLOCK_WIDTH, i * BLOCK_HEIGHT);
            }
        }
    }
}

void GameLevel::render(sf::RenderTarget& target) const {
    // Render the cannon
    cannon.render(target);

    
    // Render the balls
    for (const auto& ball : cannon.balls) {
        ball->render(target);
    }

    // Render block shapes
    for (auto& row : blocks) {
        for (auto& block : row) {
            if (block) {
                target.draw(block->getShape());
            }
        }
    }
    // for (const auto& block : blocks) {
    //     std::cout << "Rendering block shape" << std::endl;
    //     target.draw(block.getShape());
    // }

    // Render block texts
    for (auto& row : blocks) {
        for (auto& block : row) {
            if (block) {
                target.draw(block->getText());
            }
        }
    }
    // for (const auto& block : blocks) {
    //     std::cout << "Rendering block text" << std::endl;
    //     target.draw(block.getText());
    // }

    // Render the scoreboard
    std::cout << "Rendering scoreboard" << std::endl;
    scoreboard.render(target);

    std::cout << "Rendering level text" << std::endl;
    target.draw(levelText);
    
}

// Shoot the cannon
void GameLevel::shootCannon() {
    cannon.handleInput();
    sf::Time deltaTime = clock.restart();
    cannon.updateShooting(deltaTime);
}

// Reflect the ball off the blocks
void GameLevel::reflectBall(Ball& ball) {
    for (const auto& row : blocks) {
        for (const auto& block : row) {
            if (block) {
                block->reflectBall(ball); 
            }
        }
    }
}

int GameLevel::getCurrentLevel() const {
    return currentLevel;
}

void GameLevel::setCurrentLevel() {
    currentLevel++;
}

void GameLevel::updateLevelText() {
    int currentLevel = getCurrentLevel();
    levelText.setString("Level : " + std::to_string(currentLevel));
}


Cannon& GameLevel::getCannon() {
    return cannon;
}

//check win lose condition
bool GameLevel::checkLoseCondition(float limitLineY) const {
    for (const auto& row : blocks) {
        for (const auto& block : row) {
            if (block && block->getShape().getPosition().y + block->getShape().getSize().y >= limitLineY) {
                return true;
            }
        }
    }
    return false;
}

bool GameLevel::checkWinCondition() const {
    return currentLevel >= 12;
}