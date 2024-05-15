#include "../include/Ball.h"

void Ball::initializeBall()
{
    radius = 10.f;
    this->ball.setRadius(10.f);
    this->ball.setFillColor(sf::Color(150, 150, 150));
    this->ball.setOrigin(5.f, 5.f);
}

Ball::Ball() 
{
    initializeBall();
}

Ball::~Ball()
{

}

void Ball::setPosition(const sf::Vector2f& position) {
    this->ball.setPosition(position);
}

void Ball::setVelocity(const sf::Vector2f& velocity) {
    this->velocity = velocity;
}

sf::Vector2f Ball::getPosition() const {
    return this->ball.getPosition();
}

sf::Vector2f Ball::getVelocity() const {
    return velocity;
}

void Ball::update(const sf::Time& dt, sf::RenderWindow& window) {
        // Update position based on velocity
    sf::Vector2f position = this->getPosition();
    position += this->velocity * dt.asSeconds();  // Move the ball
    this->setPosition(position);

    // Get the size of the window and convert it to sf::Vector2f for calculations
    sf::Vector2u size_u = window.getSize();
    sf::Vector2f size(static_cast<float>(size_u.x), static_cast<float>(size_u.y));

    // Check collision with the window's boundaries
    bool hasCollided = false;
    sf::Vector2f normal;  // This will store the normal vector of the collision surface

    // Right boundary
    if (position.x + this->ball.getRadius() >= size.x) {
        position.x = size.x - this->ball.getRadius();  // Correct the position
        normal = sf::Vector2f(-1, 0);  // Normal pointing left
        hasCollided = true;
    }

    // Left boundary
    if (position.x - this->ball.getRadius() <= 0) {
        position.x = this->ball.getRadius();  // Correct the position
        normal = sf::Vector2f(1, 0);  // Normal pointing right
        hasCollided = true;
    }

    // Top boundary
    if (position.y - this->ball.getRadius() <= 0) {
        position.y = this->ball.getRadius();  // Correct the position
        normal = sf::Vector2f(0, 1);  // Normal pointing down
        hasCollided = true;
    }

    // Update ball's velocity if it collided
    if (hasCollided) {
        reflect(normal);
    }
}


void Ball::reflect(const sf::Vector2f& normal) {
    // Reflect the velocity vector
    float dotProduct = this->velocity.x * normal.x + this->velocity.y * normal.y;
    this->velocity = this->velocity - 2 * dotProduct * normal;
    this->setPosition(this->getPosition());  // Update the position after reflection
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->ball, states);
}