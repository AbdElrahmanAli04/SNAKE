#pragma once 
#include <iostream>
#include <limits>
#include <vector>


using namespace std ; 


class clsUtil {
    private : 


    public : 
        static void SeedRandom() {
            srand((unsigned)time(NULL)); 
            }


        static float RandomNumberFromto(int From, int To){
            float randNum = rand() % (To - From + 1) + From;
            return randNum;
                }

        
        



};