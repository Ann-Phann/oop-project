#ifndef NORMALBLOCK_H
#define NORMALBLOCK_H

#include "Block.h"

class NormalBlock : public Block {
public:
    NormalBlock(float x, float y, int level);
    ~NormalBlock();
};

#endif // NORMALBLOCK_H
