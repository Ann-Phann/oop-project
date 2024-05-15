#ifndef NORMAL_BLOCK_H
#define NORMAL_BLOCK_H

#include <math.h>
#include <vector>
#include <iostream>
#include <memory>

#include "Ball.h"
#include "Block.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class NormalBlock : public Block {
public:
    NormalBlock(); // Constructor
    virtual ~NormalBlock(); // Destructor

    void update(Ball& ball) override;
    //void update(const sf::Time& dt, Ball& ball) override; // Implementation of the update function
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // Implementation of the draw function
    
protected:
    void initializeBlock();
    void initializeBlockFont();

};

#endif