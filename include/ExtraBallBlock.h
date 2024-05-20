#ifndef EXTRABALLBLOCK_H
#define EXTRABALLBLOCK_H

#include "Block.h"

class ExtraBallBlock : public Block {
public:
    ExtraBallBlock(float x, float y);
    ~ExtraBallBlock();
    bool isExtraBall() const override;
    void update(sf::RenderWindow &window) override;
};

#endif // EXTRABALLBLOCK_H
