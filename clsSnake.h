#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering
#include "clsFood.h"

using namespace std;
using namespace sf;




class clsSnake : public sf::Sprite {
    private : 
        enum enTriggeredButtons {None , R_Arrow , D_Arrow , L_Arrow , U_Arrow  } ;
        short TriggeredButton = 0 ; 
        static vector <clsSnake> Body ;
        bool Is_Alive = true ;  

    void MoveRight () {
        if (Body[0].getPosition().x < Screen_Width-64 && TriggeredButton!=enTriggeredButtons::L_Arrow ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Right) || TriggeredButton == enTriggeredButtons::R_Arrow) {
            TriggeredButton = enTriggeredButtons::R_Arrow ; 
            for (clsSnake &itr : Body) {
                itr.move(0.05 , 0);
            }
        }
    }
    }

    void MoveLeft () {
        if (Body[0].getPosition().x >= 0 && TriggeredButton!=enTriggeredButtons::R_Arrow ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) || TriggeredButton == enTriggeredButtons::L_Arrow ) {
            TriggeredButton = enTriggeredButtons::L_Arrow ; 
            for (clsSnake &itr : Body) {
                itr.move(-0.05 , 0);
            }
        }
    }
    }

    void MoveUP () {
        if (Body[0].getPosition().y >0 && TriggeredButton!=enTriggeredButtons::D_Arrow ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Up) || TriggeredButton == enTriggeredButtons::U_Arrow ) {
            for (clsSnake &itr : Body) {
                itr.move(0 , -0.05);
            }      
            TriggeredButton = enTriggeredButtons::U_Arrow ; 

        }
    }
    }

    void MoveDown () {
        if (Body[0].getPosition().y < Screen_Hight-64 && TriggeredButton!=enTriggeredButtons::U_Arrow ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Down) || TriggeredButton == enTriggeredButtons::D_Arrow ) {
            TriggeredButton = enTriggeredButtons::D_Arrow ; 
            for (clsSnake &itr : Body) {
                itr.move(0 , 0.05);
            }
        }
    }
    }


    public :

    Texture text1 ;


    clsSnake(sf::Texture &sharedTexture, short x = 64*4, short y = 0, short length = 64, short width = 64, bool filler = false) {
        
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        // Add a new texture to the vector
        // textures.emplace_back(); // Adds a new default-constructed texture
        // auto& texture1 = textures.back(); // Reference to the newly added texture

        // Load the texture from file
        if (!sharedTexture.loadFromFile("snake-graphics.png" , IntRect(x, y , length , width) )) {
            throw std::runtime_error("Failed to load texture from Apple.png");
        }


    this->text1 = sharedTexture ;
    this->setTexture(sharedTexture);

    if (filler) {
        this->setPosition(Body[Body.size()-1].getPosition().x-64  , Body[Body.size()-1].getPosition().y );
    }
    Body.push_back(*this);

    // this->setPosition(100.f, 100.f); 
    // this->setScale(0.15,0.15);
    }

    void Movement () {
        MoveRight();
        MoveLeft();
        MoveUP();
        MoveDown();
    }   

    void Eat(clsFood &Food) {
        if (Food.getGlobalBounds().intersects(Body[0].getGlobalBounds())  ) {
            Food.setRandPostion();
            Increaselen();
        }
    }

    void Increaselen(){
        clsSnake Filler ( text1 , 64 , 0 , 64 , 64 , true ) ;
        Body.push_back(Filler);
        Body.pop_back();
    }

    static std::vector<clsSnake>& GetBody() { return Body; } // دالة إرجاع الجسم المشترك


};

std::vector<clsSnake> clsSnake::Body;















    //Set the Vertex array 
    // VertexArray verArray (PrimitiveType::TrianglesStrip , 10) ;

    // verArray[0].position = sf::Vector2f(100.f, 100.f);
    // verArray[1].position = sf::Vector2f(100.f, 164.f);
    // verArray[2].position = sf::Vector2f(164.f, 100.f);
    // verArray[3].position = sf::Vector2f(164.f, 164.f);
    // verArray[4].position = sf::Vector2f(228.f, 100.f);
    // verArray[5].position = sf::Vector2f(228.f, 164.f);
    // verArray[6].position = sf::Vector2f(228.f, 100.f);
    // verArray[7].position = sf::Vector2f(228.f, 164.f);
    // verArray[8].position = sf::Vector2f(292.f, 100.f);
    // verArray[9].position = sf::Vector2f(292.f, 164.f);


    // // define its texture area to be a 25x50 rectangle starting at (0, 0)
    // verArray[0].texCoords = sf::Vector2f(ImageSlice[0] , ImageSlice[0]); //Tail upperleft
    // verArray[1].texCoords = sf::Vector2f(ImageSlice[0] , ImageSlice[1]); //Tail lowerleft
    // verArray[2].texCoords = sf::Vector2f(ImageSlice[1] , ImageSlice[0]); //Tail upper right
    // verArray[3].texCoords = sf::Vector2f(ImageSlice[1] , ImageSlice[1]); //Tail lower right
    // verArray[4].texCoords = sf::Vector2f(ImageSlice[2] , ImageSlice[0]); //Tail upper right
    // verArray[5].texCoords = sf::Vector2f(ImageSlice[2] , ImageSlice[1]); //Tail lower right
    // verArray[6].texCoords = sf::Vector2f(ImageSlice[4] , ImageSlice[0]); //Tail upper right
    // verArray[7].texCoords = sf::Vector2f(ImageSlice[4] , ImageSlice[1]); //Tail lower right
    // verArray[8].texCoords = sf::Vector2f(ImageSlice[5] , ImageSlice[0]); //Tail upper right
    // verArray[9].texCoords = sf::Vector2f(ImageSlice[5] , ImageSlice[1]); //Tail lower right



    // // verArray[4].texCoords = sf::Vector2f(4*square_side_len, 2*square_side_len); //Tail upperleft
    // // verArray[5].texCoords = sf::Vector2f(4*square_side_len, 2*square_side_len); //Tail upperleft
    // // verArray[6].texCoords = sf::Vector2f(4*square_side_len, 3*square_side_len); //Tail lowerleft
    // // verArray[7].texCoords = sf::Vector2f(5*square_side_len, 2*square_side_len); //Tail upper right
    // // verArray[8].texCoords = sf::Vector2f(5*square_side_len, 3*square_side_len); //Tail lower right

