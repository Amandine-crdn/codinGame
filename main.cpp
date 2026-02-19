#include "Sudoku.hpp"

int main(int argc, char *argv[])
{
    init_game();
    Sudoku sdk;
    // touchwin(stdscr); // Force ncurses à redessiner CHAQUE pixel au prochain refresh
    sdk.init_grid();

    showMenu();

    while (1)
    {
        int key = getch(); // On attend l'événement clavier
        erase();
        sdk.actionsKey(key);
        sdk.showGrid(false);
        move(sdk.grid.cursorGrid.x,sdk.grid.cursorGrid.y);
        curs_set(0);
    }
    return 0;
}