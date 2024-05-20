#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Ball : public GameObject {
private:
    sf::CircleShape ball;
    sf::Vector2f velocity;

    //private functions
    void initializeBall();


public:
    Ball();

    float radius;

    //public functions
    void setPosition(const sf::Vector2f& position);
    void setVelocity(const sf::Vector2f& velocity);
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    void updatePosition(const sf::Time& dt, sf::RenderWindow& window);
    void reflect(const sf::Vector2f& normal);
    const sf::CircleShape& getCircle() const;  // Getter for the circle shape
    float getRadius() const;    
    void update(sf::RenderWindow &window) override;
    void render(sf::RenderTarget& target) const override;

    // getters and setters
    friend class Cannon;
};

#endif // BALL_H
