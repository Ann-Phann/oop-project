#ifndef CANNON_H
#define CANNON_H

#include <iostream>

#include <math.h>
#include <vector>
#include <memory>

#include "Ball.h"
#include "Block.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846  // Define the pi constant
#endif


class Cannon : public sf::Drawable, public sf::Transformable {
    private:
        std::vector<sf::Drawable*> cannonParts;
        sf::CircleShape base;
        sf::RectangleShape gun;
        sf::Vector2f gunPosition;
        sf::Vertex aimLine[2];
        sf::Vertex reflectionAimLine[2];

        //Balls to be shot
        int numberBall;
        std::vector<std::shared_ptr<Ball>> balls;
        int ammo; // Current ammunition count
        bool isFiring; // Flag to check if currently firing
        sf::Clock fireTimer; // Timer to control the interval between shots
       
        //check if the mouse is pressed
        bool isPressed;

        //block
        std::vector<Block> blocks;
        
        //private functions
        void initializeVariables();
        void initializeCannon();
    
    public:
        //constructor and destructor
        Cannon();
        virtual ~Cannon();

        //shot the ball
        void fireCannon();

        //update and draw
        void update(sf::Time dt, sf::RenderWindow& window);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        //motion functions
        void updateGunRotation(sf::RenderWindow& window);
        void updateAimLine(sf::RenderWindow& window);

        sf::Vector2f calculateGunTipPosition();  // Calculates the firing position at the cannon's tip
        sf::Vector2f calculateFiringVelocity();  // Calculates the velocity of a fired ball based on the gun's orientation

        //manage and access balls
        //update all balls that have been fired, ensuring their motion is processed each frame.
        void updateBall(sf::Time dt, sf::RenderWindow& window);
        void ballsHitBlock(Block&);

        //get number of ball
        int getNumberBall() const;
};   

#endif