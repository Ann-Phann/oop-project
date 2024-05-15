#include "../include/Block.h"

Block::Block()
{
    // this->strength = 1;
    this->initializeBlock();
}



Block ::~Block()
{}

int Block::getStrength() {
    return strength;
}

bool Block:: getIsDestroyed() const
{
    return isDestroyed;
}

void Block::initializeBlock()
{
    size = sf::Vector2f(210.f,150.f);
    block.setSize(sf::Vector2f(210.f,150.f)); 
    block.setOutlineThickness(5.f);
    // if colour = white 
    block.setOutlineColor(sf::Color::White);
    // else 
    //green
    block.setPosition(400.f, 500.f);
    
}

// void Block::initializeBlockWithPos(int top, int left){
//     size = sf::Vector2f(210.f,150.f);
//     block.setSize(sf::Vector2f(210.f,150.f)); 
//     block.setOutlineThickness(5.f);
//     // if colour = white 
//     block.setOutlineColor(sf::Color::White);
//     // else 
//     //green
//     block.setPosition((float)top, (float)left);
// }


// void Block:: update(const sf::Time& dt, Ball& ball)
// {
//    this->hitBall(ball);
// }

void Block:: update(Ball& ball)
{
   this->hitBall(ball);

}


void Block:: hitBall(Ball& ball)
{
    // sf::FloatRect thisBound = sf::FloatRect(this->getPosition(), this->size);
    // sf::FloatRect ballBound = sf::FloatRect(ball.getPosition(), sf::Vector2f(ball.radius, ball.radius));

    sf::FloatRect thisBound = block.getGlobalBounds();
    sf::FloatRect ballBound = ball.getCircle().getGlobalBounds();
    if (thisBound.intersects(ballBound)) {
        strength--;  
        reflectBall(ball); 

        if(this->strength <= 0)
        {
            isDestroyed = true;
            std::cout << "Destroyed" << std::endl;
            
        }
    }

    // reflectBall(ball);
    // if(strength <= 0)
    // {
    //     std::cout << "Delete" << std::endl;
    //     isDestroyed = true;
  
    // }
}

void Block:: reflectBall(Ball& ball) 
{
    sf::RectangleShape blockShape = this->block; // Assuming you have a member that represents the block shape
    sf::CircleShape ballShape = ball.getCircle(); // Assuming Ball class has a getCircle method returning sf::CircleShap
    CollisionDetails collision = checkCollision(blockShape, ballShape);
    if (collision.collisionType != 0) {  // If there's a collision
        sf::Vector2f incomingVelocity = ball.getVelocity();
        float dotProduct = incomingVelocity.x * collision.normal.x + incomingVelocity.y * collision.normal.y;
        sf::Vector2f reflectedVelocity = incomingVelocity - 2 * dotProduct * collision.normal;
        ball.setVelocity(reflectedVelocity);
    }
}
/*Check collision between ball and block
# return 0 if they dont hit
# return 1 if they hit left or right
# return 2 if they hit top or bottom
# return 3 if they hit a corner
*/


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
  



