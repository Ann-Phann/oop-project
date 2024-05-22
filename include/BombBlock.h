#ifndef BOMBBLOCK_H
#define BOMBBLOCK_H

#include "Block.h"

/**
 * @brief The BombBlock class represents a special block in the game that acts as a bomb.
 *
 * This class is derived from the Block class and provides additional functionality
 * specific to bomb blocks.
 */
class BombBlock : public Block {
public:
    BombBlock(float x, float y, int level);
    ~BombBlock();

    // Getters
    bool isBomb() const override;

    // Other methods
    void update(sf::RenderWindow &window) override;
};

#endif // BOMBBLOCK_H
