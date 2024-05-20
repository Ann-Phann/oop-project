#include "../include/Block.h"

// Declare a static sf::Font object
static sf::Font blockFont;

Block::Block(float x, float y) : blockStrength(1) {
    block.setSize(sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT));
    block.setPosition(x, y);
    block.setFillColor(sf::Color::Green);
    block.setOutlineThickness(5.f);
    block.setOutlineColor(sf::Color(250, 150, 100));
    isDestroyed = false;
   

    std::cout << "Loading font for block..." << std::endl;
    if (!blockFont.loadFromFile("assets/fonts/Roboto-Black.ttf"))
    {
        std::cout << "Failed to load background image!" << std::endl;
    } else {
        std::cout << "Font loaded successfully!" << std::endl;
        blockText.setFont(blockFont);
        blockText.setCharacterSize(20.f);
        blockText.setFillColor(sf::Color::Red);
        blockText.setString(std::to_string(blockStrength));
        sf::FloatRect textRect = blockText.getLocalBounds();
        blockText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
        blockText.setPosition(block.getPosition().x + block.getSize().x/2.0f, block.getPosition().y + block.getSize().y/2.0f);
        std::cout << "Block text initialized at position: " << blockText.getPosition().x << ", " << blockText.getPosition().y << std::endl;
    }
}

void Block:: reflectBall(Ball& ball) 
{
    sf::RectangleShape blockShape = this->block; // Assuming you have a member that represents the block shape
    sf::CircleShape ballShape = ball.getCircle(); // Assuming Ball class has a getCircle method returning sf::CircleShap
    CollisionDetails collision = checkCollision(blockShape, ballShape);
    if (collision.collisionType != 0) {  // If there's a collision
        --blockStrength;
        sf::Vector2f incomingVelocity = ball.getVelocity();
        float dotProduct = incomingVelocity.x * collision.normal.x + incomingVelocity.y * collision.normal.y;
        sf::Vector2f reflectedVelocity = incomingVelocity - 2 * dotProduct * collision.normal;
        ball.setVelocity(reflectedVelocity);
        if (blockStrength <= 0) {
            isDestroyed = true;
        }
    }
}

 struct CollisionDetails {
    int collisionType;       // 0 = No collision, 1 = Side, 2 = Top/Bottom, 3 = Corner
    sf::Vector2f normal;     // Normal vector at the point of collision
};

Block::CollisionDetails Block::checkCollision(const sf::RectangleShape &r1, const sf::CircleShape &c1){
    // Variables to find the gap and calculate distance
    float gapX = std::clamp(c1.getPosition().x, r1.getPosition().x, r1.getPosition().x + r1.getSize().x);
    float gapY = std::clamp(c1.getPosition().y, r1.getPosition().y, r1.getPosition().y + r1.getSize().y);
    float distanceX = c1.getPosition().x - gapX;
    float distanceY = c1.getPosition().y - gapY;
    float distanceSquared = distanceX * distanceX + distanceY * distanceY;

    CollisionDetails details;
    details.collisionType = 0;  // Default to no collision
    details.normal = sf::Vector2f(0, 0);  // Default normal

    if (distanceSquared < c1.getRadius() * c1.getRadius()) {
        if (gapY == c1.getPosition().y) {
            details.collisionType = 1;  // Side collision
            details.normal = sf::Vector2f(distanceX > 0 ? -1.f : 1.f, 0.f);  // Horizontal normal
        } else if (gapX == c1.getPosition().x) {
            details.collisionType = 2;  // Top/Bottom collision
            details.normal = sf::Vector2f(0.f, distanceY > 0 ? -1.f : 1.f);  // Vertical normal
        } else {
            details.collisionType = 3;  // Corner collision
            details.normal = sf::Vector2f(distanceX > 0 ? -1.f : 1.f, distanceY > 0 ? -1.f : 1.f);  // Diagonal normal
        }
    }

    return details;
}


void Block::update(sf::RenderWindow &window) {
    // update
    blockText.setString(std::to_string(blockStrength));
}    

void Block::render(sf::RenderTarget& target) const {
}

//getter setter method
bool Block:: getIsDestroyed() const
{
    return isDestroyed;
}

void Block:: setSize(sf::Vector2f size)
{
    block.setSize(size);
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

void Block::setPosition(float x, float y) {
    block.setPosition(x, y);
    blockText.setPosition(x + block.getSize().x / 2.0f, y + block.getSize().y / 2.0f);
}

