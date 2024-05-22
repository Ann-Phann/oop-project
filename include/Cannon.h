#ifndef CANNON_H
#define CANNON_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Ball.h"

/**
 * @brief The Cannon class represents the cannon object in the game.
 *
 * This class handles the cannon's rotation, aiming, shooting mechanics, and ball management.
 */
class Cannon : public GameObject {
private:
    sf::CircleShape base;                 // The cannon's base
    sf::RectangleShape gun;               // The cannon's gun
    sf::Vector2f gunPosition;             // Position of the cannon's gun
    sf::Vertex aimLine[2];                // Line for aiming
    sf::Vertex reflectionAimLine[2];      // Line for reflection aim

    // Shooting variables
    int initialAmmo;                      // Initial ammunition count
    int ammo;                             // Current ammunition count
    sf::Time fireInterval;                // Time interval between shots
    sf::Time timeSinceLastShot;           // Time since the last shot was fired
    bool isPressed;                       // Check if the mouse is pressed
    bool canRotateGun;                    // Stop moving gun when firing

    std::vector<std::shared_ptr<Ball>> balls; // Vector of balls

    // Private functions
    void initializeVariables();           // Initializes the cannon's variables
    void initializeCannon();              // Initializes the cannon's shape

public:
    Cannon();

    // Motion functions
    void updateGunRotation(sf::RenderWindow& window);  // Updates the gun's rotation based on mouse position
    void updateAimLine(sf::RenderWindow& window);      // Updates the aim line based on gun's orientation
    sf::Vector2f calculateGunTipPosition();            // Calculates the firing position at the cannon's tip
    sf::Vector2f calculateFiringVelocity();            // Calculates the velocity of a fired ball based on the gun's orientation

    // Other methods
    void update(sf::RenderWindow &window) override;    // Updates the cannon
    void render(sf::RenderTarget& target) const override; // Renders the cannon
    void shoot();                                      // Shoots a ball
    void handleInput();                                // Handles input for shooting
    void updateShooting(sf::Time deltaTime);           // Updates the shooting mechanics
    void reload(int ammo);                             // Reloads the cannon with specified ammunition
    bool checkBallsTouchBottom(float screenHeight);    // Checks if any balls touch the bottom of the screen
    std::vector<std::shared_ptr<Ball>>& getBalls();    // Getter for balls

    friend class GameLevel;
};

#endif // CANNON_H
