#ifndef BLOCK_H
#define BLOCK_H



#include <math.h>
#include <vector>
#include <iostream>
#include <memory>
#include <string>

#include "Ball.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Block : public sf::Sprite
{
protected:
    sf::RectangleShape block;
    int strength;
    bool isDestroyed;
    void initializeBlock();
    sf::Vector2f size;

    //text for block strength
    sf::Font blockFont;
    // sf::Text blockStrength;
public:
    Block();
    virtual ~Block() = 0;  

    struct CollisionDetails {
        int collisionType;       // 0 = No collision, 1 = Side, 2 = Top/Bottom, 3 = Corner
        sf::Vector2f normal;     // Normal vector at the point of collision
    };

    //public functions
    virtual void update(Ball& ball) = 0;
    //virtual void update(const sf::Time& dt, Ball& ball) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

    bool getIsDestroyed() const;
    virtual void hitBall(Ball& ball);
    int getStrength();
    CollisionDetails checkCollision(const sf::RectangleShape &rectangle, const sf::CircleShape &circle);
    void reflectBall(Ball& ball);
    sf::Text blockStrength;

};

#endif