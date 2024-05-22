#include "../include/Ball.h"

// Initializes the ball's properties
void Ball::initializeBall() {
    radius = 10.f;
    ball.setRadius(radius);
    ball.setFillColor(sf::Color(150, 150, 150));
    ball.setOrigin(radius, radius);
}

Ball::Ball() {
    initializeBall();
}

// Getters
sf::Vector2f Ball::getPosition() const {
    return ball.getPosition();
}

sf::Vector2f Ball::getVelocity() const {
    return velocity;
}

const sf::CircleShape& Ball::getCircle() const {
    return ball;
}

float Ball::getRadius() const {
    return ball.getRadius();
}

// Setters
void Ball::setPosition(const sf::Vector2f& position) {
    ball.setPosition(position);
}

void Ball::setVelocity(const sf::Vector2f& velocity) {
    this->velocity = velocity;
}

// Other methods

// Updates the ball's position based on its velocity and the time elapsed since the last update.
void Ball::updatePosition(const sf::Time& dt, sf::RenderWindow& window) {
    sf::Vector2f position = getPosition();
    position += velocity * dt.asSeconds();  // Move the ball
    setPosition(position);

    sf::Vector2f size(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    bool hasCollided = false;
    sf::Vector2f normal;

    // Check collision with window boundaries
    if (position.x + radius >= size.x) {    // Right boundary
        position.x = size.x - radius;
        normal = sf::Vector2f(-1, 0);
        hasCollided = true;
    } else if (position.x - radius <= 0) {  // Left boundary
        position.x = radius;
        normal = sf::Vector2f(1, 0);
        hasCollided = true;
    } else if (position.y - radius <= 0) {  // Top boundary
        position.y = radius;
        normal = sf::Vector2f(0, 1);
        hasCollided = true;
    }

    if (hasCollided) { // Reflect the ball's velocity
        reflect(normal);
    }
}

// Reflects the ball's velocity based on the normal vector of the collision.
void Ball::reflect(const sf::Vector2f& normal) {
    float dotProduct = velocity.x * normal.x + velocity.y * normal.y;
    velocity -= 2 * dotProduct * normal;
    setPosition(getPosition());
}


// Updates the ball's position and checks for collisions with the window boundaries.
void Ball::update(sf::RenderWindow &window) {
    updatePosition(sf::seconds(1.f / 60.f), window);
}


// Renders the ball to the target window.
void Ball::render(sf::RenderTarget& target) const {
    target.draw(ball);
}
