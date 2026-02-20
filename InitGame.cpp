#include "Sudoku.hpp"

vector<int> levelGrid = {
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

void showMenu()
{
    attron(A_BOLD | COLOR_PAIR(1));
    printw("Bienvenue au CLI Sudoku\nAppuyez sur ");
    attroff(A_BOLD | COLOR_PAIR(1));
    attron(A_BOLD | COLOR_PAIR(2));
    printw("espace");
    attroff(A_BOLD | COLOR_PAIR(2));
    attron(A_BOLD | COLOR_PAIR(1));
    printw(" pour commencer\n");
}

void showRules()
{
    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(1, 30, "REGLES DU JEU\n");
    mvprintw(4, 30, "Touche 'S' pour voir/cacher les hypotheses\n");
    mvprintw(5, 30, "Touche 'Entrer' pour acceder au  mode hypothese\n");
    mvprintw(7, 30, "Touche 'Backspace' pour supprimer\n");
    attroff(A_BOLD | COLOR_PAIR(1));
}

void showMenu2()
{
    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(1, 30, "MENU\n");
    mvprintw(4, 30, "=== RESOUDRE ===\n");
    mvprintw(5, 30, "Entrez un chiffre (1-9): \n");
    mvprintw(6, 30, "=== AUTRES ===\n");
    mvprintw(7, 30, "A.Voir les hypotheses\n");
    mvprintw(8, 30, "B.Modifier les hypotheses\n");
    mvprintw(9, 30, "C.Reponses\n");
    mvprintw(11, 30, "Q pour quitter\n");
    move(5, 57);
    attroff(A_BOLD | COLOR_PAIR(1));
}

void init_game()
{
    setlocale(LC_ALL, ""); // Pour supporter les caractères spéciaux comme les lignes de ta grille
    initscr();             // Initialise la mémoire de l'écran
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);   // Curseur normal
    init_pair(2, COLOR_CYAN, COLOR_BLACK);   // Bon (Chiffre vert)
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Mode saisie (Rose)
    init_pair(4, COLOR_RED, COLOR_BLACK);     // Erreur (Chiffre rouge)
    init_pair(5, COLOR_WHITE, COLOR_BLACK);   // Curseur normal
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);   // Curseur normal
 
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
