#include "../include/Cannon.h"

// ********** PRIVATE FUNCTIONS **********
constexpr double PI = 3.14159265358979323846;

void Cannon::initializeVariables()
{
    isPressed = false;
    canRotateGun = true;
    ammo = 21;
    fireInterval = sf::seconds(0.3f); // Time between shots
    timeSinceLastShot = sf::Time::Zero; // Time since the last shot was fired
}

void Cannon::initializeCannon()
{
    // base initialize
    base.setRadius(50.f);
    base.setFillColor(sf::Color(150, 50, 250));
    base.setOutlineThickness(10.f);
    base.setOutlineColor(sf::Color(250, 150, 100));
    float xBase = (1280 / 2.0f) - base.getRadius();
    float yBase = 1024 - base.getRadius();
    base.setPosition(xBase, yBase);

    // gun initialize
    gun.setSize(sf::Vector2f(120.f, 10.f));
    gun.rotate(-90.f);
    gun.setFillColor(sf::Color(0, 0, 0));
    // this->gun.setOrigin(gun.getSize().x / 2, gun.getSize().y);  // Origin set to the bottom center
    gun.setPosition(base.getPosition().x + base.getRadius(), base.getPosition().y + base.getRadius()); // Position gun on top of the base
}


// constructor
Cannon::Cannon()
{
    this->initializeVariables();
    this->initializeCannon();
}

// ********** MOTION FUNCTIONS **********
// #### gun rotation ####
void Cannon::updateGunRotation(sf::RenderWindow &window)
{
    // get gun position
    gunPosition = this->gun.getPosition();

    // Handle mouse position relative to the gun base
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // Calculate the angle to rotate the gun
    float dx = mousePosF.x - gunPosition.x;
    float dy = mousePosF.y - gunPosition.y;
    float angle = atan2(dy, dx) * 180 / PI;

    // limit rotation angle from 0--> 170 degree
    if (angle < -170.f)
    {
        angle = -170.f;
    }
    else if (angle > -10.f)
    {
        angle = -10.f;
    }

    gun.setRotation(angle);
}


// #### aim line rotation ####
void Cannon::updateAimLine(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // Calculate the endpoint of the gun (tip of the gun)
    float gunLength = gun.getSize().x;               // Assuming the length of the gun is the size of the rectangle
    float angleRad = gun.getRotation() * PI / 180; // Convert rotation to radians


    // Calculate the gun tip position
    sf::Vector2f gunTip = gun.getPosition() + sf::Vector2f(cos(angleRad) * gunLength, sin(angleRad) * gunLength);
    gunTip.x += 5.0f;

    // Determine the direction vector based on the gun rotation
    sf::Vector2f unitDirection = sf::Vector2f(cos(angleRad), sin(angleRad));

    // Determine how far to extend the line to cross the window boundaries
    float maxDistance = std::max(window.getSize().x, window.getSize().y);

    // Calculate the end point of the line
    sf::Vector2f lineEndPoint = gunTip + unitDirection * maxDistance;

    // Update aim line to start from the gun tip and extend beyond the window
    aimLine[0] = sf::Vertex(gunTip, sf::Color::White);       // Start at the tip of the gun
    aimLine[1] = sf::Vertex(lineEndPoint, sf::Color::White); // End at a distant point in the direction

    // Calculate reflection line
    // Collision detection with window boundaries
    float leftBoundary = 0;
    float rightBoundary = static_cast<float>(window.getSize().x);
    float topBoundary = 0;

    // Variables to hold potential intersection points and distances
    sf::Vector2f intersectPoint;
    float distanceX, distanceY;

    // Check for collision with right and left boundaries
    if (unitDirection.x > 0)
    { // Moving right
        intersectPoint = gunTip + unitDirection * ((rightBoundary - gunTip.x) / unitDirection.x);
        distanceX = (rightBoundary - gunTip.x) / unitDirection.x;
    }
    else
    { // Moving left
        intersectPoint = gunTip + unitDirection * ((leftBoundary - gunTip.x) / unitDirection.x);
        distanceX = (gunTip.x - leftBoundary) / -unitDirection.x;
    }
    sf::Vector2f topIntersect;
    // Check for collision with top boundary
    if (unitDirection.y < 0)
    { // Moving up
        topIntersect = gunTip + unitDirection * ((topBoundary - gunTip.y) / unitDirection.y);
        distanceY = (gunTip.y - topBoundary) / -unitDirection.y;
        if (distanceY < distanceX)
        {
            intersectPoint = topIntersect;
        }
    }

    // Determine reflection direction based on the collided boundary
    sf::Vector2f reflectionDirection;
    if (intersectPoint == topIntersect)
    {
        reflectionDirection = sf::Vector2f(unitDirection.x, -unitDirection.y); // Reflect vertically
    }
    else
    {
        reflectionDirection = sf::Vector2f(-unitDirection.x, unitDirection.y); // Reflect horizontally
    }

    sf::Vector2f reflectionEndPoint = intersectPoint + reflectionDirection * (maxDistance * 2);
    
    reflectionAimLine[0] = sf::Vertex(intersectPoint, sf::Color::White);
    reflectionAimLine[1] = sf::Vertex(reflectionEndPoint, sf::Color::White);
}

// #### shoot function ####
//  calculate the gun tip position where the ball being fired
sf::Vector2f Cannon::calculateGunTipPosition()
{
    float angleRad = (gun.getRotation()) * (PI / 180.0f); // Converting degrees to radians
    float gunLength = gun.getSize().x;                      // Assuming the length is along the x-axis of the rectangle
    return sf::Vector2f(gun.getPosition().x + cos(angleRad) * gunLength,
                        gun.getPosition().y + sin(angleRad) * gunLength);
}

// calculate the direction and the speed of the ball
sf::Vector2f Cannon::calculateFiringVelocity()
{
    float angleRad = (gun.getRotation()) * (PI / 180.0f); // Assuming right is 0 degrees
    float speed = 400.0f;                                   // Speed of the ball
    return sf::Vector2f(cos(angleRad) * speed, sin(angleRad) * speed);
}

void Cannon::handleInput() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isPressed) {
        isPressed = true;
        // Stop rotating the gun while firing
        canRotateGun = false;
        timeSinceLastShot = sf::Time::Zero; // Reset timer for the first shot
    }
}

void Cannon::shoot() {
        if (ammo > 0) {
            sf::Vector2f firingPosition = calculateGunTipPosition(); // Calculate where the ball should start
            sf::Vector2f firingVelocity = calculateFiringVelocity(); // Calculate the initial velocity based on the cannon's orientation

            // Add some randomness to the firing velocity for a "shotgun" effect
            firingVelocity.x += (rand() % 100 - 50) / 100.0f;
            firingVelocity.y += (rand() % 100 - 50) / 100.0f;

            // Create a new ball using smart pointers for automatic memory management
            std::shared_ptr<Ball> newBall = std::make_shared<Ball>();
            newBall->setPosition(firingPosition);
            newBall->setVelocity(firingVelocity);

            // Add the new ball to the vector of balls
            balls.push_back(newBall);

            // Decrease ammo count
            ammo--;
            std::cout << "Ammo: " << ammo << std::endl;
        }
}

void Cannon::updateShooting(sf::Time deltaTime) {
    if (isPressed) {
        timeSinceLastShot += deltaTime;

        // Check if it's time to shoot another ball
        if (timeSinceLastShot >= fireInterval) {
            shoot();
            timeSinceLastShot = sf::Time::Zero; // Reset timer after each shot

            // Stop firing if out of ammo
            if (ammo <= 0) {
                isPressed = false;
                // Allow the gun to rotate again
                canRotateGun = true;
            }
        }
    }
}

void Cannon::reload(int currentLevel) {
    ammo = currentLevel * 10;
}


void Cannon::update(sf::RenderWindow &window) {

    // gun rotate via mouse
    if (canRotateGun) {
        this->updateGunRotation(window);
    }
    this->updateAimLine(window);
}

void Cannon::render(sf::RenderTarget& target) const {
    // Draw the aim line when the cannon is not firing
    if (!isPressed) {
        target.draw(aimLine, 2, sf::Lines);
        target.draw(reflectionAimLine, 2, sf::Lines);
    }

    target.draw(base);
    target.draw(gun);
}

