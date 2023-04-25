#include <iostream>
#include "Game.h"

int main()
{
    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));


    // init Game engine
    Game game;
    
    // Game loop
    while (game.running())
    {
        // Update
       
        game.update();
        // Render
        game.render();
    }

    return 0;
}