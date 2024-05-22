#include "../include/ExtraBallBlock.h"
#include <iostream>

// Constructor
ExtraBallBlock::ExtraBallBlock(float x, float y)
    : Block(x, y) {
    // Set the block's color and strength
    this->blockStrength = 1;
    this->block.setFillColor(sf::Color::Yellow);
}

ExtraBallBlock::~ExtraBallBlock() {
    std::cout << "ExtraBallBlock destroyed" << std::endl;
}

// Getters
bool ExtraBallBlock::isExtraBall() const {
    return true;
}

// Other methods
void ExtraBallBlock::update(sf::RenderWindow &window) {
    this->blockText.setString("Ball");
}
