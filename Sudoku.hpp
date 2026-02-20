#ifndef SUDOKU_HPP
#define SUDOKU_HPP
using namespace std;
#include <stdio.h>
#include <iostream>
#include <vector>
#include <curses.h>
#include <locale.h>
#include <algorithm>

#define KEY_ESC 27

class Sudoku 
{
    // private:?
    public:
    
    struct Point
    {
        int x;
        int y;
    };
    
    struct Box
    {
        int answer;
        vector<int> possibilities;
        Point coordonnes;
        bool canDelete;
    };
    
    struct GridSdk
    {
        vector<Box> cell;
        Point cursorGrid;
        bool modeHypothetical;
    };
    
    //Attributes
    GridSdk grid;
    
    //Methods
    void init_grid();
    void replace(int key);
    void give_possibilities();
    void actionsKey(int key);
    void showHypotheticalSolutions();
    void showGrid();
    void actionsHypothetical(int key);
    void printBox(Box bx);
    void drawHypotheticalGrid();
    void direction(int key);
};

void init_game();
void showMenu();
void showRules();
void showMenu2();
extern vector<int> levelGrid;

#endif