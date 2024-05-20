#include "../include/ExtraBallBlock.h"

ExtraBallBlock::ExtraBallBlock(float x, float y)
    : Block(x, y) {
    this->blockStrength = 1;
    this->block.setFillColor(sf::Color::Yellow);
}

ExtraBallBlock::~ExtraBallBlock() {
    std::cout << "ExtraBallBlock destroyed" << std::endl;
}

void ExtraBallBlock::update(sf::RenderWindow &window) {
    // update
    this->blockText.setString("Ball");
} 
    


bool ExtraBallBlock::isExtraBall() const {
    return true;
}
