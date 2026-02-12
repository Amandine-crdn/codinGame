//Shadows of the Knight - Episode 1
//Shadows of the Knight - Episode 1

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int w; // width of the building.
    int h; // height of the building.
    cin >> w >> h; cin.ignore();
    cerr << w << " " << h << endl;
    int n; // countimum number of turns before game over.
    cin >> n; cin.ignore();
    cerr << n << endl;

    int x0;
    int y0;
    cin >> x0 >> y0; cin.ignore();
    cerr << x0 << " " << y0 << endl;
    int min_w = 0, min_h = 0;
    int max_w = w - 1;
    int max_h = h - 1;

    // game loop
    while (1) {
        string bomb_dir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bomb_dir; cin.ignore();
        cerr << bomb_dir << endl;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        // empecher de depasser le cadre
        int count;

        if (bomb_dir.find("R") != -1 )
        {
            min_w = x0 + 1;
            x0 += (max_w - x0 + 1) / 2;
        }
        else if (bomb_dir.find("L") != -1 )
        {
            max_w = x0 - 1;
            x0 -= (x0 - min_w + 1) / 2;
        }

        if (bomb_dir.find("D") != -1 )
        {
            min_h = y0 + 1;
            y0 += (max_h - y0 + 1) / 2 ;
        }
        else if (bomb_dir.find("U") != -1 )
        {
            max_h = y0 - 1;
            y0 -= (y0 - min_h + 1) /2;
        }
        cout << x0 << " " <<  y0 << endl;
    }
}


// mars lander
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int surface_n; // the number of points used to draw the surface of Mars.
    cin >> surface_n; cin.ignore();
    for (int i = 0; i < surface_n; i++) {
        int land_x; // X coordinate of a surface point. (0 to 6999)
        int land_y; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> land_x >> land_y; cin.ignore();
    }

    // game loop
    while (1) {
        int x;
        int y;
        int h_speed; // the horizontal speed (in m/s), can be negative.
        int v_speed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        cin >> x >> y >> h_speed >> v_speed >> fuel >> rotate >> power; cin.ignore();
        cerr << x << " "<< y << " "<< h_speed << " "<< v_speed << " "<< fuel << " "<< rotate << " "<< power << endl;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        if (v_speed <= -40) {
            // On met la puissance maximum pour freiner
            cout << "0 4" << endl;
        } else {
            // On se laisse tomber tranquillement
            cout << "0 0" << endl;
        }       
       
        // 2 integers: rotate power. rotate is the desired rotation angle (should be 0 for level 1), power is the desired thrust power (0 to 4).
    }
}

// horse
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    vector<int> power;
    int a, b;
    int n;
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        int pi;
        cin >> pi; cin.ignore();
        power.push_back(pi);
    }
    sort(power.begin(), power.end());
    vector<int>::iterator itb = power.begin();
    vector<int>::iterator ite = power.end();
    int min_ecart, comp;
    for (int i = 0; itb != ite - 1; itb++, i++)
    {
        if (i == 0)
        {
            if (*(itb + 1) > *itb)
            {
                min_ecart = *(itb + 1) - *itb;
            }
            else
            {
                min_ecart = *itb - *(itb + 1);
            }
        }
        else
        {
            if (*(itb + 1) >= *itb)
            {
                comp = *(itb + 1) - *itb;
            }
            else
            {
                comp = *itb - *(itb + 1);
            }
            if (comp < min_ecart)
            {
                min_ecart = comp;
                a = *itb;
                b = *itb +1;
            }
        }
    }
    cout << min_ecart << endl;


    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

}

//There is no Spoon - Episode 1
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/

int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    vector<string> tab;
    for (int i = 0; i < height; i++) {
        string line;
        getline(cin, line); // width characters, each either 0 or .
        tab.push_back(line);
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            string answer = "";
            if (tab[y][x] == '0')
            {
                answer = to_string(x) + " " + to_string(y);

                int temp_x = x + 1;
                while (temp_x != width)
                {
                    if (tab[y][temp_x] == '0')
                    {
                        answer += " " + to_string(temp_x) + " " + to_string(y);
                        break ;
                    }
                    temp_x++;     
                }
                if (temp_x == width)
                {
                    answer += " -1 -1";
                }
                
                int temp_y = y + 1;
                while (temp_y != height)
                {
                    if (tab[temp_y][x] == '0')
                    {
                        answer += " " + to_string(x) + " " + to_string(temp_y);
                        break ;
                    }
                    temp_y++;     
                }
                if (temp_y == height)
                {
                    answer += " -1 -1";
                }
                cout << answer << endl;
            }
        }
    }

  
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;


    // Three coordinates: a node, its right neighbor, its bottom neighbor
}


//parenthese
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    string expression;
    cin >> expression; cin.ignore();
    stack<char> tab;
    bool valid = true;

    for (int i = 0; i < expression.length(); i++)
    {
        if (expression[i] == '{' || expression[i] == '(' ||expression[i] == '[')
        {
            tab.push(expression[i]);
        }
        else if (expression[i] == '}' || expression[i] == ')' ||expression[i] == ']')
        {
            if (i == 0 || tab.empty())
            {
                valid = false;
                break;
            }
            if ( expression[i] == '}' && tab.top() == '{' ||
            expression[i] == ']' && tab.top() == '[' ||
            expression[i] == ')' && tab.top() == '(')
            {
                tab.pop();
            }
            else
            {
                valid = false;
            }
        
        }
    }
    if (valid == false || !tab.empty())
    {
        cout << "false" << endl;
    }
    else if (tab.empty())
    {
        cout << "true" << endl;
    }
   


    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

}

//numero de telephone
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
struct Node
{
    map<char, Node*> children;
};

Node root;
int total = 0;

int main()
{
    int n;
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string telephone;
        cin >> telephone; cin.ignore();
        cerr << telephone << endl;
        Node* current = &root; // On repart toujours de la racine

        for (int y = 0; y < telephone.length(); y++)
        {
            if (current->children.find(telephone[y]) == current->children.end())
            {
                current->children[telephone[y]] = new Node(); 
                total ++;
            }
            current = current->children[telephone[y]];
        }
    }
    cout << total << endl;

    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;


    // The number of elements (referencing a number) stored in the structure.
}

//dont panic

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int nb_floors; // number of floors
    int width; // width of the area
    int nb_rounds; // maximum number of rounds
    int exit_floor; // floor on which the exit is found
    int exit_pos; // position of the exit on its floor
    int nb_total_clones; // number of generated clones
    int nb_additional_elevators; // ignore (always zero)
    int nb_elevators; // number of elevators
    cin >> nb_floors >> width >> nb_rounds >> exit_floor >> exit_pos >> nb_total_clones >> nb_additional_elevators >> nb_elevators; cin.ignore();

    vector<int> elevatorTab(nb_floors);
    for (int i = 0; i < nb_elevators; i++) {
        int elevator_floor; // floor on which this elevator is found
        int elevator_pos; // position of the elevator on its floor
        cin >> elevator_floor >> elevator_pos; cin.ignore();

        elevatorTab[elevator_floor] = elevator_pos;
    }

    // game loop
    while (1) {
        int clone_floor; // floor of the leading clone
        int clone_pos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> clone_floor >> clone_pos >> direction; cin.ignore();

        if (clone_floor == - 1)
        {
            cout << "WAIT" << endl; // action: WAIT or BLOCK
        }
        //pour la sortie
        if (exit_floor == clone_floor)
        {   
  
            if (clone_pos > exit_pos && direction == "RIGHT")
            {
                cout << "BLOCK" << endl; // action: WAIT or BLOCK
            }
            else if (clone_pos < exit_pos && direction == "RIGHT")
            {
                cout << "WAIT" << endl; // action: WAIT or BLOCK
            }
            else if (clone_pos > exit_pos && direction == "LEFT")
            {
                cout << "WAIT" << endl; // action: WAIT or BLOCK
            }
            else if (clone_pos < exit_pos && direction == "LEFT")
            {
                cout << "BLOCK" << endl; // action: WAIT or BLOCK
            }
            else if (clone_pos == exit_pos)
            {
                cout << "WAIT" << endl; // action: WAIT or BLOCK
            }
        }
        else
        {
            // pour lascensuer
            if (clone_pos > elevatorTab[clone_floor] && direction == "RIGHT")
            {
                cout << "BLOCK" << endl; // action: WAIT or BLOCK
            }
            else if (clone_pos < elevatorTab[clone_floor] && direction == "RIGHT")
            {
                cout << "WAIT" << endl; // action: WAIT or BLOCK
            }
            else if (clone_pos > elevatorTab[clone_floor] && direction == "LEFT")
            {
                cout << "WAIT" << endl; // action: WAIT or BLOCK
            }
            else if (clone_pos < elevatorTab[clone_floor] && direction == "LEFT")
            {
                cout << "BLOCK" << endl; // action: WAIT or BLOCK
            }
            else if (clone_pos == elevatorTab[clone_floor])
            {
                cout << "WAIT" << endl; // action: WAIT or BLOCK
            } 
           
        }
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

    }
}


//Suite de Conway

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int r;
    cin >> r; cin.ignore();
    int l;
    cin >> l; cin.ignore();

    vector<int> row;
    vector<int> current_row;
    vector<int> next_row;
    row.push_back(r);

    int i = 0;
    current_row = row;
    while ( i < l - 1)
    {
        for (int y = 0; y < current_row.size();)
        {
            int number = current_row[y];
            int count = 0;
            while (y < current_row.size() && current_row[y] == number)
            {
                count++;
                y++;
            }
            next_row.push_back(count);
            next_row.push_back(number);
            
        }
        current_row = next_row;
        next_row.clear();
        i ++;
    }
    string answer;
    for (int z = 0; z < current_row.size(); z++)
    {
        if (z != 0)
        {
            answer += " ";
        }
        answer += to_string(current_row[z]);
    }
    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << answer << endl;
}


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int n;
    cin >> n; cin.ignore();
    // 3 voitures
    cerr << n << endl;
    map<int, bool> total;
    map<int, bool>::iterator itb = total.begin();
    map<int, bool>::iterator ite = total.end();

    for (int i = 0; i <= 24; i++)
    {
        total[i] = false;
    }

    for (int i = 0; i < n; i++) {
        int start;
        int end;
        cin >> start >> end; cin.ignore();

        for (int count = start; count != end; count ++)
        {
            total[count] = true;
            cerr << " yes " << count << endl;
        }
    }

    itb = total.begin();
    ite = total.end();
    int hours = 0;
    for (; itb != ite; itb++)
    {
        if (itb->second == true)
        {
            hours += 1;
        }
    }


 

    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << hours << endl;
}

//laby
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
struct Point
{
    int y;
    int x;
};

// gauche, haut, droit, bas
int direction_x[] = {-1, 0, 1, 0};
int direction_y[] = {0, -1, 0, 1};
vector<string> laby;


int main()
{
    int w;
    int h;
    cin >> w >> h; cin.ignore();
    int x;
    int y;
    cin >> x >> y; cin.ignore();
    for (int i = 0; i < h; i++) {
        string r;
        getline(cin, r);
        laby.push_back(r);
    }


    // Point parent[w][h]; // Adapte la taille selon le jeu
    bool visited[h][w];
    for (int i = 0; i < w ; i++)
    {
        for (int y = 0; y < h ; y++)
        {
            visited[y][i] = false;
        }

    }
    visited[y][x] = true;
    queue<Point> q;
    q.push({y, x}); // Ta position actuelle
    Point cible = {-1, -1};
    int exit = 0;
    int next_x = 0;
    int next_y = 0;
    vector<int> points;
    while (!q.empty())
    {
        Point current = q.front();
        for (int i = 0; i < 4; i++)
        {
            next_x = current.x + direction_x[i];
            next_y = current.y + direction_y[i];
            
            if (0 <= next_y && next_y < h && 0 <= next_x && next_x < w \
                && laby[next_y][next_x] == '.' && visited[next_y][next_x] == false)
            {
                visited[next_y][next_x] = true;
                q.push({next_y, next_x});
                //estce un bord ?
                if ( next_y == 0 || next_y == h - 1 ||next_x == 0 || next_x == w - 1)
                {
                    exit++;
                    points.push_back(next_x);
                    points.push_back(next_y);
                }
            }
        }
        q.pop();
    }

    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    // sort(points.begin(), points.end());
    
    cout << exit;
    
    
    for (int i = 0; i < points.size(); i++)
    {
        if (i == 0)
        {
            cout << points[i];
        }
        else
        {
            cout << " " << points[i];
        }
    }
    cout << endl;
}