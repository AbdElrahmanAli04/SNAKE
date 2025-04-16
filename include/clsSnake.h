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
        float Speed = 2000000;
        vector <sf::Keyboard::Key> Changing_Dir_Vector = {Keyboard::Key::A} ; 
        sf::Color Snakecolor = sf::Color (85,107,47) ; 
        int GrowthRate = 10 ;

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

    //Not used for now but may be used in the future 
    bool Is_Head_In_boundries(vector <clsSnake> &Body , Keyboard::Key key){

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

    //Brings back the snake to screen if it gets out of it 
    void Bring_To_Screen (vector <clsSnake> &Body , Keyboard::Key key) {
        switch (key)
        {

        case Keyboard::Key::Down :
            if (Body[0].getPosition().y > Screen_Hight-64*0.6 ){   
                Body[0].setPosition ( Body[0].getPosition().x , 0) ;
            }
            break;

        case Keyboard::Key::Left :
            if (Body[0].getPosition().x < 0 ){   
                Body[0].setPosition ( Screen_Width-64*0.6 , Body[0].getPosition().y) ;
            }
            break;

        case Keyboard::Key::Up :
            if (Body[0].getPosition().y < 0 ){   
                Body[0].setPosition ( Body[0].getPosition().x , Screen_Hight-64*0.6) ;
            }
            break;
        
        case Keyboard::Key::Right :
            if (Body[0].getPosition().x > Screen_Width-64*0.6 ){   
                Body[0].setPosition ( 0 , Body[0].getPosition().y) ;

            }
        break;

        default:
            break;
        }


    }

    //The logic of Moving by the last postion of the last segemnt
    void MyMove(vector<clsSnake>& Body, Keyboard::Key key, sf::Time &Deltatime) {
        static sf::Clock clock;
        static sf::Time accumulatedTime = sf::Time::Zero;    
    
            
            sf::Time frameTime = clock.restart();
            if (frameTime.asSeconds() > 0.1f) {  // Cap maximum frame time
                frameTime = sf::seconds(0.1f);
            }
            accumulatedTime += frameTime;

            const float moveInterval = 0.015f;
            
            while (accumulatedTime.asSeconds() >= moveInterval) {
                accumulatedTime -= sf::seconds(moveInterval);

                Bring_To_Screen(Body , key) ;  
                Filler_Movement(Body[0], key, Deltatime);
                
                for (size_t i = Body.size() - 1; i > 0; i--) {
                    Body[i].setPosition(Body[i - 1].getPosition());
                }
            }
    }  
    

    //The movemen of any segment except the head
    void Filler_Movement(clsSnake &filler , Keyboard::Key key , Time &Deltatime  ) {


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
    

    clsSnake(){

    }




    clsSnake (vector <clsSnake> &Body , vector <Vector2f> &Body_Postions , bool Is_head = false ) {
        
    this->setSize({64,64});
    this->setFillColor(Snakecolor);
    this->setPosition(100,100);
    this->setScale(0.6,0.6);

    if (Is_head) {
            this->setOutlineColor(Color::Black);
            this->setOutlineThickness(3);
            Body.push_back(*this);
            Body_Postions.push_back(this->getPosition());
            
            for (int i = 0 ; i<2 ; i++ ){
                Increaselen(Body,Body_Postions); // To add a small tale in the beggining of the game 
            }
    }

    }

    //Handels the changing in direction and prevent the user to move in 2 opposite ways or move in diagonal way 
    void Movement ( vector <clsSnake> &Body ,  sf::Time &Deltatime ) {
        
        Keyboard::Key newKey = Get_Pressed_key();

        if (Changing_Dir_Vector.size()==1){
            Changing_Dir_Vector[0] = newKey ;
        }

        if (newKey!=Body[0].PressedKey && (newKey>=Keyboard::Key::Left && newKey<=Keyboard::Key::Down ) && (((int(newKey)+ Body[0].PressedKey) != 143) && ((int(newKey)+Body[0].PressedKey) != 147)  ))  //Ensures The new key is in our controls && change in dir happens
        {                                                                                                                                                           //The 143 (Left+Right)  and 147 (Down+UP) Gaurntee that the Snake will not move in the opposite direction
            Change_In_Dir = true;
            if (Changing_Dir_Vector.back()!= newKey || Changing_Dir_Vector.size() == 1) {
                Changing_Dir_Vector.push_back(newKey);
                Body[0].PressedKey = newKey;

            }

        }

        else {
            Change_In_Dir = false ; // Just a Dummy Step to understand the logic
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


    //Handeles the Eating mechanism
    void Eat(clsFood &Food , vector <clsSnake> &Body , vector <Vector2f> &Body_Postions) {
        if ( Check_for_eat (Food , Body) ) {
            Food.setRandPostion(Body_Postions);
            Increaselen(Body , Body_Postions );
        }
    }

    bool Check_for_eat (clsFood &Food , vector <clsSnake> &Body  ) {
        if (Food.getGlobalBounds().intersects(Body[0].getGlobalBounds())) {
            return true ; 
        } 
        return false ;
    }    
    
    //Increase the Snake length if it eats an apple 
    void Increaselen(vector<clsSnake> &Body, vector<Vector2f> &Body_Postions) {
        if (Body.empty()) return; // Ensure there's at least one segment
    
        Vector2f lastPosition = Body.back().getPosition();  
    

        for (int i = 0; i < GrowthRate; i++) { 
            clsSnake Filler(Body , Body_Postions);  
            Filler.setPosition(lastPosition.x, lastPosition.y);  
    
            Body.push_back(Filler);
            Body_Postions.push_back(Filler.getPosition());
        }
    }
    
    //Check for death 
    bool Ate_It_self(vector<clsSnake> &Body){


        for (int i = GrowthRate*3+1 ; i<Body.size()-1 ; i+=GrowthRate) {
                if ( Body[0].getGlobalBounds().intersects(Body[i].getGlobalBounds()) ) {
                    return true ;
                }    
            }
        return false ;
    }

    


};

