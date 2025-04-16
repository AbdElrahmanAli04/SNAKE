#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering

#include "clsSnake.h"
#include "clsMainMenu.h"
#include "clsGameOver.h"
#include "clsGame.h"

using namespace std;
using namespace sf;

Screentype CurrentScreen = StartMenu ;

RenderWindow window(VideoMode(Screen_Width, Screen_Hight), "SNAKE" );

Clock gameClock; 
clsMainMenu MainMenu ; 
clsGameOver GameOver ;
clsGame Game ;

bool Restart = true ; 



int main() {

    clsUtil::SeedRandom();



    while (window.isOpen()) {
        Event event;

        switch (CurrentScreen)
        
        {
            case Screentype::StartMenu : {

                MainMenu.Setup(window , event , CurrentScreen) ;
                break;
            
            }
    
        
            case Screentype::MainGame : {
                Game.Setup(event, window ,CurrentScreen , gameClock , Restart) ;
                break;
            }


        
            case Screentype ::Gameover : 
                GameOver.Setup(window , event , CurrentScreen , Restart) ;
                break;

            }
            }


    return 0;
}


// ******* If you want to see the perforamnce while debuging , breakpoint at Increase len
