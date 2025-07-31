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
        bool valid = true;
        cout << " ▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬" << endl;
        cout << "\n \t PLAYER PROFILE " << endl;

        do
        {
            cout << " \n \t Enter your name: ";
            cin >> data[i].name;

            for (char c : data[i].name)
            {
                if (!isalpha(c))
                    valid = false;

                else if (isalpha(c))
                    valid = true;
            }

            if (!valid)
            {

                SetConsoleTextAttribute(hConsole, 13);

                cout << "\n \t Invalid name. Use only letters (no numbers or symbols)." << endl;

                SetConsoleTextAttribute(hConsole, 9);
            }
        } while (!valid);

        do
        {
            valid = true; // Reiniciar la bandera en cada iteración

            cout << "\n\tEnter your age: ";
            cin >> data[i].age;

            // Verifica que la entrada no sea inválida (como letras u otros símbolos)
            if (cin.fail())
            {
                cin.clear();            // limpia el estado de error
                cin.ignore(1000, '\n'); // limpia el buffer
                valid = false;

                SetConsoleTextAttribute(hConsole, 13); // rojo
                cout << "\t\n\t Invalid input. Please enter a numeric age.\n";
                SetConsoleTextAttribute(hConsole, 9); // color normal
                continue;                             // vuelve a pedir
            }

            if (data[i].age < 18 || data[i].age > 90)
            {
                valid = false;

                SetConsoleTextAttribute(hConsole, 13); // rosa
                cout << "\t\n\t Age restriction: only users aged 18 to 90 can play." << endl;
                SetConsoleTextAttribute(hConsole, 9);
            }

        } while (!valid);

        do
        {

            cout << "\n \t Enter your initial balance: $ ";
            cin >> data[i].balance;

            if (cin.fail())
            {

                SetConsoleTextAttribute(hConsole, 13);

                cout << "\n\t\t Invalid number" << endl;

                SetConsoleTextAttribute(hConsole, 9);
            }
            else if (data[i].balance < 500)
            {

                SetConsoleTextAttribute(hConsole, 13);

                cout << "\n \t You do not have enough money to bet." << endl;
                cout << "\n \t You must to bet more than $500." << endl;

                SetConsoleTextAttribute(hConsole, 9);
            }
        } while (data[i].balance < 700);

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
