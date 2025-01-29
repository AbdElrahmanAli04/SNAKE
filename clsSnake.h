#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering
#include "clsFood.h"

using namespace std;
using namespace sf;


class clsSnake : public sf::Sprite {
    private : 

    int ImageSlice[6] = {
        0, 64, 128, 192, 256 , 320  // Row 0
    };
    
    int square_side_len = 64 ;
    bool Is_Alive = true ;  

    void MoveRight () {
        if (this->getPosition().x < Screen_Width-64 ){   
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
        if (this->getPosition().y < Screen_Hight-64 ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
            this->move(0,0.1);
        }
    }
    }


    public :

    Texture text ;
    VertexArray Body ;

    clsSnake ( std::vector<sf::Texture> &textures ){
        
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        // Add a new texture to the vector
        textures.emplace_back(); // Adds a new default-constructed texture
        auto& texture1 = textures.back(); // Reference to the newly added texture

        // Load the texture from file
        if (!texture1.loadFromFile("snake-graphics.png" )) {
            throw std::runtime_error("Failed to load texture from Apple.png");
        }


    this->text = texture1 ;
    this->setTexture(texture1);
    // this->setPosition(100.f, 100.f); 
    // this->setScale(0.15,0.15);

    //Set the Vertex array 
    VertexArray verArray (PrimitiveType::TrianglesStrip , 10) ;

    verArray[0].position = sf::Vector2f(100.f, 100.f);
    verArray[1].position = sf::Vector2f(100.f, 164.f);
    verArray[2].position = sf::Vector2f(164.f, 100.f);
    verArray[3].position = sf::Vector2f(164.f, 164.f);
    verArray[4].position = sf::Vector2f(228.f, 100.f);
    verArray[5].position = sf::Vector2f(228.f, 164.f);
    verArray[6].position = sf::Vector2f(228.f, 100.f);
    verArray[7].position = sf::Vector2f(228.f, 164.f);
    verArray[8].position = sf::Vector2f(292.f, 100.f);
    verArray[9].position = sf::Vector2f(292.f, 164.f);


    // define its texture area to be a 25x50 rectangle starting at (0, 0)
    verArray[0].texCoords = sf::Vector2f(ImageSlice[0] , ImageSlice[0]); //Tail upperleft
    verArray[1].texCoords = sf::Vector2f(ImageSlice[0] , ImageSlice[1]); //Tail lowerleft
    verArray[2].texCoords = sf::Vector2f(ImageSlice[1] , ImageSlice[0]); //Tail upper right
    verArray[3].texCoords = sf::Vector2f(ImageSlice[1] , ImageSlice[1]); //Tail lower right
    verArray[4].texCoords = sf::Vector2f(ImageSlice[2] , ImageSlice[0]); //Tail upper right
    verArray[5].texCoords = sf::Vector2f(ImageSlice[2] , ImageSlice[1]); //Tail lower right
    verArray[6].texCoords = sf::Vector2f(ImageSlice[4] , ImageSlice[0]); //Tail upper right
    verArray[7].texCoords = sf::Vector2f(ImageSlice[4] , ImageSlice[1]); //Tail lower right
    verArray[8].texCoords = sf::Vector2f(ImageSlice[5] , ImageSlice[0]); //Tail upper right
    verArray[9].texCoords = sf::Vector2f(ImageSlice[5] , ImageSlice[1]); //Tail lower right



    // verArray[4].texCoords = sf::Vector2f(4*square_side_len, 2*square_side_len); //Tail upperleft
    // verArray[5].texCoords = sf::Vector2f(4*square_side_len, 2*square_side_len); //Tail upperleft
    // verArray[6].texCoords = sf::Vector2f(4*square_side_len, 3*square_side_len); //Tail lowerleft
    // verArray[7].texCoords = sf::Vector2f(5*square_side_len, 2*square_side_len); //Tail upper right
    // verArray[8].texCoords = sf::Vector2f(5*square_side_len, 3*square_side_len); //Tail lower right



    this->Body = verArray ; 


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