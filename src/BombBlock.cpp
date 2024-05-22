#include "../include/BombBlock.h"
#include <iostream>

// Constructor
BombBlock::BombBlock(float x, float y, int level)
    : Block(x, y) {
    // Initialize the bomb block
    this->blockStrength = level;
    this->blockText.setString(std::to_string(blockStrength));
    this->block.setFillColor(sf::Color(192, 192, 192));
}

BombBlock::~BombBlock() {
    std::cout << "BombBlock destroyed" << std::endl;
}

// Getters
bool BombBlock::isBomb() const {
    return true;
}

// Other methods
void BombBlock::update(sf::RenderWindow &window) {
    this->blockText.setString("Bomb: " + std::to_string(blockStrength));
}
