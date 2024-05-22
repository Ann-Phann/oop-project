#include "../include/Block.h"
#include <iostream>

// Declare a static sf::Font object
static sf::Font blockFont;

// Constructor for the Block class
Block::Block(float x, float y) : blockStrength(1), isDestroyed(false) {
    // Initialize the block
    block.setSize(sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT));
    block.setPosition(x, y);
    block.setFillColor(sf::Color::Green);
    block.setOutlineThickness(2.f);
    block.setOutlineColor(sf::Color(250, 150, 100));

    std::cout << "Loading font for block..." << std::endl;
    if (!blockFont.loadFromFile("assets/fonts/Roboto-Black.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
    } else {
        std::cout << "Font loaded successfully!" << std::endl;   
        // Initialize the block text   
        blockText.setFont(blockFont);
        blockText.setCharacterSize(20.f);
        blockText.setFillColor(sf::Color::Red);
        blockText.setString(std::to_string(blockStrength));
        sf::FloatRect textRect = blockText.getLocalBounds();
        blockText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        blockText.setPosition(block.getPosition().x + block.getSize().x / 2.0f, block.getPosition().y + block.getSize().y / 2.0f);
        std::cout << "Block text initialized at position: " << blockText.getPosition().x << ", " << blockText.getPosition().y << std::endl;
    }
}

// Reflects the ball upon collision
void Block::reflectBall(Ball& ball) {
    sf::RectangleShape blockShape = this->block;
    sf::CircleShape ballShape = ball.getCircle();
    CollisionDetails collision = checkCollision(blockShape, ballShape);     // Check for collision
    // Reflect the ball if there is a collision
    if (collision.collisionType != 0) {
        --blockStrength;    // Decrease the block's strength
        sf::Vector2f incomingVelocity = ball.getVelocity(); 
        float dotProduct = incomingVelocity.x * collision.normal.x + incomingVelocity.y * collision.normal.y;
        sf::Vector2f reflectedVelocity = incomingVelocity - 2 * dotProduct * collision.normal; // Reflect the velocity
        ball.setVelocity(reflectedVelocity); 
        if (blockStrength <= 0) {
            isDestroyed = true;
        }
    }
}

// Checks collision with the ball
Block::CollisionDetails Block::checkCollision(const sf::RectangleShape &r1, const sf::CircleShape &c1) {
    float gapX = std::clamp(c1.getPosition().x, r1.getPosition().x, r1.getPosition().x + r1.getSize().x);
    float gapY = std::clamp(c1.getPosition().y, r1.getPosition().y, r1.getPosition().y + r1.getSize().y);
    float distanceX = c1.getPosition().x - gapX;
    float distanceY = c1.getPosition().y - gapY;
    float distanceSquared = distanceX * distanceX + distanceY * distanceY; // Distance between the ball and the block

    CollisionDetails details;
    details.collisionType = 0; 
    details.normal = sf::Vector2f(0, 0); // No collision

    if (distanceSquared < c1.getRadius() * c1.getRadius()) { // Check for collision
        if (gapY == c1.getPosition().y) {   // Check if the ball is colliding with the top or bottom of the block
            details.collisionType = 1; 
            details.normal = sf::Vector2f(distanceX > 0 ? -1.f : 1.f, 0.f);
        } else if (gapX == c1.getPosition().x) {   // Check if the ball is colliding with the sides of the block
            details.collisionType = 2;
            details.normal = sf::Vector2f(0.f, distanceY > 0 ? -1.f : 1.f);
        } else {    // Check if the ball is colliding with the corners of the block
            details.collisionType = 3;
            details.normal = sf::Vector2f(distanceX > 0 ? -1.f : 1.f, distanceY > 0 ? -1.f : 1.f);
        }
    }

    return details; // Return the collision details
}

// Updates the block's state
void Block::update(sf::RenderWindow &window) {
    blockText.setString(std::to_string(blockStrength));
}

// Renders the block
void Block::render(sf::RenderTarget& target) const {
    target.draw(block);
    target.draw(blockText);
}

// Getters
bool Block::getIsDestroyed() const {
    return isDestroyed;
}

const sf::RectangleShape& Block::getShape() const {
    return block;
}

const sf::Text& Block::getText() const {
    return blockText;
}

int Block::getStrength() const {
    return blockStrength;
}

// Setters
void Block::setSize(sf::Vector2f size) {
    block.setSize(size);
}

void Block::setPosition(float x, float y) {
    block.setPosition(x, y);
    blockText.setPosition(x + block.getSize().x / 2.0f, y + block.getSize().y / 2.0f);
}
