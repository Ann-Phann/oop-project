#ifndef NORMALBLOCK_H
#define NORMALBLOCK_H

#include "Block.h"

/**
 * @brief The NormalBlock class represents a standard block in the game.
 *
 * This class is derived from the Block class and provides functionality specific
 * to normal blocks, including setting the block's strength based on the level.
 */
class NormalBlock : public Block {
public:
    NormalBlock(float x, float y, int level);
    ~NormalBlock();
};

#endif // NORMALBLOCK_H
