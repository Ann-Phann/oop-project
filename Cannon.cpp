#include "Cannon.h"

Cannon::Cannon()
{
    
}

void Cannon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
        for (const auto& item : cannonParts) {
            target.draw(*item, states);
        }
}

void Cannon::add(sf::Drawable* part) {
    cannonParts.push_back(part);
}

