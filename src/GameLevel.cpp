#include "../include/GameLevel.h"
#include <SFML/Graphics/Shape.hpp>

void GameLevel::generateBlocks() {
     //clear the array before generating new blocks
    blocks.clear();
    // add blocks to the vector
    for (int i = 0; i < 6; i++) {
        Block block(213*i, 140, 213, 140, 10); // Create a new Block object
        block.setColor(sf::Color::Red); // Set the color of the block to red (for now
        blocks.push_back(block); // Add it to the blocks vector
    }
    std::cout << "Total blocks created: " << blocks.size() << std::endl;

}

GameLevel::GameLevel() {
    currentLevel = 1;
    generateBlocks();

}

int GameLevel::getCurrentLevel() const {
    return currentLevel;
}

void GameLevel::update(sf::RenderWindow &window) {
    // Update the cannon
    cannon.update(window);

    //for balls
    for (auto& ball : cannon.balls) {
        ball->update(window);
        reflectBall(*ball);
    }

    //for blocks
    for (auto it = blocks.begin(); it != blocks.end(); ) {
        it->update(window);
        if (it->getIsDestroyed()) {
            scoreboard.addScores();
            it = blocks.erase(it);
        } else {
            ++it;
        }
    }

    // Update the scoreboard
    scoreboard.updatePoints();

}

void GameLevel::render(sf::RenderTarget& target) const {
    // Render the cannon
    cannon.render(target);
    
    // Render the balls
    for (const auto& ball : cannon.balls) {
        ball->render(target);
    }

    // Render block shapes
    for (const auto& block : blocks) {
        std::cout << "Rendering block shape" << std::endl;
        target.draw(block.getShape());
    }

    // Render block texts
    for (const auto& block : blocks) {
        std::cout << "Rendering block text" << std::endl;
        target.draw(block.getText());
    }

    // Render the scoreboard
    std::cout << "Rendering scoreboard" << std::endl;
    scoreboard.render(target);
    
}

// Shoot the cannon
void GameLevel::shootCannon() {
    cannon.handleInput();
    sf::Time deltaTime = clock.restart();
    cannon.updateShooting(deltaTime);
}

// Reflect the ball off the blocks
void GameLevel::reflectBall(Ball& ball) {
   for (auto& block : blocks) {
        block.reflectBall(ball); 
    }
}






