//grille 
#include "Sudoku.hpp"
// #include "raylib.h"
#include <curses.h>
#include <locale.h>
#define KEY_ESC 27

void Sudoku::get_grid(bool isInMenu, int cursorX = 0, int cursorY = 0)
{
    refresh();
    clear();
    move(0,0);
    // Style du titre
    attron(A_BOLD |A_UNDERLINE | COLOR_PAIR(2)); // Titre en vert par exemple
    printw("    MASTER SUDOKU   \n\n"); 
    attroff(A_BOLD | A_UNDERLINE | COLOR_PAIR(2));



    int x = 0;
    int y = 0;

    for (Box box: this->grid.cell)
    {
        if (x == 0 && y == 0) printw(" _________________\n");
        if (x == 0) printw("|");
        
        if (box.coordonnes.x == cursorX && box.coordonnes.y == cursorY)
        {
            if (isInMenu) attron(COLOR_PAIR(3) | A_BOLD);
            else attron(COLOR_PAIR(1) | A_REVERSE);

            if (box.answer == 0) printw(" ");
            else printw("%d", box.answer);
            
            if (isInMenu) attroff(COLOR_PAIR(3) | A_BOLD);
            else attroff(COLOR_PAIR(1) | A_REVERSE);
        }
        else
        {
            if (box.answer == 0) printw(" ");
            else printw("%d", box.answer);
        }
        
        x++;
        printw((x % 3 == 0) ? "|" : " ");
        if (x == 9)
        {
            printw("\n");
            x = 0;
            y++;
            if (y % 3 == 0) printw(" _________________\n");
        }
    }
    refresh();
}



vector<int> easy_grid = {
    5, 3, 0,  0, 7, 0,  0, 0, 0,  // Ligne 1
    6, 0, 0,  1, 9, 5,  0, 0, 0,  // Ligne 2
    0, 9, 8,  0, 0, 0,  0, 6, 0,  // Ligne 3
    
    8, 0, 0,  0, 6, 0,  0, 0, 3,  // Ligne 4
    4, 0, 0,  8, 0, 3,  0, 0, 1,  // Ligne 5
    7, 0, 0,  0, 2, 0,  0, 0, 6,  // Ligne 6
    
    0, 6, 0,  0, 0, 0,  2, 8, 0,  // Ligne 7
    0, 0, 0,  4, 1, 9,  0, 0, 5,  // Ligne 8
    0, 0, 0,  0, 8, 0,  0, 7, 9   // Ligne 9
};


void Sudoku::init_grid(vector<int> grid)
{
    Box box;
    Point localization;
    localization.x = 0;
    localization.y = 0;

    for (int c: grid)
    {
        box.answer = c;
        box.coordonnes = localization;
        this->grid.cell.push_back(box);
        localization.x++;
        if (localization.x == 9)
        {
            localization.x = 0;
            localization.y++;
        }
    } 
}

void init_game()
{
    setlocale(LC_ALL, ""); // Pour supporter les caractères spéciaux comme les lignes de ta grille
    initscr();             // Initialise la mémoire de l'écran
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);   // Curseur normal
    init_pair(2, COLOR_GREEN, COLOR_BLACK);   // Bon (Chiffre vert)
    init_pair(3, COLOR_WHITE, COLOR_MAGENTA); // Mode saisie (Rose)
    init_pair(4, COLOR_RED, COLOR_BLACK);     // Erreur (Chiffre rouge)
 
    // --- LE SECRET EST ICI ---
    wbkgd(stdscr, COLOR_PAIR(1)); // Applique le fond noir à toute la fenêtre
    attron(COLOR_PAIR(1));        // Active la couleur blanche sur noir par défaut
    erase();                      // Remplit virtuellement tout l'écran avec la couleur de fond
    refresh();                    // Envoie l'instruction au terminal immédiatement
    // -------------------------
    
    cbreak();              // Reçoit les touches immédiatement sans attendre 'Entrée'
    noecho();              // Empêche l'affichage des touches pressées sur l'écran
    keypad(stdscr, TRUE);  // MAGIE : Permet d'utiliser KEY_UP, KEY_DOWN, etc.
    curs_set(0);           // Cache le curseur clignotant du terminal (optionnel)
}

void replace(int key,Sudoku &sdk)
{
    int x = sdk.grid.cursorX;
    int y = sdk.grid.cursorY;

    int index = y * 9 + x;

    sdk.grid.cell[index].answer = key - '0'; // Convertit le caractère '5' en chiffre 5
    
}

void choice(Sudoku &sdk)
{
    curs_set(1);
    int cursorX = 5;
    int cursorY = 30;

    attron(A_BOLD | COLOR_PAIR(1));
    move(1, 30); printw("MENU\n");
    move(4, 30); printw("=== RESOUDRE ===\n");
    move(5, 30); printw("A. Entrez un chiffre (1-9): \n");
    move(6, 30); printw("=== AUTRES ===\n");
    move(7, 30); printw("A.Voir les hypotheses\n");
    move(8, 30); printw("B.Modifier les hypotheses\n");
    move(9, 30); printw("C.Reponses\n");
    move(11, 30); printw("q pour quitter\n");
    move(5, 57);
    attroff(A_BOLD | COLOR_PAIR(1));
    int number = -1;
    while (true)
    {
        refresh();
        int key = getch(); // On attend la saisie
        
        if (key == KEY_UP && cursorX > 5)
        {
            cursorX--;
            if (cursorX == 6) cursorX--;
        }
        if (key == KEY_DOWN && cursorX < 9)
        {
            cursorX++;
            if (cursorX == 6) cursorX++;
        }
        cursorY = cursorX == 5 ? 57 : 30;
        if ('0' < key  && key < '9' && cursorX == 5)
        {
            printw("%c", char(key));
            number = key;
        }
        if (key == 10 && number != -1)
        {
            replace(number, sdk);
            return ;
        }
        move(cursorX, cursorY);

        if (key =='q')
        {
            return; // quitte la deuxime fois
        }
    }
    curs_set(0);
}

int main(int argc, char *argv[])
{

    init_game();
    Sudoku sdk;
    // touchwin(stdscr); // Force ncurses à redessiner CHAQUE pixel au prochain refresh
    sdk.init_grid(easy_grid);
    sdk.grid.cursorX = 0;
    sdk.grid.cursorY = 0;
    // sdk.get_grid(false);
    attron(A_BOLD | COLOR_PAIR(1));
    printw("Bienvenue au CLI Sudoku\nAppuyez sur ");
    attroff(A_BOLD | COLOR_PAIR(1));

    attron(A_BOLD | COLOR_PAIR(2));
    printw("espace");
    attroff(A_BOLD | COLOR_PAIR(2));
    
    attron(A_BOLD | COLOR_PAIR(1));
    printw(" pour commencer\n");

    while (1)
    {
        int key = getch(); // On attend l'événement clavier
        erase();
        if (key == KEY_UP && sdk.grid.cursorY > 0) sdk.grid.cursorY--;
        if (key == KEY_DOWN && sdk.grid.cursorY < 8) sdk.grid.cursorY++;
        if (key == KEY_RIGHT && sdk.grid.cursorX < 8) sdk.grid.cursorX++;
        if (key == KEY_LEFT && sdk.grid.cursorX > 0) sdk.grid.cursorX--;
        if (key == 10)
        {
            // clear();
            sdk.get_grid(true, sdk.grid.cursorX, sdk.grid.cursorY);
            choice(sdk);
            curs_set(0);           // Cache le curseur clignotant du terminal (optionnel)
            // move(sdk.grid.cursorX, sdk.grid.cursorY);
            // clear();
        }
        sdk.get_grid(false, sdk.grid.cursorX, sdk.grid.cursorY);

    }
    return 0;
}

// chaque case: chiffre definitif