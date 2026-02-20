//grille 
#include "Sudoku.hpp"

void Sudoku::init_grid()
{
    this->grid.cursorGrid.x = 0;
    this->grid.cursorGrid.y = 0;
    this->grid.modeHypothetical = false;
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

void Sudoku::showGrid()
{
    refresh();
    clear();
    // Style du titre
    attron(A_BOLD  | COLOR_PAIR(3)); // Titre en vert par exemple
    mvprintw(0, 0, "    MASTER SUDOKU   \n\n"); 
    attroff(A_BOLD  | COLOR_PAIR(3));

    int x = 0;
    int y = 0;

    for (Box box: this->grid.cell)
    {
        if (x == 0 && y == 0) printw("  _________________\n");
        if (x == 0) printw(" |");
        
        if (box.coordonnes.x == this->grid.cursorGrid.x && box.coordonnes.y == this->grid.cursorGrid.y)
        {
            if (box.coordonnes.y == 8 || box.coordonnes.y == 5 || box.coordonnes.y == 2) attron(COLOR_PAIR(1) | A_BOLD | A_UNDERLINE | A_REVERSE);
            else attron(COLOR_PAIR(1) | A_BOLD | A_REVERSE);
            
            if (box.answer == 0) printw(" ");
            else printw("%d", box.answer);
            
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

void Sudoku::direction(int key)
{
    if (key == KEY_UP && this->grid.cursorGrid.y > 0) this->grid.cursorGrid.y--;
    if (key == KEY_DOWN && this->grid.cursorGrid.y < 8) this->grid.cursorGrid.y++;
    if (key == KEY_RIGHT && this->grid.cursorGrid.x < 8) this->grid.cursorGrid.x++;
    if (key == KEY_LEFT && this->grid.cursorGrid.x > 0) this->grid.cursorGrid.x--;
}

void Sudoku::actionsKey(int key)
{
    this->direction(key);
    if (key == 10) this->grid.modeHypothetical = !this->grid.modeHypothetical;
    if (key == 127 || key == KEY_BACKSPACE) this->replace(48);  
    if (key > 48 && key < 59 && this->grid.modeHypothetical == true) this->actionsHypothetical(key);
    else if (key > 48 && key < 59) this->replace(key);
}

void Sudoku::actionsHypothetical(int key)
{
    int index = this->grid.cursorGrid.y * 9 + this->grid.cursorGrid.x;
    auto & myHypothetical = this->grid.cell[index].possibilities;
    auto isFind = find(myHypothetical.begin(), myHypothetical.end(), key - '0' );
            
    //remplir hypotheses
    if (isFind == myHypothetical.end())
    {
        if (this->grid.cell[index].canDelete == true) myHypothetical.push_back(key - '0');
    }
    else myHypothetical.erase(isFind);
}

void Sudoku::drawHypotheticalGrid() {
    int startRow = 17;
    int startCol = 0;
    int cellHeight = 4; // 3 lignes de texte + 1 ligne de bordure
    int cellWidth = 9;  // 7 colonnes de texte + 2 colonnes de bordure (pour être large)

    // 1. On dessine d'abord les petites lignes partout
    attron(A_DIM | COLOR_PAIR(5));
    for (int i = 0; i <= 9; i++) {
        // Horizontales
        for (int c = 0; c <= (9 * cellWidth); c++) 
            mvaddch(startRow + (i * cellHeight), startCol + c, '-');
        // Verticales
        for (int r = 0; r <= (9 * cellHeight); r++) 
            mvaddch(startRow + r, startCol + (i * cellWidth), '|');
    }

    // 2. On repasse les GROS BLOCS par-dessus (Priorité absolue au #)
    for (int i = 0; i <= 9; i += 3) {
        // Horizontales épaisses
        for (int c = 0; c <= (9 * cellWidth); c++) 
            mvaddch(startRow + (i * cellHeight), startCol + c, '#');
        // Verticales épaisses
        for (int r = 0; r <= (9 * cellHeight); r++) 
            mvaddch(startRow + r, startCol + (i * cellWidth), '#');
    }
    attroff(A_DIM | COLOR_PAIR(5));
}

void Sudoku::printBox(Box bx)
{
    // On garde tes multiplicateurs de grille (4 pour les lignes, 9 pour les colonnes)
    int row = (bx.coordonnes.y * 4) + 17;
    int col = (bx.coordonnes.x * 9);

    vector<int>::iterator itb = bx.possibilities.begin();
    vector<int>::iterator ite = bx.possibilities.end();

    if (bx.answer != 0)
    {
        if (bx.canDelete == true && bx.coordonnes.x == this->grid.cursorGrid.x && bx.coordonnes.y == this->grid.cursorGrid.y) attron(A_BOLD | COLOR_PAIR(5) | A_REVERSE);
        else if (bx.canDelete == true) attron(A_BOLD | COLOR_PAIR(5));
        else if (bx.coordonnes.x == this->grid.cursorGrid.x && bx.coordonnes.y == this->grid.cursorGrid.y) attron(A_REVERSE | A_BOLD | COLOR_PAIR(5));
        else attron(A_BOLD | COLOR_PAIR(1));
        
        mvprintw(row + 2, col + 4, "%d", bx.answer);
        
        if (bx.canDelete == true) attroff(A_BOLD | COLOR_PAIR(5) | A_REVERSE);
        else if (bx.coordonnes.x == this->grid.cursorGrid.x && bx.coordonnes.y == this->grid.cursorGrid.y) attroff(A_REVERSE | A_BOLD | COLOR_PAIR(5));
        else attroff(A_BOLD | COLOR_PAIR(1));
    }
    else
    {
        // Affiche l'espace central avec le curseur si sélectionné
        if (bx.possibilities.empty() == true && bx.coordonnes.x == this->grid.cursorGrid.x && bx.coordonnes.y == this->grid.cursorGrid.y)
        {
            attron(A_REVERSE | A_BOLD | COLOR_PAIR(5));
        }
        
        mvprintw(row + 2, col + 4, " ");
        
        if (bx.possibilities.empty() == true && bx.coordonnes.x == this->grid.cursorGrid.x && bx.coordonnes.y == this->grid.cursorGrid.y)
        {
            attroff(A_REVERSE | A_BOLD | COLOR_PAIR(5));
        }
        
        // Affiche les hypothèses (petits chiffres) avec le style correct
        int i = 0;
        int j = 0;
        
        // SI la cellule est sélectionnée, utilise la couleur du curseur sinon la couleur dim
        if (bx.coordonnes.x == this->grid.cursorGrid.x && bx.coordonnes.y == this->grid.cursorGrid.y)
        {
            attron(A_BOLD | COLOR_PAIR(5)); // Couleur curseur pour les hypothèses aussi
        }
        else
        {
            attron(A_DIM | COLOR_PAIR(5)); // Style normal
        }
        
        for (int count = 1; count <= 9; count++)
        {
            if (std::find(itb, ite, count) != ite)
            {
                mvprintw(row + i + 1, col + 2 + j, "%d", count);
            }
            j += 2;
            if (j % 3 == 0)
            {
                i++;
                j = 0;
            }
        }
        
        // Désactive le style après les hypothèses
        if (bx.coordonnes.x == this->grid.cursorGrid.x && bx.coordonnes.y == this->grid.cursorGrid.y)
        {
            attroff(A_BOLD | COLOR_PAIR(5));
        }
        else
        {
            attroff(A_DIM | COLOR_PAIR(5));
        }
    }
}
void Sudoku::showHypotheticalSolutions()
{
    //mode on/off
    attron(A_BOLD  | COLOR_PAIR(3));
    const char *str = this->grid.modeHypothetical ? "  MODE HYPOTHESE ACTIVEE   " : "MODE HYPOTHESE DESACTIVEE";
    mvprintw(16, 29, str);
    attroff(A_BOLD  | COLOR_PAIR(3)); 
    this->drawHypotheticalGrid();
    for (Box box: this->grid.cell) this->printBox(box);
    move(this->grid.cursorGrid.y * 4 + 17 + 2, this->grid.cursorGrid.x * 9 + 4);
}   
                    
void Sudoku::replace(int key)
{
    int x = this->grid.cursorGrid.x;
    int y = this->grid.cursorGrid.y;

    int index = y * 9 + x;
    if (this->grid.cell[index].canDelete == true) this->grid.cell[index].answer = key - '0';
}



