#ifndef BINGO_H
#define BINGO_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

const int rows = 5;
const int cols = 5;
int board1[rows][cols];
int board2[rows][cols];

extern Player data[2];

void RunningBingo()
{
    ifstream file("src/Player_profiles.txt");

    if (!file.is_open())
    {
        cout << "ERROR: Could not open the file." << endl;
        return;
    }

    string line;
    int i = 0;
    while (getline(file, line) && i < 2)
    {
        stringstream ss(line);
        string name, delete1, delete2, years, dollarSign;
        int age;
        float balance;

        ss >> name >> delete1 >> age >> years >> delete2 >> dollarSign >> balance;

        data[i].name = name;
        data[i].age = age;
        data[i].balance = balance;
        i++;
    }
    file.close();

    system("cls");

    for (int k = 0; k < i; k++)
    {
        bool valid = false;
        while (!valid)
        {
            cout << R"(
                                                     ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
                                                     ▓▓                                      ▓▓
                                                     ▓▓   ▓▓      ▓▓   ▓▓      ▓▓    ▓▓▓▓    ▓▓
                                                     ▓▓     ▓▓    ▓▓   ▓▓      ▓▓       ▓▓   ▓▓
                                                     ▓▓   ▓▓▓▓   ▓▓   ▓▓▓▓▓▓  ▓▓   ▓▓▓▓▓▓    ▓▓
                                                     ▓▓                                      ▓▓
                                                     ▓▓          W E L C O M E   T O         ▓▓
                                                     ▓▓               B I N G O              ▓▓
                                                     ▓▓                                      ▓▓
                                                     ▓▓  ▓▓▓▓▓   ▓▓▓▓   ▓▓  ▓▓   ▓▓▓▓▓▓▓▓▓▓  ▓▓
                                                     ▓▓    ▓▓     ▓▓   ▓▓▓▓▓▓     ▓▓         ▓▓
                                                     ▓▓  ▓▓▓▓    ▓▓   ▓▓  ▓▓     ▓▓▓▓▓▓      ▓▓
                                                     ▓▓                                      ▓▓
                                                     ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
            )" << endl;

            cout << "\t\t\t\t\t\t\t   ══════════════════════════════" << endl;
            cout << "\t\t\t\t\t\t\t\t" << "Welcome: " << data[k].name << endl;
            cout << "\t\t\t\t\t\t\t\tHow much do you want to bet? " << endl;
            cout << "\t\t\t\t\t\t\t\t$";
            cin >> data[k].bet;

            cout << "\t\t\t\t\t\t\t\tSaving info..." << endl;
            Sleep(2000);
            cout << "\t\t\t\t\t\t\t    ══════════════════════════════" << endl;

            if (data[k].bet < 75)
            {
                cout << "\n\t\t\t\t\t\t\tYou must bet at least $75.\n";
                Sleep(2000);
                system("cls");
            }
            else if (data[k].bet > data[k].balance)
            {
                cout << "\n\t\t\t\t\t\tYou don’t have enough balance for that bet.\n";
                Sleep(2000);
                system("cls");
            }
            else
            {
                valid = true;
                cout << "\t\t\t\t\t\t\tBet registered successfully.\n";
                system("cls");
            }
        }
    }

    system("cls");
}

void BingoCards()
{
    srand(time(0));
    for (int i = 0; i < rows; i++)
    {
        cout << "\t\t\t";
        for (int j = 0; j < cols; j++)
        {
            board1[i][j] = rand() % 99 + 1;
            board2[i][j] = rand() % 99 + 1;
        }
    }
}

bool numbers[100] = {false};

void RandomNumber()
{
    cout << R"(


▓                ▓
▓   B I N G O    ▓
▓                ▓  )"
         << endl;

    int number;
    do
    {
        number = rand() % 99 + 1;
    } while (numbers[number]);

    numbers[number] = true;

    cout << "\t\t\t\t\t\t\t       RANDOM NUMBER: " << number << "\n"
         << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (board1[i][j] == number)
                board1[i][j] = -2;
            if (board2[i][j] == number)
                board2[i][j] = -2;
        }
    }
}

void Boards()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "\n\t\t\t\t\tPLAYER 1\t\t\t\t\t\t\tPLAYER 2\n\n";
    cout << " \t\t\t══════════════════════════════════════\t\t\t\t ══════════════════════════════════════\n";
    for (int i = 0; i < rows; i++)
    {
        cout << "\t\t\t";
        for (int j = 0; j < cols; j++)
        {
            if (board1[i][j] == -2)
            {
                SetConsoleTextAttribute(hConsole, 3);
                cout << " [ XX ] ";
            }
            else if (board1[i][j] < 10)
            {
                SetConsoleTextAttribute(hConsole, 5);
                cout << " [ 0" << board1[i][j] << " ] ";
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 5);
                cout << " [ " << board1[i][j] << " ] ";
            }
        }

        cout << "\t\t\t";

        for (int j = 0; j < cols; j++)
        {
            if (board2[i][j] == -2)
            {
                SetConsoleTextAttribute(hConsole, 3);
                cout << " [ XX ] ";
            }
            else if (board2[i][j] < 10)
            {
                SetConsoleTextAttribute(hConsole, 5);
                cout << " [ 0" << board2[i][j] << " ] ";
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 5);
                cout << " [ " << board2[i][j] << " ] ";
            }
        }

        cout << "\n\n";
    }

    cout << " \t\t\t══════════════════════════════════════\t\t\t\t ══════════════════════════════════════\n";

    int score1 = 0, score2 = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (board1[i][j] == -2)
                score1++;
            if (board2[i][j] == -2)
                score2++;
        }
    }

    SetConsoleTextAttribute(hConsole, 5);

    cout << "\n";
    cout << "            \t     ╔══════════════════════════╦═══════════════════════╗\n";
    cout << "            \t     ║ " << data[0].name << "\t\t\t\t" << data[1].name << "\t\t" << endl;
    cout << "            \t     ║  \t                                        ║" << endl;
    cout << "            \t     ╠══════════════════════════╬═══════════════════════╣\n";
    cout << "            \t     ║        ";

    if (score1 < 10)
        cout << score1 << "           ";
    else if (score1 < 100)
        cout << score1 << "          ";
    else
        cout << score1 << "         ";

    cout << "      ║        ";

    if (score2 < 10)
        cout << score2 << "           ";
    else if (score2 < 100)
        cout << score2 << "          ";
    else
        cout << score2 << "         ";

    cout << "   ║\n";
    cout << "            \t     ╚══════════════════════════╩═══════════════════════╝\n";

    bool Win = false;
    int plus = 0;

    if (score1 != 25 && score2 != 25)
    {
        cout << "Waiting for a winner..." << endl;
    }
    if (score1 == 25)
    {
        SetConsoleTextAttribute(hConsole, 3);
        plus = data[0].bet + data[1].bet;
        Win = true;
        cout << "================ BINGO RESULT ================" << endl;
        cout << data[0].name << " has won and taken : $ " << plus << " prize pool. Congratulations!" << endl;
        cout << data[1].name << " has lost his $" << data[1].bet << " bet. Better luck next time." << endl;
        cout << "=============================================" << endl;
        data[1].balance -= data[1].bet;

        ofstream file("Bingo_scores.txt", ios::app);
        file << "=== BINGO GAME ===\n";
        file << "Player 1: " << data[0].name << " - Wins: " << score1 << " - Balance: $" << data[0].balance << endl;
        file << "Player 2: " << data[1].name << " - Wins: " << score2 << " - Balance: $" << data[1].balance << endl;
        file.close();
    }

    else if (score2 == 25)
    {
        SetConsoleTextAttribute(hConsole, 3);
        plus = data[1].bet + data[0].bet;
        Win = true;
        cout << "================ BINGO RESULT ================" << endl;
        cout << data[1].name << " has won and taken : $ " << plus << " prize pool. Congratulations!" << endl;
        cout << data[0].name << " has lost his $" << data[0].bet << " bet. Better luck next time." << endl;
        cout << "=============================================" << endl;
        data[0].balance -= data[0].bet;

        ofstream file("Bingo_scores.txt", ios::app);
        file << "=== BINGO GAME ===\n";
        file << "Player 1: " << data[0].name << " - Wins: " << score1 << " - Balance: $" << data[0].balance << endl;
        file << "Player 2: " << data[1].name << " - Wins: " << score2 << " - Balance: $" << data[1].balance << endl;
        file.close();
    }
}

bool CardComplete(int board[rows][cols])
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (board[i][j] != -2)
                return false;
    return true;
}

void Play()
{
    do
    {
        system("pause");
        system("cls");
        RandomNumber();
        Boards();
    } while (!CardComplete(board1) && !CardComplete(board2));
    return;
}

#endif
