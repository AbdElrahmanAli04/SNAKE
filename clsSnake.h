#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering
#include "clsFood.h"

using namespace std;
using namespace sf;




class clsSnake : public sf::RectangleShape {
    private : 
        short PressedKey = 0 ; 
        bool Is_Alive = true ;  

    short Get_Pressed_key(){
        if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
            return Keyboard::Key::Right ; 
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
            return  Keyboard::Key::Down ; 
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
            return  Keyboard::Key::Left ; 
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
            return  Keyboard::Key::Up ; 
        }
        return 0 ;
    }

    void MoveRight (vector <clsSnake> &Body) {
        if (Body[0].getPosition().x < Screen_Width-64*0.6 ){   
            for (clsSnake &itr : Body) {
                if (itr.getPosition() == Body[0].getPosition()){ //Makes Sure the Head is moving right
                    itr.move(0.04, 0);                 
                }

        }
    }
    }

    void MoveDown (vector <clsSnake> &Body) {
        if (Body[0].getPosition().y < Screen_Hight-64*0.6 ){   
            for (clsSnake &itr : Body) {
                if (itr.getPosition() == Body[0].getPosition()){
                    itr.move(0 , 0.04);                    
                }   
                }
    }
    }

    void MoveLeft (vector <clsSnake> &Body) {
        if (Body[0].getPosition().x > 0 ){   
            for (clsSnake &itr : Body) {
                if (itr.getPosition() == Body[0].getPosition()){
                    itr.move(-0.04, 0);                    
                }
                }
    }
    }

    void MoveUp (vector <clsSnake> &Body) {
        if (Body[0].getPosition().y > 0 ){   
            for (clsSnake &itr : Body) {
                if (itr.getPosition() == Body[0].getPosition()){
                    itr.move(0, -0.04);                    
                }
                }
    }
    }

    public :

    clsSnake () {
            this->setSize({64,64});
            this->setFillColor(Color::Magenta);
            this->setPosition(100,100);
            this->setScale(0.6,0.6);
    }


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

    void Movement ( vector <clsSnake> &Body ) {
        
        short newKey = Get_Pressed_key();

        if (newKey != 0) {  // If a new key is pressed, update direction
            PressedKey = newKey;
        }

        
        switch (PressedKey)
        {

        case Keyboard::Key::Down :
            MoveDown(Body);
            break;

        case Keyboard::Key::Left :
            MoveLeft(Body);
            break;

        case Keyboard::Key::Up :
            MoveUp(Body);
            break;
        
        case Keyboard::Key::Right :
            MoveRight(Body);
            break;

        default:
            break;
        }

    }   

    void Eat(clsFood &Food , vector <clsSnake> &Body , vector <Vector2f> &Body_Postions) {
        if ( Check_for_eat (Food , Body) ) {
            Food.setRandPostion(Body_Postions);
            // Increaselen(Body , Body_Postions);
        }
    }

    void Increaselen(vector <clsSnake> &Body, vector <Vector2f> &Body_Postions) {
    clsSnake Filler; 
    Vector2f lastPosition = Body.back().getPosition();  // Get last segment position

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

