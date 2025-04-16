#pragma once 

#include "clsSnake.h"
#include <SFML/Window.hpp>
#include "clsMainMenu.h"
#include "clsText.h"


class clsGame {
    private : 
    Color WindowColor  = Color (250,240,190); 
    std::vector<sf::Texture> textures1;
    bool eaten_food = false ;
    vector <clsSnake> Body ;
    vector <Vector2f> Body_Postions;    
    clsSnake Snake;
    clsFood Food  ;
    short Score = 0 ; 
    clsGameText ScoreBoard ; 
    sf::Font RegFont ;

    public : 

    clsGame() {
        RegFont.loadFromFile("assets/Playball-Regular.ttf") ;
    }

    void Setup ( Event &event , RenderWindow &window , Screentype &CurrentScreen , Clock &gameClock ,  bool &Restart) {

        Time deltaTime = gameClock.restart();


        if (Restart) {
            textures1.clear();
            eaten_food = false ;
            Body.clear() ;
            Body_Postions.clear();    
            Snake = clsSnake ( Body , Body_Postions , true );
            Food = clsFood (textures1 ) ;
            Restart = false ;
            gameClock.restart();
            Score = 0 ;
        }

        deltaTime = gameClock.restart() ; // Get elapsed time since last frame
    



    // Event handling
        while (window.pollEvent(event)  ) {
            
            if (event.type == Event::Closed || Snake.Ate_It_self(Body)  ) {
                CurrentScreen = Screentype::Gameover;
            }

        }


        ScoreBoard = clsGameText( RegFont , "Score : " + to_string(Score) , 30  , sf::Color::Red , 30 , 550 ) ;

        
        // Clear the window
        window.clear(WindowColor);

        window.draw(ScoreBoard) ;
        // Draw the sprite
        for (clsSnake &Part : Body) {
        window.draw(Part);
        }
        window.draw(Food);
        Snake.Movement(Body , deltaTime );
        
        //Check for food eating 
        eaten_food = Snake.Check_for_eat (Food , Body , Score) ; 
        if (eaten_food) {
        Snake.Eat(Food , Body , Body_Postions);
        eaten_food = false ;
        }



        // Display the content
        window.display();

    
    }

} ;