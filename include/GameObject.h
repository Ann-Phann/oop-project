#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<iostream>
#include <SFML/Graphics.hpp>

class GameObject : public sf::Sprite {
public:
    virtual void update(sf::RenderWindow &window) = 0;
    virtual void render(sf::RenderTarget& target) const = 0;
    virtual ~GameObject() {}
};

#endif // GAMEOBJECT_H
