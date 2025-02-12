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

    int Screen_Width = 800 ; 
    int Screen_Hight = 600 ;
    clsUtil::SeedRandom();
    std::vector<sf::Texture> textures1;
    vector <clsSnake> Body ;
    vector <Vector2f> Body_Postions;
    bool eaten_food = false ;


 
   //GameCompononets :
    RenderWindow window(VideoMode(Screen_Width, Screen_Hight), "SNAKE");
    clsSnake Snake( Body , Body_Postions , true );
    clsFood Food (textures1 ) ; 

    int objects_count = 0;

    // Main game loop
    while (window.isOpen()) {
    

        // Event handling
        Event event;
        while (window.pollEvent(event)) {
            
            if (event.type == Event::Closed) {
                window.close();
            }

        }

        // Clear the window
        window.clear(Color::Green);

        // Draw the sprite
        for (clsSnake &Part : Body) {
        window.draw(Part);
        }
        window.draw(Food);
        Snake.Movement(Body);
        
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




