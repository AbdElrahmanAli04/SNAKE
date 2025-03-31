#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering

#include "clsSnake.h"
#include "clsUtil.h"
#include "clsFood.h"
#include "clsText.h"

using namespace std;
using namespace sf;

// ******* If you want to see the perforamnce while debuging , breakpoint at Increase len

int main() {

    enum Screentype {MainGame , StartMenu , Gameover} ;
    Screentype CurrentScreen = MainGame ;

    int Screen_Width = 800 ; 
    int Screen_Hight = 600 ;
    sf::Font GameoverFont , RegularFont ;
    GameoverFont.loadFromFile("game_over.ttf") ;
    RegularFont.loadFromFile("Playball-Regular.ttf") ;

    clsUtil::SeedRandom();
   //GameCompononets :

    Color WindowColor ; 
    WindowColor.r = 250 , WindowColor.g =  240 , WindowColor.b =  190 ;

    RenderWindow window(VideoMode(Screen_Width, Screen_Hight), "SNAKE");

    clsGameText Gametexts ;
    clsGameText GameoverText = Gametexts.Game_Over(GameoverFont);
    clsGameText PlayAgainText = Gametexts.Play_Again(RegularFont ) ;
    clsGameText ExitText = Gametexts.Exit(RegularFont ) ;

    bool Restart = true ; 

    std::vector<sf::Texture> textures1;
    bool eaten_food = false ;
    vector <clsSnake> Body ;
    vector <Vector2f> Body_Postions;    
    clsSnake Snake;
    clsFood Food  ; 

    Clock gameClock; 

    while (window.isOpen()) {
        Event event;

        switch (CurrentScreen)
        {
        
        case Screentype::MainGame : {

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

            }

            deltaTime = gameClock.restart() ; // Get elapsed time since last frame
        



            // Event handling
            while (window.pollEvent(event)  ) {
                
                if (event.type == Event::Closed || Snake.Ate_It_self(Body)  ) {
                    CurrentScreen = Screentype::Gameover;
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
            break;
        }

        case Screentype::StartMenu :
            break;

        case Screentype ::Gameover : 
            window.clear() ;

            window.draw(GameoverText);
            window.draw (ExitText);

            window.draw (PlayAgainText);
            

            while (window.pollEvent(event)  ) {
                sf::FloatRect MousePostion (float(Mouse::getPosition(window).x) , float (Mouse::getPosition(window).y ) , 1,1) ;

                if ( ExitText.getGlobalBounds().intersects(MousePostion) ) {
                        ExitText.setStyle(Text::Bold) ;

                    if (Mouse::isButtonPressed(Mouse::Button::Left) ) {
                        window.close();
                    }
                }

                else {
                    ExitText.setStyle(Text::Regular) ;
                }


                if ( PlayAgainText.getGlobalBounds().intersects(MousePostion) ) {
                    PlayAgainText.setStyle(Text::Bold) ;

                    if (Mouse::isButtonPressed(Mouse::Button::Left) ) {
                        CurrentScreen = Screentype::MainGame ;
                        Restart = true ;


                    }
                    }

                else {
                    PlayAgainText.setStyle(Text::Regular) ;
                }                




            }

            window.display();
            break;

        }
        }


    return 0;
}


/*
What do we need 
Handle Snake death DONE

The Apple should not respwan on the snakes body ** Not Done yet 

If Snake collide with a wall he should die 
Make a main menu 
Make score board
Make constarains in the snake movement



Bouns
If the Snake pass into wall he should be entring from the another side
Make High Scores list menu





*/

