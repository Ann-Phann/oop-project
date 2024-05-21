#ifndef BOMBBLOCK_H
#define BOMBBLOCK_H

#include "Block.h"

class BombBlock : public Block {
public:
    BombBlock(float x, float y, int level);
    ~BombBlock();
    
    bool isBomb() const;
    void update(sf::RenderWindow &window) override;

};

#endif // BOMBBLOCK_H