#ifndef CANNON_H
#define CANNON_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <memory>

#include "GameObject.h"
#include "Ball.h"

class Cannon : public GameObject {
private:
    sf::CircleShape base;
    sf::RectangleShape gun;
    sf::Vector2f gunPosition;
    sf::Vertex aimLine[2];
    sf::Vertex reflectionAimLine[2];

    //shooting variables
    int initialAmmo;
    int ammo;
    sf::Time fireInterval;
    sf::Time timeSinceLastShot;
    //check if the mouse is pressed
    bool isPressed;

    //stop moving gun when firing
    bool canRotateGun;

    //std::vector<Ball> balls;
    std::vector<std::shared_ptr<Ball>> balls;




    //private functions
    void initializeVariables();
    void initializeCannon();

public:

    Cannon();

     //motion functions
    void updateGunRotation(sf::RenderWindow& window);
    void updateAimLine(sf::RenderWindow& window);
    sf::Vector2f calculateGunTipPosition();  // Calculates the firing position at the cannon's tip
    sf::Vector2f calculateFiringVelocity();  // Calculates the velocity of a fired ball based on the gun's orientation

    void update(sf::RenderWindow &window) override;
    void render(sf::RenderTarget& target) const override;
    
    void shoot();
    void handleInput();
    void updateShooting(sf::Time deltaTime);
    void reload(int ammo);
    bool checkBallsTouchBottom(float screenHeight); // New function
    std::vector<std::shared_ptr<Ball>>& getBalls(); // Getter for balls


    friend class GameLevel;
};

#endif // CANNON_H
