#include "../include/Cannon.h"
#include "../include/Ball.h"

// private functions
void Cannon::initializeVariables()
{
    isPressed = false;
}

void Cannon::initializeCannon()
{
    // base initialize
    this->base.setRadius(50.f);
    this->base.setFillColor(sf::Color(150, 50, 250));
    this->base.setOutlineThickness(10.f);
    this->base.setOutlineColor(sf::Color(250, 150, 100));
    float xBase = (1280 / 2.0f) - base.getRadius();
    float yBase = 1024 - base.getRadius();
    this->base.setPosition(xBase, yBase);

    // gun initialize
    this->gun.setSize(sf::Vector2f(120.f, 10.f));
    this->gun.rotate(-90.f);
    this->gun.setFillColor(sf::Color(0, 0, 0));
    // this->gun.setOrigin(gun.getSize().x / 2, gun.getSize().y);  // Origin set to the bottom center
    this->gun.setPosition(base.getPosition().x + base.getRadius(), base.getPosition().y + base.getRadius()); // Position gun on top of the base

    // group shape
    cannonParts.push_back(&base);
    cannonParts.push_back(&gun);

    // initialize ammo
    ammo = 5; // Start with full ammo
    isFiring = false;
}

// constructor and destructor
Cannon::Cannon()
{
    this->initializeVariables();
    this->initializeCannon();
}

Cannon::~Cannon()
{
}

// fire part
//  calculate the gun tip position where the ball being fired
sf::Vector2f Cannon::calculateGunTipPosition()
{
    float angleRad = (gun.getRotation()) * (M_PI / 180.0f); // Converting degrees to radians
    float gunLength = gun.getSize().x;                      // Assuming the length is along the x-axis of the rectangle
    return sf::Vector2f(gun.getPosition().x + cos(angleRad) * gunLength,
                        gun.getPosition().y + sin(angleRad) * gunLength);
}

// calculate the direction and the speed of the ball
sf::Vector2f Cannon::calculateFiringVelocity()
{
    float angleRad = (gun.getRotation()) * (M_PI / 180.0f); // Assuming right is 0 degrees
    float speed = 500.0f;                                   // Speed of the ball
    return sf::Vector2f(cos(angleRad) * speed, sin(angleRad) * speed);
}

// fire the cannon
void Cannon::fireCannon()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (isPressed)
            return;

        isPressed = true;
        sf::Vector2f firingPosition = calculateGunTipPosition(); // Calculate where the ball should start
        sf::Vector2f firingVelocity = calculateFiringVelocity(); // Calculate the initial velocity based on the cannon's orientation

        // Create a new ball using smart pointers for automatic memory management
        std::shared_ptr<Ball> newBall = std::make_shared<Ball>();
        newBall->setPosition(firingPosition);
        newBall->setVelocity(firingVelocity);

        // Add the new ball to the vector of balls
        balls.push_back(newBall);
    }
    else
    {
        isPressed = false;
    }
}

// update gun rotation
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
    float angle = atan2(dy, dx) * 180 / M_PI;

    // limit rotation angle from 20--> 160 degree
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

void Cannon::updateAimLine(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // Calculate the endpoint of the gun (tip of the gun)
    float gunLength = gun.getSize().x;               // Assuming the length of the gun is the size of the rectangle
    float angleRad = gun.getRotation() * M_PI / 180; // Convert rotation to radians

    // Calculate the gun tip position
    sf::Vector2f gunTip = gun.getPosition() + sf::Vector2f(cos(angleRad) * gunLength, sin(angleRad) * gunLength);
    gunTip.x += 5.0f;

    // Determine the direction vector towards the mouse
    sf::Vector2f direction = mousePosF - gunTip;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f unitDirection = direction / length;

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

void Cannon::updateBall(sf::Time dt, sf::RenderWindow &window)
{
    for (auto &ball : this->balls)
    {
        ball->update(dt, window);
    }
}

// update and draw
void Cannon::update(sf::Time dt, sf::RenderWindow &window)
{
    // gun rotate via mouse
    updateGunRotation(window);

    // Update the aim line
    updateAimLine(window);

    // fire Cannon
    fireCannon();
    updateBall(dt, window);

    //
}

void Cannon::ballsHitBlock(Block &block) {
    // for (auto ball : this->balls) {
    //     block.hitBall(*ball);}

    //     if (block.getStrength() <= 0) {
    //         std::cout << "Delete" << std::endl;
    //         delete &block;
    //         //block.~Block();
    //     }
    // }
    for (auto ball : this->balls) {
        block.update(*ball);
        }    
}

int Cannon:: getNumberBall() const
{
    return numberBall;
}

void Cannon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    // Draw aim line
    target.draw(aimLine, 2, sf::Lines, states);
    target.draw(reflectionAimLine, 2, sf::Lines, states);

    // Draw the cannon
    states.transform *= getTransform();
    for (const auto &item : cannonParts)
    {
        target.draw(*item, states);
    }

    // Draw each ball that has been fired
    for (const auto &ball : balls)
    {
        ball->draw(target, states); // Here the ball's draw method is called
    }
}
