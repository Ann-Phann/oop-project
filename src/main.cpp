#include <iostream>
#include "../include/GameWindow.h"
#include "../include/Menu.h"

int main(void) {
    GameWindow gameWindow;

    while (gameWindow.running())
    {
        

        //update
        gameWindow.update();
        
        //render
        gameWindow.render();

    }

 \

}
