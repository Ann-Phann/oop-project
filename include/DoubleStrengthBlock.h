#ifndef DOUBLESTRENGTHBLOCK_H
#define DOUBLESTRENGTHBLOCK_H

#include "Block.h"

/**
 * @brief The DoubleStrengthBlock class represents a special block in the game that has double the strength.
 *
 * This class is derived from the Block class and provides additional functionality
 * specific to double strength blocks.
 */
class DoubleStrengthBlock : public Block {
public:
    DoubleStrengthBlock(float x, float y, int level);
    ~DoubleStrengthBlock();
};

#endif // DOUBLESTRENGTHBLOCK_H
