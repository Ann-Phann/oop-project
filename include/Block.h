#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Constants.h"
#include "GameObject.h"

const float BLOCK_WIDTH = 210.f;
const float BLOCK_HEIGHT = 105.f;

/**
 * @brief The Block class represents a block object in the game.
 *
 * This abstract class provides functionality for setting the block's position,
 * checking for collisions, and rendering it. Derived classes must implement
 * specific behaviors for different block types.
 */
class Block : public GameObject {
private:
    struct CollisionDetails {
        int collisionType;       // 0 = No collision, 1 = Side, 2 = Top/Bottom, 3 = Corner
        sf::Vector2f normal;     // Normal vector at the point of collision
    };

protected:
    sf::RectangleShape block;    // The block's rectangle shape
    sf::Text blockText;          // Text displayed on the block
    int blockStrength;           // The block's strength
    bool isDestroyed;            // Flag indicating if the block is destroyed

public:
    Block(float x, float y);
    virtual ~Block() = default;

    // Getters
    virtual bool getIsDestroyed() const;                 // Checks if the block is destroyed
    virtual const sf::RectangleShape& getShape() const;  // Gets the block's shape
    virtual const sf::Text& getText() const;             // Gets the block's text
    virtual int getStrength() const;                     // Gets the block's strength

    // Setters
    virtual void setSize(sf::Vector2f size);             // Sets the block's size
    virtual void setPosition(float x, float y);          // Sets the block's position

    // Other methods
    virtual void reflectBall(Ball& ball);                // Reflects the ball upon collision
    virtual void update(sf::RenderWindow &window);       // Updates the block state
    virtual void render(sf::RenderTarget& target) const; // Renders the block
    virtual bool isExtraBall() const { return false; }   // For ExtraBallBlock
    virtual bool isBomb() const { return false; }        // For BombBlock

    CollisionDetails checkCollision(const sf::RectangleShape &r1, const sf::CircleShape &c1); // Checks for collision
};

#endif // BLOCK_H
