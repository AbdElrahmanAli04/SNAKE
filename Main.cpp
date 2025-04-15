#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering

#include "clsSnake.h"
#include "clsUtil.h"
#include "clsFood.h"
#include "clsText.h"
#include "clsGame.h"


using namespace std;
using namespace sf;

// ******* If you want to see the perforamnce while debuging , breakpoint at Increase len

int main() {

    
    sf::Font GameoverFont , RegularFont ;
    GameoverFont.loadFromFile("game_over.ttf") ;
    RegularFont.loadFromFile("Playball-Regular.ttf") ;


    enum Screentype {MainGame , StartMenu , Gameover} ;
    Screentype CurrentScreen = StartMenu ;

    int Screen_Width = 800 ; 
    int Screen_Hight = 600 ;

    clsUtil::SeedRandom();
   //GameCompononets :

    Color WindowColor  = Color (250,240,190); 

    RenderWindow window(VideoMode(Screen_Width, Screen_Hight), "SNAKE");

    clsGameText GameoverText = clsGameText(GameoverFont, "Game Over", 150, sf::Color::Red, 250, 80 );
    clsGameText PlayAgainText = clsGameText(RegularFont, "Play Again ?", 50, sf::Color::Blue, 50, 370);
    clsGameText ExitText = clsGameText(RegularFont, "Exit", 50, sf::Color::Blue, 600, 370);
    clsGameText Main_Menu_Text = clsGameText(GameoverFont, "Main Menu", 150, Color(34, 139, 34), 250, 100);
    clsGameText Start_Text = clsGameText(RegularFont, "Start", 50, sf::Color::Blue, 100, 370);

    // For Main_Menu_Text, add the outline after construction:


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


            case Screentype::StartMenu : {

        
            
                window.clear(WindowColor) ;
    
                window.draw(Main_Menu_Text);
                window.draw (ExitText);
    
                window.draw (Start_Text);
                
    
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
    
    
                    if ( Start_Text.getGlobalBounds().intersects(MousePostion) ) {
                        Start_Text.setStyle(Text::Bold) ;
    
                        if (Mouse::isButtonPressed(Mouse::Button::Left) ) {
                            CurrentScreen = Screentype::MainGame ;
                        }
                        }
    
                    else {
                        Start_Text.setStyle(Text::Regular) ;
                    }                
    
                }   
            
    
                window.display();
                break;
            
            }
    
        
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
                
                if (event.type == Event::Closed /*|| Snake.Ate_It_self(Body)*/  ) {
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


        
        case Screentype ::Gameover : 
            window.clear(WindowColor) ;

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

