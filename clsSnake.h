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
        bool Change_In_Dir = false ; 
        float Speed = 20000;

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

    bool Is_Head_In_boundries(vector <clsSnake> &Body , Keyboard::Key key){
        clsSnake Head = Body[0] ;
        switch (key)
        {

        case Keyboard::Key::Down :
            if (Body[0].getPosition().y < Screen_Hight-64*0.6 ){   
            return true ;
        }
            break;

        case Keyboard::Key::Left :
            if (Body[0].getPosition().x > 0 ){   
                return true ;
            }
            break;

        case Keyboard::Key::Up :
            if (Body[0].getPosition().y > 0 ){   
                return true ;
            }
            break;
        
        case Keyboard::Key::Right :
            if (Body[0].getPosition().x < Screen_Width-64*0.6 ){   
            return true ;
            }
        break;

        default:
            return false ; 
            break;
        }
        return false ;
    }

    void MyMove(vector <clsSnake> &Body , Keyboard::Key key  ) {
        if (Is_Head_In_boundries(Body , key)){
            sf::Clock clock; // starts the clock
            sf::Time Deltatime ; 
            for (clsSnake &itr : Body) { 
                if (itr.getPosition() == Body[0].getPosition()){ //Makes Sure the Head is moving right
                    clock.restart();
                    Deltatime = clock.getElapsedTime();
                    Filler_Movement(itr,key , Deltatime);
                }
                else {
                    Filler_Movement(itr,key , Deltatime);
                }
        }

        }
    }

    //The movemen of any segment except the head
    void Filler_Movement(clsSnake &filler , Keyboard::Key key , Time Deltatime  ) {


        switch (key)
        {

        case Keyboard::Key::Down :
            filler.move(0 , Speed*Deltatime.asSeconds());                    
            break;

        case Keyboard::Key::Left :
            filler.move(-Speed*Deltatime.asSeconds(), 0);                    
            break;

        case Keyboard::Key::Up :
            filler.move(0, -Speed*Deltatime.asSeconds());                    
            break;
        
        case Keyboard::Key::Right :
            filler.move(Speed*Deltatime.asSeconds(), 0);                    
            break;

        default:
            break;
        }

    }

    public :

    clsSnake (vector <clsSnake> &Body ) {
            this->setSize({64,64});
            this->setFillColor(Color::Magenta);
            this->setPosition(100,100);
            this->setScale(0.6,0.6);
            this->PressedKey = Body.back().PressedKey ; 
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

        if (newKey!=Body[0].PressedKey && (newKey>=Keyboard::Key::Left && newKey<=Keyboard::Key::Down ))  //Ensures The new key is in our controls && change in dir happens
        {
            Change_In_Dir = true;
        }

        else {
            Change_In_Dir = false ; 
        }

        if (newKey != 0) {  // If a new key is pressed, update direction
            Body[0].PressedKey = newKey;
        }

        
        switch (Body[0].PressedKey)
        {

        case Keyboard::Key::Down :
            MyMove(Body , Keyboard::Key::Down );
            break;

        case Keyboard::Key::Left :
            MyMove(Body , Keyboard::Key::Left );
            break;

        case Keyboard::Key::Up :
            MyMove(Body , Keyboard::Key::Up );
            break;

        case Keyboard::Key::Right :
            MyMove(Body , Keyboard::Key::Right );
            break;

        default:
            break;
        }

    }   


    void Eat(clsFood &Food , vector <clsSnake> &Body , vector <Vector2f> &Body_Postions) {
        if ( Check_for_eat (Food , Body) ) {
            Food.setRandPostion(Body_Postions);
            Increaselen(Body , Body_Postions);
        }
    }

    bool Check_for_eat (clsFood &Food , vector <clsSnake> &Body  ) {
        if (Food.getGlobalBounds().intersects(Body[0].getGlobalBounds())) {
            return true ; 
        } 
        return false ;
    }    
    
    
    void Increaselen(vector <clsSnake> &Body, vector <Vector2f> &Body_Postions) {
    clsSnake Filler (Body)  ; 
    Vector2f lastPosition = Body.back().getPosition();  // Get last segment position

    Filler.setPosition(lastPosition.x - (64 * 0.6), lastPosition.y); 
    
    Body.push_back(Filler);
    Body_Postions.push_back(Filler.getPosition());
}

        


    







};

