#include "../include/NormalBlock.h"

NormalBlock::NormalBlock(float x, float y, int level)
    : Block(x, y) {
    this->blockStrength = level;
    this->blockText.setString(std::to_string(blockStrength));
}

NormalBlock::~NormalBlock() {
    std::cout << "NormalBlock destroyed" << std::endl;
}