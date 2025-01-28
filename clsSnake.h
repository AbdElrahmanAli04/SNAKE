#pragma once

#include <SFML/Graphics.hpp>  // For rendering
#include "clsFood.h"

using namespace std;
using namespace sf;

class clsSnake : public sf::Sprite {
    private : 
    
    bool Is_Alive = true ;  

    void MoveRight () {
        if (this->getPosition().x < 715 ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
            this->move(0.1,0);
        }
    }
    }

    void MoveLeft () {
        if (this->getPosition().x >= 0 ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
            this->move(-0.1,0);
        }
    }
    }

    void MoveUP () {
        if (this->getPosition().y >0 ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
            this->move(0,-0.1);
        }
    }
    }

    void MoveDown () {
        if (this->getPosition().y < 520 ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
            this->move(0,0.1);
        }
    }
    }


    public :

    Sprite Snake ; 


    clsSnake ( std::vector<sf::Texture> &textures ){
        
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        // Add a new texture to the vector
        textures.emplace_back(); // Adds a new default-constructed texture
        auto& texture1 = textures.back(); // Reference to the newly added texture

        // Load the texture from file
        if (!texture1.loadFromFile("6945949.png")) {
            throw std::runtime_error("Failed to load texture from Apple.png");
        }


    texture1.getSize().x ; 
    texture1.getSize().y ; 


    this->setTexture(texture1);
    this->setPosition(100.f, 100.f); 
    this->setScale(0.15,0.15);

    }

    void Movement () {
        MoveRight();
        MoveLeft();
        MoveUP();
        MoveDown();
    }   

    void Eat(clsFood &Food) {
        if (Food.getGlobalBounds().intersects(this->getGlobalBounds())  ) {
            Food.setRandPostion();
        }




    }

};