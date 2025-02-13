#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>  // For rendering
#include "clsFood.h"
#include <iostream>
using namespace std;
using namespace sf;



class clsSnake : public sf::RectangleShape {
    private : 
        short PressedKey = 0 ; 
        bool Is_Alive = true ;  
        bool Change_In_Dir = false ; 
        float Speed = 20000;
        vector <sf::Keyboard::Key> Changing_Dir_Vector = {Keyboard::Key::A} ; 
        Color Snakecolor ; 

    Keyboard::Key Get_Pressed_key(){
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
        return Keyboard::A ;
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

    void MyMove(vector<clsSnake>& Body, Keyboard::Key key, sf::Time Deltatime) {
        if (Is_Head_In_boundries(Body, key)) {
            static sf::Clock clock; // Static clock to track time continuously
            static sf::Time accumulatedTime = sf::Time::Zero; 
    
            accumulatedTime += clock.restart(); // Get time elapsed since last call
    
            double moveInterval = 0.015; // Adjust this value for smooth movement between 0.005 and 0.01
    
            while (accumulatedTime.asSeconds() >= moveInterval) {
                accumulatedTime -= sf::seconds(moveInterval);
    
                // Move the head
                Filler_Movement(Body[0], key, Deltatime);
    
                // Move the body by following the previous segments
                for (size_t i = Body.size() - 1; i >0; i--) {
                    Body[i].setPosition(Body[i - 1].getPosition()); 
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
        Snakecolor.r = 85 , Snakecolor.g = 107 , Snakecolor.b = 47 ;         
        this->setSize({64,64});
            this->setFillColor(Snakecolor);
            this->setPosition(100,100);
            this->setScale(0.6,0.6);
            this->PressedKey = Body.back().PressedKey ; 
    }


    clsSnake (vector <clsSnake> &Body , vector <Vector2f> &Body_Postions , bool Is_head = false ) {
        
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    Snakecolor.r = 85 , Snakecolor.g = 107 , Snakecolor.b = 47 ; 
    this->setSize({64,64});
    this->setFillColor(Snakecolor);
    this->setPosition(100,100);
    this->setScale(0.6,0.6);
    this->setOutlineColor(Color::Black);
    this->setOutlineThickness(3);

    if (Is_head) {
            Body.push_back(*this);
            Body_Postions.push_back(this->getPosition());
    }

    }

    void Movement ( vector <clsSnake> &Body ,  sf::Time Deltatime ) {
        
        Keyboard::Key newKey = Get_Pressed_key();

        if (Changing_Dir_Vector.size()==1){
            Changing_Dir_Vector[0] = newKey ;
        }

        if (newKey!=Body[0].PressedKey && (newKey>=Keyboard::Key::Left && newKey<=Keyboard::Key::Down ))  //Ensures The new key is in our controls && change in dir happens
        {
            Change_In_Dir = true;
            if (Changing_Dir_Vector.back()!= newKey || Changing_Dir_Vector.size() == 1) {
                Changing_Dir_Vector.push_back(newKey);
            }

        }

        else {
            Change_In_Dir = false ; 
        }

        if (newKey != Keyboard::Key::A) {  // If a new key is pressed, update direction
            Body[0].PressedKey = newKey;
        }

        
        switch (Body[0].PressedKey)
        {

        case Keyboard::Key::Down :
            MyMove(Body , Keyboard::Key::Down , Deltatime);
            break;

        case Keyboard::Key::Left :
            MyMove(Body , Keyboard::Key::Left , Deltatime );
            break;

        case Keyboard::Key::Up :
            MyMove(Body , Keyboard::Key::Up , Deltatime );
            break;

        case Keyboard::Key::Right :
            MyMove(Body , Keyboard::Key::Right , Deltatime );
            break;

        default:
            break;
        }

    }   


    void Eat(clsFood &Food , vector <clsSnake> &Body , vector <Vector2f> &Body_Postions) {
        if ( Check_for_eat (Food , Body) ) {
            Food.setRandPostion(Body_Postions);
            Increaselen(Body , Body_Postions , 10);
        }
    }

    bool Check_for_eat (clsFood &Food , vector <clsSnake> &Body  ) {
        if (Food.getGlobalBounds().intersects(Body[0].getGlobalBounds())) {
            return true ; 
        } 
        return false ;
    }    
    
    void Increaselen(vector<clsSnake> &Body, vector<Vector2f> &Body_Postions, int growthRate) {
        if (Body.empty()) return; // Ensure there's at least one segment
    
        Vector2f lastPosition = Body.back().getPosition();  
    
        for (int i = 0; i < growthRate; i++) { 
            clsSnake Filler(Body);  
            Filler.setPosition(lastPosition.x, lastPosition.y);  
    
            Body.push_back(Filler);
            Body_Postions.push_back(Filler.getPosition());
        }
    }
    
    bool Ate_It_self(vector<clsSnake> &Body){
        for (short i = Body.size()-1 ; i>30 ; i--) {
            if (Body[1].getGlobalBounds().intersects(Body[i].getGlobalBounds())) {
                return true ;
            }
        }
        return false ;
    }

    


};

