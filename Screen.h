#pragma once
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class clsScreen {

    private : 

    public : 
    
    sf::Window _Screen ; 

    clsScreen() {
        _Screen.create(sf::VideoMode(800,600) , "SNAKE GAME") ;
    }

    
};