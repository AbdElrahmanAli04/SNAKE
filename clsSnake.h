#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering
#include "clsFood.h"

using namespace std;
using namespace sf;




class clsSnake : public sf::RectangleShape {
    private : 
        enum enTriggeredButtons {None , R_Arrow , D_Arrow , L_Arrow , U_Arrow  } ;
        short TriggeredButton = 0 ; 
        bool Is_Alive = true ;  

    void MoveRight (vector <clsSnake> &Body) {
        if (Body[0].getPosition().x < Screen_Width-64 && TriggeredButton!=enTriggeredButtons::L_Arrow ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Right) || TriggeredButton == enTriggeredButtons::R_Arrow) {
            TriggeredButton = enTriggeredButtons::R_Arrow ; 
            for (clsSnake &itr : Body) {
                itr.move(0.05 , 0);
            }
        }
    }
    }

    void MoveLeft (vector <clsSnake> &Body) {
        if (Body[0].getPosition().x >= 0 && TriggeredButton!=enTriggeredButtons::R_Arrow ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) || TriggeredButton == enTriggeredButtons::L_Arrow ) {
            TriggeredButton = enTriggeredButtons::L_Arrow ; 
            for (clsSnake &itr : Body) {
                itr.move(-0.05 , 0);
            }
        }
    }
    }

    void MoveUP (vector <clsSnake> &Body) {
        if (Body[0].getPosition().y >0 && TriggeredButton!=enTriggeredButtons::D_Arrow ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Up) || TriggeredButton == enTriggeredButtons::U_Arrow ) {
            for (clsSnake &itr : Body) {
                itr.move(0 , -0.05);
            }      
            TriggeredButton = enTriggeredButtons::U_Arrow ; 

        }
    }
    }

    void MoveDown (vector <clsSnake> &Body) {
        if (Body[0].getPosition().y < Screen_Hight-64 && TriggeredButton!=enTriggeredButtons::U_Arrow ){   
        if (Keyboard::isKeyPressed(Keyboard::Key::Down) || TriggeredButton == enTriggeredButtons::D_Arrow ) {
            for (clsSnake &itr : Body) {
                itr.move(0 , 0.05);

            }

            TriggeredButton = enTriggeredButtons::D_Arrow ; 
        }
    }
    }


    public :


    clsSnake (vector <clsSnake> &Body , vector <Vector2f> &Body_Postions , bool Is_head = false ) {
        
        std::srand(static_cast<unsigned>(std::time(nullptr)));

    this->setSize({64,64});
    this->setFillColor(Color::Magenta);
    this->setPosition(100,100);
    this->setScale(0.6,0.6);

    if (Is_head) {
            Body.push_back(*this);
            Body_Postions.push_back(this->getPosition());
    }

    }

    clsSnake () {
            this->setSize({64,64});
            this->setFillColor(Color::Magenta);
            this->setPosition(100,100);
            this->setScale(0.6,0.6);
    }


    void Movement ( vector <clsSnake> &Body ) {
        MoveRight(Body);
        MoveLeft(Body);
        MoveUP(Body);
        MoveDown(Body);
    }   

    void Eat(clsFood &Food , vector <clsSnake> &Body , vector <Vector2f> &Body_Postions) {
        if ( Check_for_eat (Food , Body) ) {
            Food.setRandPostion(Body_Postions);
            Increaselen(Body , Body_Postions);
        }
    }

    void Increaselen(vector <clsSnake> &Body, vector <Vector2f> &Body_Postions) {
    clsSnake Filler;  // Default constructor
    Vector2f lastPosition = Body.back().getPosition();  // Get last segment position
    
    // Offset new segment based on direction (this assumes movement is horizontal)
    Filler.setPosition(lastPosition.x - (64 * 0.6), lastPosition.y); 
    
    Body.push_back(Filler);
    Body_Postions.push_back(Filler.getPosition());
}

        
    bool Check_for_eat (clsFood &Food , vector <clsSnake> &Body  ) {
        if (Food.getGlobalBounds().intersects(Body[0].getGlobalBounds())) {
            return true ; 
        } 
        return false ;
    }        

    







};

