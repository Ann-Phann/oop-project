#include "../include/BombBlock.h"

BombBlock::BombBlock(float x, float y, int level)
    : Block(x, y) {
    this->blockStrength = level;
    this->blockText.setString(std::to_string(blockStrength));
    this->block.setFillColor(sf::Color(192,192,192));
}

BombBlock::~BombBlock() {
    std::cout << "BombBlock destroyed" << std::endl;
}

bool BombBlock:: isBomb() const
{
    return true;
}

void BombBlock:: update(sf::RenderWindow &window)
{
    this->blockText.setString("Bomb: " + std::to_string(blockStrength));
}

