#pragma once
#include <SFML/Graphics.hpp>
#include "clsSnake.h"
#include "clsFood.h"
#include "clsText.h"

class clsGame {
public:
    enum Screentype {MainGame, StartMenu, Gameover};
    Screentype CurrentScreen = StartMenu;
    
    const int Screen_Width = 800;
    const int Screen_Hight = 600;
    sf::RenderWindow window;
    sf::Font GameoverFont, RegularFont;
    
    sf::Color WindowColor;
    sf::Color MainMenu_Color;
    
    // Game components
    clsGameText GameoverText = clsGameText(GameoverFont, "Game Over", 150, sf::Color::Red, 250, 50);
    clsGameText PlayAgainText = clsGameText(RegularFont, "Play Again ?", 50, sf::Color::Blue, 30, 370);
    clsGameText ExitText = clsGameText(RegularFont, "Exit", 50, sf::Color::Blue, 600, 370);
    clsGameText Main_Menu_Text = clsGameText(GameoverFont, "Main Menu", 150, Color(34, 139, 34), 250, 100);
    clsGameText Start_Text = clsGameText(RegularFont, "Start", 50, sf::Color::Blue, 100, 370);

    
    bool Restart;
    std::vector<sf::Texture> textures1;
    bool eaten_food;
    std::vector<clsSnake> Body;
    std::vector<sf::Vector2f> Body_Postions;
    clsSnake Snake;
    clsFood Food;
    sf::Clock gameClock;


};