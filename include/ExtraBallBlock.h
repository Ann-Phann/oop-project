#ifndef EXTRABALLBLOCK_H
#define EXTRABALLBLOCK_H

#include "Block.h"

/**
 * @brief The ExtraBallBlock class represents a special block in the game that grants an extra ball.
 *
 * This class is derived from the Block class and provides additional functionality
 * specific to extra ball blocks.
 */
class ExtraBallBlock : public Block {
public:
    ExtraBallBlock(float x, float y);
    ~ExtraBallBlock();

    // Getters
    bool isExtraBall() const override;

    // Other methods
    void update(sf::RenderWindow &window) override;
};

#endif // EXTRABALLBLOCK_H
