#pragma once 
#include "clsMainMenu.h"

class clsGameOver : public clsMainMenu  {
    
    private :

    clsGameText GameoverText , PlayAgainText ;


    public : 


    clsGameOver() {

        GameoverText = clsGameText(GameoverFont, "Game Over", 150, sf::Color::Red, 250, 80 );
        PlayAgainText = clsGameText(RegularFont, "Play Again ?", 50, sf::Color::Blue, 50, 370);    

    }

    void Setup(sf::RenderWindow &window , sf::Event &event , Screentype &CurrentScreen , bool &Restart) {

        window.clear(WindowColor) ;

        window.draw(GameoverText);
        window.draw (ExitText);

        window.draw (PlayAgainText);
        

        while (window.pollEvent(event)  ) {
            sf::FloatRect MousePostion (float(sf::Mouse::getPosition(window).x) , float (sf::Mouse::getPosition(window).y ) , 1,1) ;

            if ( ExitText.getGlobalBounds().intersects(MousePostion) ) {
                    ExitText.setStyle(sf::Text::Bold) ;

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) {
                    window.close();
                }
            }

            else {
                ExitText.setStyle(sf::Text::Regular) ;
            }


            if ( PlayAgainText.getGlobalBounds().intersects(MousePostion) ) {
                PlayAgainText.setStyle(sf::Text::Bold) ;

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) {
                    CurrentScreen = Screentype::MainGame ;
                    Restart = true ;


                }
                }

            else {
                PlayAgainText.setStyle(sf::Text::Regular) ;
            }                




        }

        window.display();


    }
} ;