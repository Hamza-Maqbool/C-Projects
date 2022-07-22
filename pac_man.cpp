#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <cmath>
using namespace std;

void printMaze();
void loadMaze();
void movePacmanLeft();
void movePacmanRight();
void movePacmanUp();
void movePacmanDown();
void printScore();
void calculateScore();
int ghostDirection();
bool ghostMovement();
bool ghostMovement2();
bool ghostMovement3();
bool ghostmovement4();
int smallestDistance();
void gotoxy(int x, int y);

char maze[24][71] =
    {{"#####################################################################"},
     {"||.. .....................................................  ......  ||"},
     {"||.. %%%%%%%%%%%%%%%%        ...     %%%%%%%%%%%%%%  |%|..   %%%%   ||"},
     {"||..        |%|   |%|     |%|...     |%|        |%|  |%|..    |%|   ||"},
     {"||..        |%|   |%|     |%|...     |%|        |%|  |%|..    |%|   ||"},
     {"||..        %%%%%%%%  . . |%|...     %%%%%%%%%%%%%%     ..   %%%%.  ||"},
     {"||..        |%|       . . |%|...    ............... |%| ..       .  ||"},
     {"||..        %%%%%%%%%%. . |%|...    %%%%%%%%%%%%    |%| ..   %%%%.  ||"},
     {"||..               |%|.             |%|......       |%| ..    |%|.  ||"},
     {"||..     ......... |%|.             |%|......|%|        ..    |%|.  ||"},
     {"||..|%|  |%|%%%|%|.|%|. |%|            ......|%|        ..|%| |%|.  ||"},
     {"||..|%|  |%|   |%|..    %%%%%%%%%%%%%  ......|%|         .|%|.      ||"},
     {"||..|%|  |%|   |%|..           ...|%|     %%%%%%        . |%|.      ||"},
     {"||..|%|            .           ...|%|               |%| ..|%|.      ||"},
     {"||..|%|  %%%%%%%%%%%%%%        ...|%|%%%%%%%%%%     |%| ..|%|%%%%%  ||"},
     {"||...............................................   |%| ..........  ||"},
     {"||   ............................................          .......  ||"},
     {"||..|%|  |%|   |%|..    %%%%%%%%%%%%%  ......|%|    |%| ..|%|.      ||"},
     {"||..|%|  |%|   |%|..           ...|%|     %%%%%%    |%| ..|%|.      ||"},
     {"||..|%|            .           ...|%|               |%| ..|%|.      ||"},
     {"||..|%|  %%%%%%%%%%%%%%        ...|%|%%%%%%%%%%     |%| ..|%|%%%%%  ||"},
     {"||...............................................   |%| ..........  ||"},
     {"||  .............................................          .......  ||"},
     {"#####################################################################"}};
int scor = 0;

int pacmanX = 9;  // X Coordinate of Pacman
int pacmanY = 40; // Y Coordinate of Pacman
float dis[4] = {10000, 10000, 10000, 10000};
int ghostX = 19; // X Coordinate of Ghost
int ghostY = 25; // Y Coordinate of Ghost
int ghost2X = 1;
int ghost2Y = 10;
int ghost3X = 15;
int ghost3Y = 20;
int ghost4X = 16;
int ghost4Y = 50;
char previousItem = ' ';
char previousItem1 = ' ';
char previousItem2 = ' ';
char previousItem3 = ' ';
int goust1, goust2, goust3, goust4;
main() // Main Function
{
    bool gameRunning = true;
    system("cls");
    //loadMaze();
    printMaze();

    gotoxy(pacmanY, pacmanX);
    cout << "P";
    gotoxy(ghostY, ghostX);
    cout << "G";
    gotoxy(ghost2Y, ghost2X);
    cout << "G";
    gotoxy(ghost3Y, ghost3X);
    cout << "G";
    gotoxy(ghost4Y, ghost4X);
    cout << "G";

    while (gameRunning)
    {

        Sleep(200);
        printScore();
        goust1 = ghostMovement();
        goust2 = ghostMovement2();
        goust3 = ghostMovement3();
        goust4 = ghostmovement4();
        if (goust1 == 0 || goust2 == 0 || goust3 == 0 || goust4 == 0)
        {
            break;
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePacmanLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePacmanRight();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movePacmanUp();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movePacmanDown();
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gameRunning = false; // Stop the game
        }
    }
}
void printMaze()
{
    for (int row = 0; row < 24; row = row + 1)
    {
        for (int col = 0; col < 71; col = col + 1)
        {
            cout << maze[row][col];
        }
        cout << endl;
    }
}
void movePacmanUp()
{
    if (maze[pacmanX - 1][pacmanY] == ' ' || maze[pacmanX - 1][pacmanY] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanX = pacmanX - 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}
void movePacmanDown()
{
    if (maze[pacmanX + 1][pacmanY] == ' ' || maze[pacmanX + 1][pacmanY] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanX = pacmanX + 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}
void movePacmanRight()
{
    if (maze[pacmanX][pacmanY + 1] == ' ' || maze[pacmanX][pacmanY + 1] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanY = pacmanY + 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}
void movePacmanLeft()
{
    if (maze[pacmanX][pacmanY - 1] == ' ' || maze[pacmanX][pacmanY - 1] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanY = pacmanY - 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}
int ghostDirection()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}
void calculateScore()
{
    scor = scor + 1;
}
bool ghostMovement()
{
    int value1 = ghostDirection();
    if (value1 == 1)
    {
        if (maze[ghostX][ghostY - 1] == '.' || maze[ghostX][ghostY - 1] == ' ' || maze[ghostX][ghostY - 1] == 'P')
        {
            maze[ghostX][ghostY] = previousItem1;
            gotoxy(ghostY, ghostX);
            cout << previousItem1;
            ghostY = ghostY - 1;
            previousItem1 = maze[ghostX][ghostY];
            if (previousItem1 == 'P')
            {
                return 0;
            }
            maze[ghostX][ghostY] = 'G';
            gotoxy(ghostY, ghostX);
            cout << 'G';
        }
    }
    if (value1 == 2)
    {
        if (maze[ghostX][ghostY + 1] == '.' || maze[ghostX][ghostY + 1] == ' ' || maze[ghostX][ghostY + 1] == 'P')
        {
            maze[ghostX][ghostY] = previousItem1;
            gotoxy(ghostY, ghostX);
            cout << previousItem1;
            ghostY = ghostY + 1;
            previousItem1 = maze[ghostX][ghostY];
            if (previousItem1 == 'P')
            {
                return 0;
            }
            maze[ghostX][ghostY] = 'G';
            gotoxy(ghostY, ghostX);
            cout << 'G';
        }
    }
    if (value1 == 3)
    {
        if (maze[ghostX + 1][ghostY] == '.' || maze[ghostX + 1][ghostY] == ' ' || maze[ghostX + 1][ghostY] == 'P')
        {
            maze[ghostX][ghostY] = previousItem1;
            gotoxy(ghostY, ghostX);
            cout << previousItem1;
            ghostX = ghostX + 1;
            previousItem1 = maze[ghostX][ghostY];
            if (previousItem1 == 'P')
            {
                return 0;
            }
            maze[ghostX][ghostY] = 'G';
            gotoxy(ghostY, ghostX);
            cout << 'G';
        }
    }
    if (value1 == 4)
    {
        if (maze[ghostX - 1][ghostY] == '.' || maze[ghostX - 1][ghostY] == ' ' || maze[ghostX - 1][ghostY] == 'P')
        {
            maze[ghostX][ghostY] = previousItem1;
            gotoxy(ghostY, ghostX);
            cout << previousItem1;
            ghostX = ghostX - 1;
            previousItem1 = maze[ghostX][ghostY];
            if (previousItem1 == 'P')
            {
                return 0;
            }
            maze[ghostX][ghostY] = 'G';
            gotoxy(ghostY, ghostX);
            cout << 'G';
        }
    }
    return 1;
}
void gotoxy(int x, int y) // Function Definition
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void printScore()
{
    gotoxy(80, 5);
    cout << "Score: " << scor;
}
bool ghostMovement2()
{
    int value = ghostDirection();
    if (value == 1)
    {
        if (maze[ghost2X][ghost2Y - 1] == '.' || maze[ghost2X][ghost2Y - 1] == ' ' || maze[ghost2X][ghost2Y - 1] == 'P')
        {
            maze[ghostX][ghostY] = previousItem2;
            gotoxy(ghost2Y, ghost2X);
            cout << previousItem2;
            ghost2Y = ghost2Y - 1;
            previousItem2 = maze[ghost2X][ghost2Y];
            if (previousItem2 == 'P')
            {
                return 0;
            }
            maze[ghost2X][ghost2Y] = 'G';
            gotoxy(ghost2Y, ghost2X);
            cout << 'G';
        }
    }
    else if (value == 2)
    {
        if (maze[ghost2X][ghost2Y + 1] == '.' || maze[ghost2X][ghost2Y + 1] == ' ' || maze[ghost2X][ghost2Y + 1] == 'P')
        {
            maze[ghost2X][ghost2Y] = previousItem2;
            gotoxy(ghost2Y, ghost2X);
            cout << previousItem2;
            ghost2Y = ghost2Y + 1;
            previousItem2 = maze[ghost2X][ghost2Y];
            if (previousItem2 == 'P')
            {
                return 0;
            }
            maze[ghost2X][ghost2Y] = 'G';
            gotoxy(ghost2Y, ghost2X);
            cout << 'G';
        }
    }
    return 1;
}
bool ghostMovement3()
{
    int value3 = ghostDirection();
    if (value3 == 1)
    {
        if (maze[ghost3X][ghost3Y - 1] == '.' || maze[ghost3X][ghost3Y - 1] == ' ' || maze[ghost3X][ghost3Y - 1] == 'P')
        {
            maze[ghost3X][ghost3Y] = previousItem3;
            gotoxy(ghost3Y, ghost3X);
            cout << previousItem3;
            ghost3Y = ghost3Y - 1;
            previousItem3 = maze[ghost3X][ghost3Y];
            if (previousItem3 == 'P')
            {
                return 0;
            }
            maze[ghost3X][ghost3Y] = 'G';
            gotoxy(ghost3Y, ghost3X);
            cout << 'G';
        }
    }
    else if (value3 == 2)
    {
        if (maze[ghost3X][ghost3Y + 1] == '.' || maze[ghost3X][ghost3Y + 1] == ' ' || maze[ghost3X][ghost3Y + 1] == 'P')
        {
            maze[ghost3X][ghost3Y] = previousItem3;
            gotoxy(ghost3Y, ghost3X);
            cout << previousItem3;
            ghost3Y = ghost3Y + 1;
            previousItem3 = maze[ghost3X][ghost3Y];
            if (previousItem3 == 'P')
            {
                return 0;
            }
            maze[ghost3X][ghost3Y] = 'G';
            gotoxy(ghost3Y, ghost3X);
            cout << 'G';
        }
    }
    return 1;
}

void loadMaze()
{
    fstream loadmaze;
    loadmaze.open("maze.txt", ios::in);
    string line;
    int row = 0;
    while (!loadmaze.eof())
    {
        getline(loadmaze, line);
        for (int col = 0; col < 71; col++)
        {
            maze[row][col] = line[col];
        }
        row++;
    }
}
int smallestDistance()
{
    float smallest = dis[0];
    int smallestidx = 0;
    for (int i = 0; i < 4; i++)
    {
        if (smallest > dis[i])
        {
            smallest = dis[i];
            smallestidx = i;
        }
    }
    return smallestidx;
}
bool ghostmovement4()
{
    dis[0] = 10000;
    dis[1] = 10000;
    dis[2] = 10000;
    dis[3] = 10000;
    if (maze[ghost4X][ghost4Y - 1] == ' ' || maze[ghost4X][ghost4Y - 1] == '.' || maze[ghost4X][ghost4Y - 1] == 'P')
    {
        dis[0] = sqrt(pow((ghost4X - pacmanX), 2) + pow((ghost4Y - 1 - pacmanY), 2));
    }
    if (maze[ghost4X][ghost4Y + 1] == ' ' || maze[ghost4X][ghost4Y + 1] == '.' || maze[ghost4X][ghost4Y + 1] == 'P')
    {
        dis[1] = sqrt(pow((ghost4X - pacmanX), 2) + pow((ghost4Y + 1 - pacmanY), 2));
    }
    if (maze[ghost4X - 1][ghost4Y] == ' ' || maze[ghost4X - 1][ghost4Y] == '.' || maze[ghost4X - 1][ghost4Y] == 'P')
    {
        dis[2] = sqrt(pow((ghost4X - 1 - pacmanX), 2) + pow((ghost4Y - pacmanY), 2));
    }
    if (maze[ghost4X + 1][ghost4Y] == ' ' || maze[ghost4X + 1][ghost4Y] == '.' || maze[ghost4X + 1][ghost4Y] == 'P')
    {
        dis[3] = sqrt(pow((ghost4X + 1 - pacmanX), 2) + pow((ghost4Y - pacmanY), 2));
    }
    int smallestidx = smallestDistance();
    if (smallestidx == 0)
    {
        if (maze[ghost4X][ghost4Y - 1] == ' ' || maze[ghost4X][ghost4Y - 1] == '.' || maze[ghost4X][ghost4Y - 1] == 'P')
        {
            gotoxy(ghost4Y, ghost4X);
            cout << previousItem;
            ghost4Y = ghost4Y - 1;
            previousItem = maze[ghost4X][ghost4Y];
            gotoxy(ghost4Y, ghost4X);
            cout << "G";
        }
    }
    else if (smallestidx == 1)
    {
        if (maze[ghost4X][ghost4Y + 1] == ' ' || maze[ghost4X][ghost4Y + 1] == '.' || maze[ghost4X][ghost4Y + 1] == 'P')
        {
            gotoxy(ghost4Y, ghost4X);
            cout << previousItem;
            ghost4Y = ghost4Y + 1;
            previousItem = maze[ghost4X][ghost4Y];
            gotoxy(ghost4Y, ghost4X);
            cout << "G";
        }
    }
    else if (smallestidx == 2)
    {
        if (maze[ghost4X - 1][ghost4Y] == ' ' || maze[ghost4X - 1][ghost4Y] == '.' || maze[ghost4X - 1][ghost4Y] == 'P')
        {
            gotoxy(ghost4Y, ghost4X);
            cout << previousItem;
            ghost4X = ghost4X - 1;
            previousItem = maze[ghost4X][ghost4Y];
            gotoxy(ghost4Y, ghost4X);
            cout << "G";
        }
    }
    else if (smallestidx == 3)
    {
        if (maze[ghost4X + 1][ghost4Y] == ' ' || maze[ghost4X + 1][ghost4Y] == '.' || maze[ghost4X + 1][ghost4Y] == 'P')
        {
            gotoxy(ghost4Y, ghost4X);
            cout << previousItem;
            ghost4X = ghost4X + 1;
            previousItem = maze[ghost4X][ghost4Y];
            gotoxy(ghost4Y, ghost4X);
            cout << "G";
        }
    }
    if (ghost4X == pacmanX && ghost4Y == pacmanY)
    {
        return 0;
    }

    return 1;
}