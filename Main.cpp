#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering

#include "clsSnake.h"
#include "clsUtil.h"
#include "clsFood.h"


using namespace std;
using namespace sf;

// ******* If you want to see the perforamnce while debuging , breakpoint at Increase len

int main() {

    enum Screentype {MainGame , StartMenu , Gameover} ;

    int Screen_Width = 800 ; 
    int Screen_Hight = 600 ;
    
    clsUtil::SeedRandom();
    std::vector<sf::Texture> textures1;
    vector <clsSnake> Body ;
    vector <Vector2f> Body_Postions;
    bool eaten_food = false ;

    
 
   //GameCompononets :
    Clock clock; // Global game clock
    Time deltaTime;
    Color WindowColor ; 
    WindowColor.r = 250 , WindowColor.g =  240 , WindowColor.b =  190 ;

    RenderWindow window(VideoMode(Screen_Width, Screen_Hight), "SNAKE");
    clsSnake Snake( Body , Body_Postions , true );
    clsFood Food (textures1 ) ; 

    while (window.isOpen()) {

        deltaTime = clock.restart(); // Get elapsed time since last frame

        // Event handling
        Event event;
        while (window.pollEvent(event)  ) {
            
            if (event.type == Event::Closed || Snake.Ate_It_self(Body)  ) {
                window.close();
            }

        }

        // Clear the window
        window.clear(WindowColor);

        // Draw the sprite
        for (clsSnake &Part : Body) {
        window.draw(Part);
        }
        window.draw(Food);
        Snake.Movement(Body , deltaTime );
        
        //Check for food eating 
        eaten_food = Snake.Check_for_eat (Food , Body) ; 
        if (eaten_food) {
        Snake.Eat(Food , Body , Body_Postions);
        eaten_food = false ;
        }

        

        // Display the content
        window.display();
    }

    return 0;
}


/*
What do we need 
Handle Snake death DONE

The Apple should not respwan on the snakes body ** Not Done yet 

If Snake collide with a wall he should die 
Make a main menu 
Make a play again menu 
Make score board


Bouns
If the Snake pass into wall he should be entring from the another side
Make High Scores list menu





*/

