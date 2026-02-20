#include "Sudoku.hpp"
#include <csignal>

void signalHandler(int signum)
{
    endwin(); // On ferme proprement ncurses avant de quitter
    exit(signum);
}

int main(int argc, char *argv[])
{
    init_game();
    Sudoku sdk;
    // touchwin(stdscr); // Force ncurses à redessiner CHAQUE pixel au prochain refresh
    sdk.init_grid();

    // showMenu();
    sdk.showGrid();
    sdk.showHypotheticalSolutions();
    signal(SIGINT, signalHandler);
    
    while (1)
    {
        int key = getch(); // On attend l'événement clavier
        erase();
        sdk.actionsKey(key);
        sdk.showGrid();
        sdk.showHypotheticalSolutions();
        move(sdk.grid.cursorGrid.x,sdk.grid.cursorGrid.y);
        curs_set(0);
    }
    return 0;
}