#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering

class clsGameText : public sf::Text {

    private :


    public :


        clsGameText( ) {
        }

        clsGameText Game_Over(  sf::Font &Font) {
            this->setFont(Font);
            this->setString("Game Over") ;
            this->setCharacterSize(150);
            this->setFillColor(sf::Color::Red);
            this->setPosition(250,100);
            this->setScale(1,1) ;
            return *this ;
        }

        clsGameText Play_Again(  sf::Font &Font ) {
            this->setFont(Font);
            this->setString("Play Again ?") ;
            this->setCharacterSize(50);
            this->setFillColor(sf::Color::Blue);
            this->setPosition(30,400);
            this->setScale(1,1) ;
        
            return *this ;
        }      
        
        clsGameText Exit(  sf::Font &Font ) {
            this->setFont(Font);
            this->setString("Exit") ;
            this->setCharacterSize(50);
            this->setFillColor(sf::Color::Blue);
            this->setPosition(600,400);
            this->setScale(1,1) ;
            return *this ;
        }      
        

} ;