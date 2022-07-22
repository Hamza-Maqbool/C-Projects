#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <conio.h>
using namespace std;

// FUNCTION PROTOTYPES

void header();
int mainMenu();
void loadmaze();
void printmaze();
void gotoxy(int x, int y);
bool moveLeft();
bool moveRight();
bool EnemycarMove();
void lineClear();
void bulletMove();
void carFire();
void printStats();
void gameOver();
void scoresSorting();
void previousScores();
void calculateScore();
void resetMaze();
string parseRecord(string record, int field);
void getScores();
void storeScores();
bool groundCheck();
int randomAxis();
void randomEnemycar();
void fly();

// DATA STRUCTURES

string names[50];
int scores[50], playerCount = 0;
char maze1[36][63];
int ship1X = 34;
int ship2X = 33;
int ship3X = 32;
int ship4X = 31;
int ship1Ys = 31;
int ship1Ye = 35;
int ship2Ys = 32;
int ship2Ye = 34;
int ship3Ys = 32;
int ship3Ye = 34;
int ship4Y = 33;
int score, lifes;
int alterationCount, speed;

main()
{
    getScores();
    while (true)
    {
        int option = mainMenu();
        if (option == 1)
        {
            loadmaze();
            alterationCount == 0;
            lifes = 3;
            score = 0;
            speed = 40;
            header();
            cout << "Enter you name: ";
            cin.ignore();
            getline(cin, names[playerCount]);
            while (lifes > 0)
            {
                system("cls");
                printmaze();
                bool gameRunning = true;
                bool gameRunning1 = true;
                bool gameRunning2 = true;
                while (gameRunning && gameRunning1 && gameRunning2)
                {
                    Sleep(0);
                    lineClear();
                    if (score % 100 == 0 && score > 0 && speed > 15)
                    {
                        speed = speed - 5;
                    }
                    if (alterationCount % speed == 0)
                    {
                        randomEnemycar();
                    }
                    if (alterationCount % 3 == 0)
                    {
                        gameRunning = EnemycarMove();
                    }
                    alterationCount++;
                    if (GetAsyncKeyState(VK_LEFT))
                    {
                        gameRunning1 = moveLeft(); // Function call to move the car towards left
                    }
                    if (GetAsyncKeyState(VK_RIGHT))
                    {
                        gameRunning1 = moveRight(); // Function call to move the car towards right
                    }
                    if (GetAsyncKeyState(VK_SHIFT))
                    {
                        fly();
                    }
                    if (GetAsyncKeyState(VK_SPACE))
                    {
                        carFire();
                    }
                    bulletMove();
                    printStats();
                    gameRunning2 = groundCheck();
                }
                lifes--;
                resetMaze();
                Sleep(1000);
            }
            scores[playerCount] = score;
            playerCount++;
            storeScores();
            gameOver();
        }
        else if (option == 2)
        {
            previousScores();
        }
        else if (option == 3)
        {
            break;
        }
        else
        {
            cout << "Wrong Option!";
        }
    }
}

void loadmaze()
{
    fstream file;
    file.open("maze1.txt", ios::in);
    for (int row = 0; row < 36; row = row + 1)
    {
        string line;
        getline(file, line);
        for (int col = 0; col < 63; col++)
        {
            maze1[row][col] = line[col];
        }
    }
    file.close();
}
void printmaze()
{
    for (int row = 0; row < 36; row = row + 1)
    {
        for (int col = 0; col < 63; col = col + 1)
        {
            cout << maze1[row][col];
        }
        cout << endl;
    }
}
void resetMaze()
{
    for (int y = 2; y < 35; y++)
    {
        gotoxy(3, y);
        for (int col = 3; col < 60; col++)
        {
            if (maze1[y][col] = '*')
            {
                maze1[y][col] = ' ';
                cout << maze1[y][col];
            }
        }
    }
}
string parseRecord(string record, int field)
{ // Code to get data from comma seperated fields 
    int commaCount = 1;
    string item;
    for (int x = 0; x < record.length(); x++)
    {
        if (record[x] == ',')
        {
            commaCount = commaCount + 1;
        }
        else if (commaCount == field)
        {
            item = item + record[x];
        }
    }
    return item;
}
void getScores()
{ // Getting Student Record from the file 
    string line;
    fstream inputFile;
    inputFile.open("scores.txt", ios::in);
    while (!(inputFile.eof()))
    {
        getline(inputFile, line);
        names[playerCount] = parseRecord(line, 1);
        scores[playerCount] = stoi(parseRecord(line, 2));
        playerCount++;
    }
    inputFile.close();
}
void storeScores()
{ // Storing Student Data in the file 
    string line;
    fstream outputFile;
    outputFile.open("scores.txt", ios::out);
    for (int i = 0; i < playerCount - 1; i++)
    {
        outputFile << names[i] << "," << scores[i] << endl;
    }
    outputFile << names[playerCount - 1] << "," << scores[playerCount - 1];
    outputFile.close();
}
void scoresSorting()
{
    string temp = " ";
    int temp1 = 0;
    for (int i = 0; i < playerCount - 1; i++)
    {
        for (int j = i + 1; j < playerCount; j++)
        {
            if (scores[j] > scores[i])
            {
                temp1 = scores[j];
                scores[j] = scores[i];
                scores[i] = temp1;
                temp = names[j];
                names[j] = names[i];
                names[i] = temp;
            }
        }
    }
}
void previousScores()
{
    scoresSorting();
    header();

    cout << "\n\t\t\t\t\t\tPlayer Name\t\tScore\n\n";
    for (int i = 0; i < playerCount; i++)
    {
        cout << "\t\t\t\t\t\t" << names[i] << "\t\t" << scores[i] << endl;
    }
    cout << endl
         << endl;
    system("pause");
}
void gotoxy(int x, int y)
{
    COORD cursorPosition;
    cursorPosition.X = x;
    cursorPosition.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void header()
{
    system("cls");
    gotoxy(0, 2);

    cout << "****************************************************************************************************************************" << endl;
    cout << "|      ________     ______    ______                    _______  __   __  ______  __   __  ______  __   __  ______  ______  | " << endl;
    cout << "|     / ____  /    / ___  /  / __  /                   / _____/ / /  / / / __  / / /  / / /_  __/ / /  / / / __  / / __  /  | " << endl;
    cout << "|    / /   /_/    / /__/ /  / /_/ /                   / /____  / /  / / / /_/ / / /  / /   / /   / /  / / / / / / / /_/ /   | " << endl;
    cout << "|   / /   __     / ___  /  / ____/                   /____  / / /  / / / ____/ / /  / /   / /   / /  / / / / / / / ____/    | " << endl;
    cout << "|  / /___/ /    / /  / /  / / | |                   _____/ / / /__/ / / / | |  | |_/ / __/ /__  | |_/ / / /_/ / / / | |     | " << endl;
    cout << "| /_______/    /_/  /_/  /_/  |_|                  /______/ /______/ /_/  |_|  |____/ /______/  |___ / /_____/ /_/  |_|     |" << endl;
    cout << "|                                                                                                                           | " << endl;
    cout << "****************************************************************************************************************************" << endl;
}
int mainMenu()
{
    int option;
    header();
    cout << "\n\n   1.  Start the game";
    cout << "\n\n   2.  View Previous Scores";
    cout << "\n\n   3.  Exit the Game";
    cout << "\n\n\n Select an option \n";
    cin >> option;
    return option;
}
void calculateScore()
{
    score = score + 5;
}
void printStats()
{
    gotoxy(77, 17);
    cout << ": Score :";
    gotoxy(81, 18);
    cout << score;
    gotoxy(74, 20);
    cout << "  : Lives Left :";
    gotoxy(82, 21);
    cout << lifes;
}
void gameOver()
{
    for (int i = 0; i < 8; i++)
    {
        system("cls");
        gotoxy(0, 6);
        cout << " ______________________________________________________________________________________________________" << endl;
        cout << "|          ________   _______   ___   ______   ______        ________   __   __   ______   ______      |" << endl;
        cout << "|         / ____  /  / ___  /  /   | / __  /  / ____/       / ____  /  / /  / /  / ____/  / __  /      |" << endl;
        cout << "|        / /   /_/  / /__/ /  / /| |/ / / /  / /___        / /   / /  / /  / /  / /___   / /_/ /       |" << endl;
        cout << "|       / / ____   / ___  /  / / |___/ / /  / ____/       / /   / /  / /  / /  / ____/  / ____/        |" << endl;
        cout << "|      / /___/ /  / /  / /  / /       / /  / /____       / /___/ /   | |_/ /  / /___   / / | |         |" << endl;
        cout << "|     /_______/  /_/  /_/  /_/       /_/  /______/      /_______/    |____/  /_____/  /_/  |_|         |" << endl;
        cout << "|______________________________________________________________________________________________________|" << endl;
        Sleep(50);
    }
    system("pause");
}
void lineClear()
{
    for (int col = 0; col < 62; col++)
    {
        if (maze1[1][col] == ' ')
        {
            gotoxy(col, 1);
            cout << " ";
        }
    }
}
int randomAxis()
{
    int result = 3 + (rand() % 55);
    if (result <= 4)
    {
        result = 5;
    }
    if (result >= 57)
    {
        result = 56;
    }
    return result;
}
void randomEnemycar()
{
    int col = randomAxis();
    if (col > 4 && col < 58)
    {
        maze1[2][col] = '*';
        maze1[3][col] = '*';
        maze1[2][col + 1] = '*';
        maze1[3][col + 1] = '*';
    }
}
bool moveLeft()
{
    if (maze1[ship1X][ship1Ys - 1] != '|')
    {
        maze1[ship1X][ship1Ye] = ' ';
        gotoxy(ship1Ye, ship1X);
        cout << " ";
        ship1Ys--;
        ship1Ye--;
        for (int i = ship1Ys; i <= ship1Ye; i++)
        {
            maze1[ship1X][i] = '+';
            gotoxy(i, ship1X);
            cout << "+";
        }
        maze1[ship2X][ship2Ye] = ' ';
        gotoxy(ship2Ye, ship2X);
        cout << " ";
        ship2Ys--;
        ship2Ye--;
        for (int i = ship2Ys; i <= ship2Ye; i++)
        {
            maze1[ship2X][i] = '+';
            gotoxy(i, ship2X);
            cout << "+";
        }
        maze1[ship3X][ship3Ye] = ' ';
        gotoxy(ship3Ye, ship3X);
        cout << " ";
        ship3Ys--;
        ship3Ye--;
        for (int i = ship3Ys; i <= ship3Ye; i++)
        {
            maze1[ship3X][i] = '+';
            gotoxy(i, ship3X);
            cout << "+";
        }
        maze1[ship4X][ship4Y] = ' ';
        gotoxy(ship4Y, ship4X);
        cout << " ";
        ship4Y--;
        maze1[ship4X][ship4Y] = '+';
        gotoxy(ship4Y, ship4X);
        cout << "+";
    }
    return 1;
}
bool moveRight()
{
    if (maze1[ship1X][ship1Ye + 1] != '|')
    {
        maze1[ship1X][ship1Ys] = ' ';
        gotoxy(ship1Ys, ship1X);
        cout << " ";
        ship1Ys++;
        ship1Ye++;
        for (int i = ship1Ys; i <= ship1Ye; i++)
        {
            maze1[ship1X][i] = '+';
            gotoxy(i, ship1X);
            cout << "+";
        }
        maze1[ship2X][ship2Ys] = ' ';
        gotoxy(ship2Ys, ship2X);
        cout << " ";
        ship2Ys++;
        ship2Ye++;
        for (int i = ship2Ys; i <= ship2Ye; i++)
        {
            maze1[ship2X][i] = '+';
            gotoxy(i, ship2X);
            cout << "+";
        }
        maze1[ship3X][ship3Ys] = ' ';
        gotoxy(ship3Ys, ship3X);
        cout << " ";
        ship3Ys++;
        ship3Ye++;
        for (int i = ship3Ys; i <= ship3Ye; i++)
        {
            maze1[ship3X][i] = '+';
            gotoxy(i, ship3X);
            cout << "+";
        }
        maze1[ship4X][ship4Y] = ' ';
        gotoxy(ship4Y, ship4X);
        cout << " ";
        ship4Y++;
        maze1[ship4X][ship4Y] = '+';
        gotoxy(ship4Y, ship4X);
        cout << "+";
    }
    return 1;
}
bool EnemycarMove()
{
    char temp;
    for (int row = 34; row >= 2; row--)
    {
        for (int col = 3; col < 60; col++)
        {
            if (maze1[row][col] == '+' && maze1[row - 1][col] == '*')
            {
                return 0;
            }
            if (maze1[row][col] != '+')
            {
                temp = maze1[row - 1][col];
                maze1[row - 1][col] = maze1[row][col];
                maze1[row][col] = temp;
            }
        }
    }
    for (int y = 2; y < 35; y++)
    {
        gotoxy(3, y);
        for (int col = 3; col < 60; col++)
        {
            cout << maze1[y][col];
        }
    }
    for (int col = 3; col < 60; col++)
    {
        if (maze1[0][col] == 'o')
        {
            gotoxy(col, 0);
            cout << "_";
            maze1[1][col] == '_';
        }
        if (maze1[1][col] == 'o')
        {
            maze1[1][col] == ' ';
            gotoxy(col, 1);
            cout << " ";
        }
    }
    return 1;
}
void carFire()
{
    gotoxy(ship4Y, ship4X - 1);
    cout << "o";
    maze1[ship4X - 1][ship4Y] = 'o';
}
void bulletMove()
{
    char temp;
    for (int row = 1; row < 34; row++)
    {
        for (int col = 3; col < 60; col++)
        {
            if (maze1[row][col] == 'o')
            {
                gotoxy(col, row);
                cout << " ";
                maze1[row][col] = ' ';
                if (maze1[row - 1][col] != '_')
                {
                    if (maze1[row - 1][col] == '*')
                    {
                        gotoxy(col, row - 1);
                        cout << " ";
                        maze1[row - 1][col] = ' ';
                        calculateScore();
                    }
                    else
                    {
                        gotoxy(col, row - 2);
                        cout << "o";
                        maze1[row - 2][col] = 'o';
                    }
                }
            }
        }
    }
    for (int col = 3; col < 60; col++)
    {
        if (maze1[0][col] == 'o')
        {
            gotoxy(col, 0);
            cout << "_";
            maze1[1][col] == '_';
        }
        if (maze1[1][col] == 'o')
        {
            gotoxy(col, 1);
            cout << " ";
            maze1[1][col] == ' ';
        }
    }
}
bool groundCheck()
{
    for (int i = 3; i < 58; i++)
    {
        if (maze1[34][i] == '*')
        {
            return 0;
        }
    }
    return 1;
}
void fly()
{
    maze1[ship4X][ship4Y] = ' ';
    gotoxy(ship4Y, ship4X);
    cout << " ";
    ship4X = ship4X - 4;
    maze1[ship4X][ship4Y] = '+';
    gotoxy(ship4Y, ship4X);
    cout << "+";
    for (int i = ship3Ys; i <= ship3Ye; i++)
    {
        maze1[ship3X][i] = ' ';
        gotoxy(i, ship3X);
        cout << " ";
    }
    ship3X = ship3X - 4;
    for (int i = ship3Ys; i <= ship3Ye; i++)
    {
        maze1[ship3X][i] = '+';
        gotoxy(i, ship3X);
        cout << "+";
    }
    for (int i = ship2Ys; i <= ship2Ye; i++)
    {
        maze1[ship2X][i] = ' ';
        gotoxy(i, ship2X);
        cout << " ";
    }
    ship2X = ship2X - 4;
    for (int i = ship2Ys; i <= ship2Ye; i++)
    {
        maze1[ship2X][i] = '+';
        gotoxy(i, ship2X);
        cout << "+";
    }
    for (int i = ship1Ys; i <= ship1Ye; i++)
    {
        maze1[ship1X][i] = ' ';
        gotoxy(i, ship1X);
        cout << " ";
    }

    ship1X = ship1X - 4;
    for (int i = ship1Ys; i <= ship1Ye; i++)
    {
        maze1[ship1X][i] = '+';
        gotoxy(i, ship1X);
        cout << "+";
    }
}