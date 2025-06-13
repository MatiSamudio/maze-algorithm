#include <iostream>  // entrada y salida en consola.
#include <vector>      // uso de arrays dinamicos (matrices).
#include <cstdlib>      //para generacion
#include <ctime>        //aleatoia 
#include <random>       //del laberinto.
#include <algorithm>    // uso del shuffle.
#include <thread>       // pausas temporales
#include <chrono>       // (sleep).
#include <queue>        //para la fila queue.

#include <windows.h>
#define CLEAR "CLS"

using namespace std;

struct Cell {
    bool visited = false; //indircar si fuie recorrida
    bool walls[4] = {true, true, true, true}; //arriba abajo izquierda derecha
};

//direcciones : arriba abajo izquierda derecha
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};



int rows, cols;
int playerX = 0;
int playerY = 0;
vector<vector<Cell>> maze; //una matriz de Cell(s)
vector<vector<bool>> solutionPath; // marcar camino correc
vector<vector<bool>> exploredPath; //marcar celdas exploradas

// valida si una celda (x, y) esta dentrro del laberinto 
bool isValid(int x, int y) {
    return x >= 0 && x < cols && y >= 0 && y < rows;
}

// quita las paredes entre dos celdas adyacentes usando su dirreccion
void removeWall(Cell &a, Cell &b, int direction) {
    a.walls[direction] = false;
    b.walls[(direction + 2) % 4] = false; 
}

void printMaze();

// genera el laberinto usando DFS backtracking(Depth-First Search)
void generateMaze(int x, int y, mt19937 &g) {
    maze[y][x].visited = true; //marca celda como visitada 

    system(CLEAR);
    printMaze();
    Sleep(200); 

    vector<int> directions = {0, 1, 2, 3};              //mezcla aleatoriamente 
    shuffle(directions.begin(), directions.end(), g);   //las direcciones.
                                                        //se mueve a vecinos 
    for (int dir : directions) {                        //no visitados quitando 
        int nx = x + dx[dir];                           //paredes.
        int ny = y + dy[dir];                           //se llama recursivamente 
                                                        //sobre nuevas celdas.
        if (isValid(nx, ny) && !maze[ny][nx].visited) {
            removeWall(maze[y][x], maze[ny][nx], dir); 
            generateMaze(nx, ny, g);
        }
    }
}


void printMaze() {
    //linea superior
    for (int x = 0; x < cols; x++) {
        cout << "+---";
    }
    cout << "+\n";

    for (int y = 0; y < rows; y++) {
        //contenido de celda
        for(int x = 0; x < cols; x++) {
            cout << (maze[y][x].walls[3] ? "|" : " ");

            if (x == playerX && y == playerY)
                cout << " $ ";
            else if (x == 0 && y == 0)
                cout << " E ";
            else if (x == cols - 1 && y == rows - 1)
                cout << " S ";
            else if (solutionPath[y][x])  // camino recorrido originalmete que queda para la solucion
                cout << " . ";
            else if (exploredPath[y][x])    // camino sin explorado que no lleva a la salida
                cout << " x ";
            else
                cout << "   ";   
        }
        cout << "|\n";


        //linea inferior de cada celda
        for (int x = 0; x < cols; x++) {
            cout << "+";
            cout << (maze[y][x].walls[2] ? "---" : "   ");
        }
        cout << "+\n";
    }
}

// algoritmo DFS backtracking para resolver el laberinto
bool solveMaze(int x, int y) {
    if (!isValid(x, y) || exploredPath[y][x]) 
        return false;

    exploredPath[y][x] = true;
    solutionPath[y][x] = true;

    //mostrarn paso a paso
    system(CLEAR);
    printMaze();
    Sleep(300); //la pausa

    if (x == cols - 1 && y == rows - 1)  //si llega a la salida
        return true;

    for (int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (!maze[y][x].walls[dir] && solveMaze(nx, ny)) {
            return true;
        }
    }

    //backtracking
    solutionPath[y][x] = false;

    //mostrar backtraking
    system(CLEAR);
    printMaze();
    Sleep(300);

    return false;
}


bool solveMazeBFS() {
    queue<pair<int, int>> q;
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, 1}));

    q.push({0, 0});
    exploredPath[0][0] = true;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        system(CLEAR);
        printMaze();
        Sleep(300);
            //si llega a la salida
        if (x == cols - 1 && y == rows - 1) {
            //reconstruir camino
            while (!(x == 0 && y == 0)) {
                solutionPath[y][x] = true;
                tie(x, y) = parent[y][x];
            }
            solutionPath[0][0] = true;

            system(CLEAR);
            printMaze();
            return true;
        }
            //explora en todas las direcciones de los lugares no visitados y por donde no hay paredes los agrega al queue 
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (isValid(nx, ny) && !maze[y][x].walls[dir] && !exploredPath[ny][nx]) {
                exploredPath[ny][nx] = true;
                parent[ny][nx] = {x, y};
                q.push({nx,ny});
            }
        }
    }

    return false;
}


void playGame() {
    playerX = 0;
    playerY = 0;

    while (true ) {
        system(CLEAR);
        printMaze();

        if (playerX == cols - 1 && playerY == rows -1) {
            cout << "\nLlegaste a la salida crack\n";
            break;
        }

        cout << "\nUsar WASD para moverte (↑ ← ↓ →): ";
        char move;
        cin >> move;

        if (move == 'q' || move == 'Q') {
            cout << "Te rendiste crack :( ";
            break;
        }

        int dir = -1;

        if (move == 'w' || move == 'W') dir = 0;
        else if (move == 'd'|| move == 'D') dir = 1;
        else if (move == 's'|| move == 'S') dir = 2;
        else if (move == 'a'|| move == 'A') dir = 3;

        if (dir != -1) {
            int nx = playerX + dx[dir];
            int ny = playerY + dy[dir];

            if (isValid(nx, ny) && !maze[playerY][playerX].walls[dir]) {
                playerX = nx;
                playerY = ny;
            }
        }
    }
}


int main() {
    cout << "Generador de laberito 2D" << endl;
    cout << "INgrese numero de filas para laberinto: ";
    cin >> rows;
    cout << "Ingrese numero de columnas para laberinto: ";
    cin >> cols;


    maze = vector<vector<Cell>>(rows, vector<Cell>(cols));
    solutionPath = vector<vector<bool>>(rows, vector<bool>(cols, false));
    exploredPath = vector<vector<bool>>(rows, vector<bool>(cols, false));
    

    mt19937 g(static_cast<unsigned int>(time(nullptr)));
    generateMaze(0, 0, g); //comeinza en 0,0


    cout << "Laberinto generado elija metodo para resolver " << endl;
    cout << "1. DFS (Backtracking)\n";
    cout << "2. BFS\n";
    cout << "3. Jugar manual\n";
    cout << "Opcion: ";

    int option;
    cin >> option;
    

    if (option == 1) {
        solveMaze(0, 0);
        cout << "Laberinto resuelto" << endl;
    } else if (option == 2){
        solveMazeBFS();
        cout << "Laberinto resuelto" << endl;
    } else {
        playGame();
    }

    return 0;
}

