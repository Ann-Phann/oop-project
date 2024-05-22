#include "../include/Cannon.h"
#include <iostream>

// Constant for PI
constexpr double PI = 3.14159265358979323846;

// Initializes the cannon's variables
void Cannon::initializeVariables() {
    isPressed = false;
    canRotateGun = true;
    initialAmmo = 1;
    ammo = initialAmmo;
    fireInterval = sf::seconds(0.3f); // Time between shots
    timeSinceLastShot = sf::Time::Zero; // Time since the last shot was fired
}

// Initializes the cannon's shape
void Cannon::initializeCannon() {
    // Base initialization
    base.setRadius(50.f);
    base.setFillColor(sf::Color(150, 50, 250));
    base.setOutlineThickness(10.f);
    base.setOutlineColor(sf::Color(250, 150, 100));
    float xBase = (1280 / 2.0f) - base.getRadius();
    float yBase = 1024 - base.getRadius();
    base.setPosition(xBase, yBase);

    // Gun initialization
    gun.setSize(sf::Vector2f(120.f, 10.f));
    gun.rotate(-90.f);
    gun.setFillColor(sf::Color(0, 0, 0));
    gun.setPosition(base.getPosition().x + base.getRadius(), base.getPosition().y + base.getRadius());
}

// Constructor
Cannon::Cannon() {
    this->initializeVariables();
    this->initializeCannon();
}

// Updates the gun's rotation based on mouse position
void Cannon::updateGunRotation(sf::RenderWindow &window) {
    gunPosition = this->gun.getPosition();

    sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Mouse position in window
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)); // Mouse position in float

    float dx = mousePosF.x - gunPosition.x;
    float dy = mousePosF.y - gunPosition.y;
    float angle = atan2(dy, dx) * 180 / PI; // Calculate angle in degrees

    // Limit the angle of the gun
    if (angle < -170.f) {
        angle = -170.f;
    } else if (angle > -10.f) {
        angle = -10.f;
    }

    gun.setRotation(angle);
}

// Updates the aim line based on gun's orientation
void Cannon::updateAimLine(sf::RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    float gunLength = gun.getSize().x;
    float angleRad = gun.getRotation() * PI / 180;

    // Calculate the gun tip position
    sf::Vector2f gunTip = gun.getPosition() + sf::Vector2f(cos(angleRad) * gunLength, sin(angleRad) * gunLength);
    gunTip.x += 5.0f;

    // Calculate the line end point
    sf::Vector2f unitDirection = sf::Vector2f(cos(angleRad), sin(angleRad));
    float maxDistance = std::max(window.getSize().x, window.getSize().y);
    sf::Vector2f lineEndPoint = gunTip + unitDirection * maxDistance;

    aimLine[0] = sf::Vertex(gunTip, sf::Color::White);
    aimLine[1] = sf::Vertex(lineEndPoint, sf::Color::White);

    float leftBoundary = 0;
    float rightBoundary = static_cast<float>(window.getSize().x); 
    float topBoundary = 0;

    sf::Vector2f intersectPoint;
    float distanceX, distanceY;

    if (unitDirection.x > 0) { // Right boundary
        intersectPoint = gunTip + unitDirection * ((rightBoundary - gunTip.x) / unitDirection.x);
        distanceX = (rightBoundary - gunTip.x) / unitDirection.x;
    } else { // Left boundary
        intersectPoint = gunTip + unitDirection * ((leftBoundary - gunTip.x) / unitDirection.x);
        distanceX = (gunTip.x - leftBoundary) / -unitDirection.x;
    }

    sf::Vector2f topIntersect;
    if (unitDirection.y < 0) { // Top boundary
        topIntersect = gunTip + unitDirection * ((topBoundary - gunTip.y) / unitDirection.y);
        distanceY = (gunTip.y - topBoundary) / -unitDirection.y;
        if (distanceY < distanceX) {
            intersectPoint = topIntersect;
        }
    }

    sf::Vector2f reflectionDirection;
    if (intersectPoint == topIntersect) { 
        reflectionDirection = sf::Vector2f(unitDirection.x, -unitDirection.y);
    } else {
        reflectionDirection = sf::Vector2f(-unitDirection.x, unitDirection.y);
    }

    sf::Vector2f reflectionEndPoint = intersectPoint + reflectionDirection * (maxDistance * 2);
    reflectionAimLine[0] = sf::Vertex(intersectPoint, sf::Color::White);
    reflectionAimLine[1] = sf::Vertex(reflectionEndPoint, sf::Color::White);
}

// Calculates the firing position at the cannon's tip
sf::Vector2f Cannon::calculateGunTipPosition() {
    float angleRad = gun.getRotation() * (PI / 180.0f); // Convert to radians
    float gunLength = gun.getSize().x;
    // Calculate the gun tip position
    return sf::Vector2f(gun.getPosition().x + cos(angleRad) * gunLength,
                        gun.getPosition().y + sin(angleRad) * gunLength);
}

// Calculates the velocity of a fired ball based on the gun's orientation
sf::Vector2f Cannon::calculateFiringVelocity() {
    float angleRad = gun.getRotation() * (PI / 180.0f);
    float speed = 400.0f;
    return sf::Vector2f(cos(angleRad) * speed, sin(angleRad) * speed);
}

// Handles input for shooting
void Cannon::handleInput() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isPressed) {
        isPressed = true;
        canRotateGun = false;
        timeSinceLastShot = sf::Time::Zero;
    }
}

// Shoots a ball
void Cannon::shoot() {
    if (ammo > 0) {
        sf::Vector2f firingPosition = calculateGunTipPosition();
        sf::Vector2f firingVelocity = calculateFiringVelocity();

        // Create a new ball
        std::shared_ptr<Ball> newBall = std::make_shared<Ball>();
        newBall->setPosition(firingPosition);
        newBall->setVelocity(firingVelocity);

        balls.push_back(newBall);

        ammo--;     // Decrease ammo
    }
}

// Updates the shooting mechanics
void Cannon::updateShooting(sf::Time deltaTime) {
    // If the mouse is pressed, shoot
    if (isPressed) {
        timeSinceLastShot += deltaTime;
        // If the time since the last shot is greater than the fire interval, shoot
        if (timeSinceLastShot >= fireInterval) {
            shoot();
            timeSinceLastShot = sf::Time::Zero; // Reset time since last shot

            if (ammo <= 0) {
                isPressed = false;
                canRotateGun = true;
            }
        }
    }
}

// Reloads the cannon with specified ammunition
void Cannon::reload(int extraAmmo) {
    ammo = initialAmmo;
    ammo += extraAmmo;
    initialAmmo = ammo;
}

// Updates the cannon
void Cannon::update(sf::RenderWindow &window) {
    if (canRotateGun) {
        this->updateGunRotation(window);
    }
    this->updateAimLine(window);
}

// Renders the cannon
void Cannon::render(sf::RenderTarget& target) const {
    if (!isPressed) {
        target.draw(aimLine, 2, sf::Lines);
        target.draw(reflectionAimLine, 2, sf::Lines);
    }
    target.draw(base);
    target.draw(gun);
}

// Checks if any balls touch the bottom of the screen
bool Cannon::checkBallsTouchBottom(float screenHeight) {
    for (const auto& ball : balls) {
        if (ball->getPosition().y + ball->getRadius() < screenHeight) {
            return false;
        }
    }
    return true;
}

// Getter for balls
std::vector<std::shared_ptr<Ball>>& Cannon::getBalls() {
    return balls;
}
