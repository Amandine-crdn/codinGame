#ifndef SUDOKU_HPP
#define SUDOKU_HPP
using namespace std;
#include <stdio.h>
#include <iostream>
#include <vector>

class Sudoku 
{
    // private:
    public:

        struct Point
        {
            int x;
            int y;
        };

        struct Box
        {
            int answer = 0;
            vector<int> possibilities;
            Point coordonnes;
        };

        struct GridSdk
        {
            vector<Box> cell;
            int cursorX;
            int cursorY;
        };


        void init_grid(vector<int> grid);
        GridSdk grid;
        
    // private:
    void replace(int key,Sudoku &sdk);

    void give_possibilities();
        
    void get_grid(bool isInMenu, int cursorX, int cursorYbool);
   

};


#endif