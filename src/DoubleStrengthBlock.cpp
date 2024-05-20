#include "../include/DoubleStrengthBlock.h"

DoubleStrengthBlock::DoubleStrengthBlock(float x, float y, int level)
    : Block(x, y) {
    this->block.setFillColor(sf::Color(255, 204, 153));
    this->blockStrength = level * 2;
    this->blockText.setString(std::to_string(blockStrength));
    this->blockText.setCharacterSize(40.f);
}


DoubleStrengthBlock::~DoubleStrengthBlock() {
    std::cout << "DoubleStrengthBlock destructor" << std::endl;
}