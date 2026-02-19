//grille 
#include "Sudoku.hpp"

void Sudoku::init_grid()
{
    this->grid.cursorGrid.x = 0;
    this->grid.cursorGrid.y = 0;

    Box box;
    Point localization;
    localization.x = 0;
    localization.y = 0;

    for (int c: levelGrid)
    {
        box.answer = c;
        box.canDelete = c == 0 ? true : false; //chiffre donner au depart vide
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

// void Menu2(Sudoku &sdk)
// {
//     sdk.showGrid(true, sdk.grid.cursorGrid.x, sdk.grid.cursorGrid.y);
//     curs_set(1);
//     int cursorGrid.x = 5;
//     int cursorGrid.y = 30;

//     showMenu2();
//     int number = -1;
//     while (true)
//     {
//         refresh();
//         int key = getch(); // On attend la saisie
        
//         if (key == KEY_UP && cursorGrid.x > 5)
//         {
//             cursorGrid.x--;
//             if (cursorGrid.x == 6) cursorGrid.x--;
//         }
//         if (key == KEY_DOWN && cursorGrid.x < 9)
//         {
//             cursorGrid.x++;
//             if (cursorGrid.x == 6) cursorGrid.x++;
//         }
//         cursorGrid.y = cursorGrid.x == 5 ? 57 : 30;
//         if ('0' < key  && key < '9' && cursorGrid.x == 5)
//         {
//             printw("%c", char(key));
//             number = key;
//         }
//         if (key == 10 && number != -1)
//         {
//             sdk.replace(number);
//             return ;
//         }
//         move(cursorGrid.x, cursorGrid.y);

//         if (key =='q')
//         {
//             return; // quitte la deuxime fois
//         }
//     }
//     curs_set(0);
// }

void Sudoku::showGrid(bool isInMenu)
{
    refresh();
    clear();
    // Style du titre
    attron(A_BOLD |A_UNDERLINE | COLOR_PAIR(2)); // Titre en vert par exemple
    mvprintw(0, 0, "    MASTER SUDOKU   \n\n"); 
    attroff(A_BOLD | A_UNDERLINE | COLOR_PAIR(2));

    int x = 0;
    int y = 0;

    for (Box box: this->grid.cell)
    {
        if (x == 0 && y == 0) printw("  _________________\n");
        if (x == 0) printw(" |");
        
        if (box.coordonnes.x == this->grid.cursorGrid.x && box.coordonnes.y == this->grid.cursorGrid.y)
        {
            // if (isInMenu) attron(COLOR_PAIR(3) | A_BOLD);
            if (box.coordonnes.y == 8 || box.coordonnes.y == 5 || box.coordonnes.y == 2) attron(COLOR_PAIR(1) | A_BOLD | A_UNDERLINE | A_REVERSE);
            else attron(COLOR_PAIR(1) | A_BOLD | A_REVERSE);
            
            if (box.answer == 0) printw(" ");
            else printw("%d", box.answer);
            
            // if (isInMenu) attroff(COLOR_PAIR(3) | A_BOLD);
            if (box.coordonnes.y == 8 || box.coordonnes.y == 5 || box.coordonnes.y == 2) attroff(COLOR_PAIR(1) | A_BOLD | A_UNDERLINE | A_REVERSE);
            else attroff(COLOR_PAIR(1) | A_BOLD | A_REVERSE);

        }
        else if (y == 8 || y == 5 || y == 2)
        {
            attron(COLOR_PAIR(1) | A_UNDERLINE);
            if (box.answer == 0) printw(" ");
            else printw("%d", box.answer);
            attroff(COLOR_PAIR(1) | A_UNDERLINE);
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
        }
    }
    refresh();
}

void Sudoku::actionsHypothetical(int key)
{
    int x = this->grid.cursorGrid.x;
    int y = this->grid.cursorGrid.y;
    if (key == KEY_UP ) this->grid.cursorGrid.y--;
    if (key == KEY_DOWN ) this->grid.cursorGrid.y++;
    if (key == KEY_RIGHT ) this->grid.cursorGrid.x++;
    if (key == KEY_LEFT ) this->grid.cursorGrid.x--;
    // if (key > 48 && key < 58) this->replace(key);
    // if (key == 127 || key == KEY_BACKSPACE) this->replace(48);  
    // if (key == 10) this->showHypotheticalSolutions();
}

void Sudoku::drawHypotheticalGrid() {
    int startRow = 17;
    int startCol = 0;
    int cellHeight = 4; // 3 lignes de texte + 1 ligne de bordure
    int cellWidth = 9;  // 7 colonnes de texte + 2 colonnes de bordure (pour être large)

    // 1. On dessine d'abord les petites lignes partout
    attron(A_DIM);
    for (int i = 0; i <= 9; i++) {
        // Horizontales
        for (int c = 0; c <= (9 * cellWidth); c++) 
            mvaddch(startRow + (i * cellHeight), startCol + c, '-');
        // Verticales
        for (int r = 0; r <= (9 * cellHeight); r++) 
            mvaddch(startRow + r, startCol + (i * cellWidth), '|');
    }
    attroff(A_DIM);

    // 2. On repasse les GROS BLOCS par-dessus (Priorité absolue au #)
    attron(A_BOLD | COLOR_PAIR(2));
    for (int i = 0; i <= 9; i += 3) {
        // Horizontales épaisses
        for (int c = 0; c <= (9 * cellWidth); c++) 
            mvaddch(startRow + (i * cellHeight), startCol + c, '#');
        // Verticales épaisses
        for (int r = 0; r <= (9 * cellHeight); r++) 
            mvaddch(startRow + r, startCol + (i * cellWidth), '#');
    }
    attroff(A_BOLD | COLOR_PAIR(2));
}

void Sudoku::printBox(Box bx)
{
    // On garde tes multiplicateurs de grille (4 pour les lignes, 9 pour les colonnes)
    int row = (bx.coordonnes.y * 4) + 17;
    int col = (bx.coordonnes.x * 9);

    bx.possibilities.push_back(5);
    bx.possibilities.push_back(7);
    vector<int>::iterator itb = bx.possibilities.begin();
    vector<int>::iterator ite = bx.possibilities.end();

    if (bx.answer != 0) {
        attron(A_BOLD | COLOR_PAIR(2));
        // CHIFRE : row+2 est le milieu vertical, col+4 est le milieu horizontal exact
        mvprintw(row + 2, col + 4, "%d", bx.answer);
        attroff(A_BOLD | COLOR_PAIR(2));
    } else {
        attron(COLOR_PAIR(1));
        int i = 0;
        int j = 0;
        for (int count = 0; count < 9; count++) {

            if (std::find(itb, ite, count) != ite)
            {
                mvprintw(row + (i % 3) + 1, col + j + 2, "%d", count);
            }
            else
            {
                mvprintw(row + (i % 3) + 1, col + j + 2, " ");
            }
            i++;
            if (i % 3 == 0) {
                j += 2; // On décale de 2 colonnes vers la droite
                i = 0;
            }
        }
        attroff(COLOR_PAIR(1));
    }
}

void Sudoku::showHypotheticalSolutions()
{
    int tempX = this->grid.cursorGrid.x;
    int tempY = this->grid.cursorGrid.y;
    int x = 17;
    int y = 0;
    // this->grid.cursorGrid.x = x; // pour le curseru plus tard
    // this->grid.cursorGrid.y = y;

    curs_set(1);
    this->showGrid(false);
    
    // Style du titre
    attron(A_BOLD |A_UNDERLINE | COLOR_PAIR(2)); // Titre en vert par exemple
    mvprintw(15, 10, "    HYPOTHETICAL SOLUTIONS   \n\n"); 
    attroff(A_BOLD | A_UNDERLINE | COLOR_PAIR(2));

    // move(this->grid.cursorGrid.x * 4, this->grid.cursorGrid.y * 4);
    
    for (Box box: this->grid.cell) this->printBox(box);
    this->drawHypotheticalGrid();
    
    while (true)
    {
        refresh();
        int key = getch(); 
        if (key =='q') break;
        this->actionsHypothetical(key);
        move(this->grid.cursorGrid.y * 4 + 17 + 2, this->grid.cursorGrid.x * 9 + 4);
    }
    curs_set(0);
    this->grid.cursorGrid.x = tempX;
    this->grid.cursorGrid.y = tempY;
}   
                    
void Sudoku::replace(int key)
{
    int x = this->grid.cursorGrid.x;
    int y = this->grid.cursorGrid.y;

    int index = y * 9 + x;
    if (this->grid.cell[index].canDelete == true) this->grid.cell[index].answer = key - '0'; // Convertit le char en int
}


void Sudoku::actionsKey(int key)
{
    if (key == KEY_UP && this->grid.cursorGrid.y > 0) this->grid.cursorGrid.y--;
    if (key == KEY_DOWN && this->grid.cursorGrid.y < 8) this->grid.cursorGrid.y++;
    if (key == KEY_RIGHT && this->grid.cursorGrid.x < 8) this->grid.cursorGrid.x++;
    if (key == KEY_LEFT && this->grid.cursorGrid.x > 0) this->grid.cursorGrid.x--;
    if (key > 48 && key < 58) this->replace(key);
    if (key == 127 || key == KEY_BACKSPACE) this->replace(48);  
    if (key == 10) this->showHypotheticalSolutions();
}


