#include <iostream>
#include "../include/GameWindow.h"

int main() {
    GameWindow gameWindow;
     //game loop
    while (gameWindow.running())
    {
        

        //update
        gameWindow.update();
        
        //render
        gameWindow.render();

    }
}
