//https://www.geeksforgeeks.org/naming-convention-in-c/
#include <iostream>
#include "Cannon.h"
#include "Game.h"
using namespace std;
using namespace sf;

int main()
{
    // Create the Game engine for ICE SMASH
    Game game;
    
    // // Load a sprite to display
    // Texture texture;
    // if(!texture.loadFromFile("blue.jpg"))
    //     return EXIT_FAILURE;
    // Sprite sprite(texture);


    // // Creat Heading to display
    // Font font;
    // if (!font.loadFromFile("font.ttf"))
    //     return EXIT_FAILURE;
    // Text text("ICE Smash", font, 50);

    // //Cannon 
    // Cannon cannon;
    // CircleShape base(50);
    // base.setFillColor(Color(150, 50, 250));
    // base.setOutlineThickness(10);
    // base.setOutlineColor(Color(250, 150, 100));
    //     // set origin
    //     // float x = (window.getSize().x / 2.f) - shape.getRadius();
    //     // float y = (window.getSize().y / 2.f) - shape.getRadius();

    //     base.setPosition({590, 670});

    // Vector2f gunBasePosition(635, 725);
    // // Initial angle pointing straight up
    // float baseAngle = 90.0f;
    // RectangleShape gun(Vector2f(100, 10));
    //     gun.rotate(-90);
    //     gun.setFillColor(Color(0, 0, 0));
    //     gun.setPosition(gunBasePosition);

   
    // cannon.add(&base);
    // cannon.add(&gun);
    

    //game loop
    while (game.running())
    {
        //update
        game.update();
        
        //render
        game.render();

    //     // Handle mouse position relative to the gun base
    //     Vector2i mousePos = Mouse::getPosition(window);
    //     Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    //     // Calculate the angle to rotate the gun
    //     float dx = mousePosF.x - gunBasePosition.x;
    //     float dy = mousePosF.y - gunBasePosition.y;
    //     float angle = atan2(dy, dx) * 180 / M_PI;

    //     // Convert angle to be relative to the vertical
    //     float adjustedAngle = angle - baseAngle;


    //     // Set the rotation of the gun
    //     gun.setRotation(angle);

        

    //     window.clear();
    //     window.draw(sprite);
    //     // Draw the string
    //     window.draw(text);
        
    //     window.draw(cannon);
        
    //     window.display();
    // }

    // return EXIT_SUCCESS;
    }
}
