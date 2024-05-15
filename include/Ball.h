#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <math.h>

class Ball : public sf::Sprite
{
private:   
    sf::CircleShape ball;
    sf::Vector2f velocity;

    //private functions
    void initializeBall();

public:
    Ball();
    ~Ball();

    float radius;

    //public functions
    void setPosition(const sf::Vector2f& position);
    void setVelocity(const sf::Vector2f& velocity);
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    void reflect(const sf::Vector2f& normal);
    void update(const sf::Time& dt, sf::RenderWindow& window);  // Update the ball's position based on its velocity
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;  // Render the ball
    const sf::CircleShape& getCircle() const { return ball; }  // Getter for the circle shape
    
    
};
#endif