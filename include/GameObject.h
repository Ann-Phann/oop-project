#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * @brief The GameObject class serves as an abstract base class for all game objects.
 *
 * This class defines the interface for game objects, which includes updating and rendering methods.
 */
class GameObject : public sf::Sprite {
public:
    // Pure virtual functions
    virtual void update(sf::RenderWindow &window) = 0;   // Updates the game object
    virtual void render(sf::RenderTarget& target) const = 0; // Renders the game object

    // Destructor
    virtual ~GameObject() {}
};

#endif // GAMEOBJECT_H
