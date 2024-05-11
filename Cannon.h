#ifndef CANNON_H
#define CANNON_H
#include <SFML/Graphics.hpp>
#include <vector>

class Cannon : public sf::Drawable, public sf::Transformable {
    private:
        std::vector<sf::Drawable*> cannonParts;
    
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    public:
        Cannon();
        void add(sf::Drawable* part);
};   

#endif