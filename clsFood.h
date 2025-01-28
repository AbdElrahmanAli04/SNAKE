#pragma once
#include"clsUtil.h"
#include <SFML/Graphics.hpp>  // For rendering

using namespace std;
using namespace sf;

class clsFood : public sf::Sprite {

    
    
    public :


    clsFood ( std::vector<sf::Texture> &textures ){
    
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        // Add a new texture to the vector
        textures.emplace_back(); // Adds a new default-constructed texture
        auto& texture1 = textures.back(); // Reference to the newly added texture

        // Load the texture from file
        if (!texture1.loadFromFile("Apple.png")) {
            throw std::runtime_error("Failed to load texture from Apple.png");
        }
    

    this->setTexture(texture1);
    this->setPosition(Random_X() , Random_Y()); 
    this->setScale(0.1,0.1);

    }

    static float Random_X (int From = 0, int To = 765) {
        return clsUtil::RandomNumberFromto(From,To) ;
        }

    static float Random_Y(int From = 0 , int To = 565) {
        return clsUtil::RandomNumberFromto(From,To) ;
        }

    void setRandPostion () {
        this->setPosition(Random_X() , Random_Y());
    } 

};