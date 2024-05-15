//https://www.geeksforgeeks.org/naming-convention-in-c/
#include <iostream>
#include "../include/Cannon.h"
#include "../include/Game.h"
using namespace std;

int main()
{
    // Create the Game engine for ICE SMASH
    Game game;

    // Setup a clock to measure time delta between updates
    sf::Clock clock;


    
    //game loop
    while (game.running())
    {
        // Calculate time delta (dt)
        sf::Time dt = clock.restart();
        
        //update
        game.update(dt);
        
        //render
        game.render();

    }
}
