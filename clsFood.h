#pragma once
#include"clsUtil.h"
#include <SFML/Graphics.hpp>  // For rendering
#include <math.h>

using namespace std;
using namespace sf;

    int Screen_Width = 800 ; 
    int Screen_Hight = 600 ;

class clsFood : public sf::Sprite {

    public :


    clsFood ( std::vector<sf::Texture> &textures ){
    
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        // Add a new texture to the vector
        textures.emplace_back(); // Adds a new default-constructed texture
        auto& texture1 = textures.back(); // Reference to the newly added texture

        // Load the texture from file
        if (!texture1.loadFromFile("snake-graphics.png" , IntRect(0,64*3,64,64) )) {
            throw std::runtime_error("Failed to load texture from Apple.png");
        }    

    this->setTexture(texture1);
    this->setPosition(200,100); //Change back to Random_X() , Random_Y() After testing 
    this->setScale(0.5,0.5);

    }

    static float Random_X (int From = 0, int To = (Screen_Width-64)) {
        return clsUtil::RandomNumberFromto(From,To) ;
        }

    static float Random_Y(int From = 0 , int To = (Screen_Hight-64)) {
        return clsUtil::RandomNumberFromto(From,To) ;
        }

    void setRandPostion (vector <Vector2f> Body_Postions) {
        do
        {
            this->setPosition(Random_X() , Random_Y());
        } 
        while (this->getGlobalBounds().contains(Body_Postions[0]));
        
    } 

};