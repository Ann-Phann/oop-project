#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Constants.h"
#include "GameObject.h"
const float BLOCK_WIDTH = 210.f;
const float BLOCK_HEIGHT = 105.f;



class Block : public GameObject {
protected:
    sf::RectangleShape block;
    sf::Text blockText;
    int blockStrength;
    bool isDestroyed;

    struct CollisionDetails {
        int collisionType;       // 0 = No collision, 1 = Side, 2 = Top/Bottom, 3 = Corner
        sf::Vector2f normal;     // Normal vector at the point of collision
    };

public:
    Block(float x, float y);
    virtual ~Block() = default;
    virtual void reflectBall(Ball& ball);
    virtual void update(sf::RenderWindow &window);
    virtual void render(sf::RenderTarget& target) const;
    virtual bool getIsDestroyed() const;
    virtual void setSize(sf::Vector2f size);
    virtual const sf::RectangleShape& getShape() const;
    virtual const sf::Text& getText() const;
    virtual int getStrength() const;
    virtual void setPosition(float x, float y);
    virtual bool isExtraBall() const { return false; } // For ExtraBallBlock
    virtual bool isBomb() const { return false; } // For BombBlock

    CollisionDetails checkCollision(const sf::RectangleShape &r1, const sf::CircleShape &c1);
};

#endif // BLOCK_H
