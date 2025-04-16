#pragma once 
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering
#include "clsText.h"

enum Screentype {MainGame , StartMenu , Gameover} ;


class clsMainMenu {

    private : 

        clsGameText Main_Menu_Text , Start_Text ;


    protected : 

        sf::Font GameoverFont , RegularFont ;
        sf::Color WindowColor  = sf::Color (250,240,190); 
        clsGameText ExitText  ;




    public : 

    clsMainMenu () {
        //Setting up the fonts and the Texts
        GameoverFont.loadFromFile("game_over.ttf") ;
        RegularFont.loadFromFile("Playball-Regular.ttf") ;

        ExitText = clsGameText(RegularFont, "Exit", 50, sf::Color::Blue, 600, 370);
        Main_Menu_Text = clsGameText(GameoverFont, "Main Menu", 150, sf::Color(34, 139, 34), 250, 100);
        Start_Text = clsGameText(RegularFont, "Start", 50, sf::Color::Blue, 100, 370);
    
    }


    void Setup(sf::RenderWindow &window , sf::Event &event , Screentype &CurrentScreen  ) {
        window.clear(WindowColor) ;
    
        window.draw(Main_Menu_Text);
        window.draw (ExitText);
    
        window.draw (Start_Text);
        
    
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
    
    
            if ( Start_Text.getGlobalBounds().intersects(MousePostion) ) {
                Start_Text.setStyle(sf::Text::Bold) ;
    
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) {
                    CurrentScreen = Screentype::MainGame ;
                }
                }
    
            else {
                Start_Text.setStyle(sf::Text::Regular) ;
            }                
    
        }   
    
    
        window.display();
    
    
    }



} ;