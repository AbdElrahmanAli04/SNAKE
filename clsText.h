#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering

class clsGameText : public sf::Text {

    

    public:

    clsGameText() {
         }

 
        clsGameText(sf::Font &Font, string Text, int size, sf::Color color, int x, int y , sf::Color OutlineColor = sf::Color::Black) {
            this->setFont(Font);
            this->setString(Text);
            this->setCharacterSize(size);
            this->setFillColor(color);
            this->setPosition(x, y);
            this->setScale(1, 1);
            this->setOutlineThickness(3.0f);
            this->setOutlineColor(OutlineColor);


        }

        // void Intialize_Game_Texts () {
        //     sf::Font GameoverFont , RegularFont ;
        //     GameoverFont.loadFromFile("game_over.ttf") ;
        //     RegularFont.loadFromFile("Playball-Regular.ttf") ;
        
        //     * Gameover_Text = clsGameText(GameoverFont, "Game Over", 150, sf::Color::Red, 250, 50);
        //     * PlayAgain_Text = clsGameText(RegularFont, "Play Again ?", 50, sf::Color::Blue, 30, 370);
        //     * Exit_Text = clsGameText(RegularFont, "Exit", 50, sf::Color::Blue, 600, 370);
        //     * MainMenu_Text = clsGameText(GameoverFont, "Main Menu", 150, Color(34, 139, 34), 250, 100);
        //     * Start_Text = clsGameText(RegularFont, "Start", 50, sf::Color::Blue, 100, 370);        

        // }


};