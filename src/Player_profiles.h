#ifndef PLAYER_PROFILES_H
#define PLAYER_PROFILES_H

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

struct Player
{
    string name;
    int age;
    int balance;
    int bet;
    int wins;
};

Player data[2];
int total = 0;

void add()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 9);

    cout << R"(
                                                        ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
                                                           PLAYER PROFILE SETUP 
                                                        ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄ 
    )" << endl;

    if (total >= 2)
    {
        cout << "Full capacity" << endl;
        return;
    }

    for (int i = total; i < 2; i++)
    {
        cout << " ▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬" << endl;
        cout << "\n \t PLAYER PROFILE " << endl;

        cout << " \n \t Enter your name: ";
        cin >> data[i].name;

        bool valid = true;
        for (char c : data[i].name)
        {
            if (!isalpha(c))
                valid = false;
        }

        if (!valid)
        {
            cout << "\n \t Invalid name. Use only letters (no numbers or symbols)." << endl;
            exit(0);
        }

        cout << "\n \t Enter your age: ";
        cin >> data[i].age;

        if (cin.fail())
        {
            cout << "\n\t\t Invalid number" << endl;
            exit(0);
        }
        else if (data[i].age < 18 || data[i].age > 90)
        {
            cout << "\t \n Age restriction: only users aged 18 to 90 can play." << endl;
            exit(0);
        }

        cout << "\n \t Enter your initial balance: $ ";
        cin >> data[i].balance;

        if (cin.fail())
        {
            cout << "\n\t\t Invalid number" << endl;
            exit(0);
        }
        else if (data[i].balance < 500)
        {
            cout << "\n \t You do not have enough money to bet." << endl;
            cout << "\n \t You must to bet more than $500." << endl;
            cout << "\n\t Please restart the game." << endl;
            exit(0);
        }

        ++total;

        cout << "\n \t Added!" << endl;
        cout << " ▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬" << endl;
    }
}

void Save()
{
    ofstream file("src/Player_profiles.txt");

    for (int i = 0; i < total; i++)
    {
        file << data[i].name << " - " << data[i].age << " years - $ " << data[i].balance << endl;
    }

    file.close();

    cout << "\n \t Player profiles saved successfully \n"
         << endl;
}

#endif
