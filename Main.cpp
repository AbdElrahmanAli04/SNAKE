#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering

#include "clsSnake.h"
#include "clsUtil.h"
#include "clsFood.h"


using namespace std;
using namespace sf;



int main() {

    int Screen_Width = 800 ; 
    int Screen_Hight = 600 ;

    clsUtil::SeedRandom();

    std::vector<sf::Texture> textures1;
    std::vector<sf::Texture> textures2;


    //GameCompononets :
    RenderWindow window(VideoMode(Screen_Width, Screen_Hight), "SNAKE");
    clsSnake Snake ( textures1 );

    // Sprite Snake = SnakeIntializer(textures1);
    clsFood Food = (textures2) ; 



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
        window.draw(Snake.Body , &Snake.text);
        window.draw(Food);
        Snake.Movement();
        Snake.Eat(Food);

        // Display the content
        window.display();
    }

    return 0;
}





/*
What do we need to edit ? 

--Change the snake to a one that it's tail get longer when it eats more apples .
--Make the eating mechanism 
--Make a Score board that increase afte eating apples
--make obstacles to be avoided
--Cahang the snake.snake
--








*/