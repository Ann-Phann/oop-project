#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Ball.h"

class Block : public GameObject{
protected:
    sf::RectangleShape block;
    int blockStrength;
    bool isDestroyed;

    //block strength display
    sf::Text blockText;
    //sf::Font blockFont;

public:
    Block(float x, float y, float width, float height, int strength);

    struct CollisionDetails {
    int collisionType;       // 0 = No collision, 1 = Side, 2 = Top/Bottom, 3 = Corner
    sf::Vector2f normal;     // Normal vector at the point of collision
    };

    CollisionDetails checkCollision(const sf::RectangleShape &rectangle, const sf::CircleShape &circle);
    void reflectBall(Ball& ball);
    bool getIsDestroyed() const ;

    //void block

    void update(sf::RenderWindow &window) override;
    void render(sf::RenderTarget& target) const override;

    //getter setter method
    int getStrength() const;
    const sf::RectangleShape& getShape() const;
    const sf::Text& getText() const;
    void setSize(sf::Vector2f size);
    
};

#endif // BLOCK_H
