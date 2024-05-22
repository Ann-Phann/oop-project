#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

/**
 * @brief The Ball class represents a ball object in the game.
 *
 * This class is derived from the GameObject class and provides functionality
 * for setting the ball's position and velocity, updating its position, and rendering it.
 */
class Ball : public GameObject {
private:
    sf::CircleShape ball;       // The ball's circle shape
    sf::Vector2f velocity;      // The ball's velocity
    float radius;               // The ball's radius

    void initializeBall();      // Initializes the ball's properties

public:
    Ball();

    // Getters
    sf::Vector2f getPosition() const;        // Gets the ball's position
    sf::Vector2f getVelocity() const;        // Gets the ball's velocity
    const sf::CircleShape& getCircle() const; // Gets the ball's circle shape
    float getRadius() const;                 // Gets the ball's radius

    // Setters
    void setPosition(const sf::Vector2f& position);  // Sets the ball's position
    void setVelocity(const sf::Vector2f& velocity);  // Sets the ball's velocity

    // Other methods
    void updatePosition(const sf::Time& dt, sf::RenderWindow& window);  // Updates the ball's position
    void reflect(const sf::Vector2f& normal);  // Reflects the ball's velocity
    void update(sf::RenderWindow &window) override;  // Updates the ball
    void render(sf::RenderTarget& target) const override;  // Renders the ball

    friend class Cannon;
};

#endif // BALL_H
