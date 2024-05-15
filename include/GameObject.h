#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <iostream>
#include <SFML/Graphics.hpp>

class GameObject {
    public:
        virtual void update() = 0;
        virtual void render(sf::RenderWindow& window) const = 0;
        virtual ~GameObject();
};

#endif // GAME_OBJECT