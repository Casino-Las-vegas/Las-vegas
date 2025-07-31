#include <iostream>
#include <windows.h> // Required for SetConsoleOutputCP and Windows functions

#include "src/Player_profiles.h"
#include "src/Bingo.h"
#include "src/Menu.h"
#include "src/Dice.h"
#include "src/Roulette.h"
#include "src/Poker.h"

using namespace std;

int main()
{

    int option;

    do
    {
        SetConsoleOutputCP(CP_UTF8); // Set console to UTF-8 encoding
        Logo();                      // Display the logo

        system("cls"); // Clear the screen

        add();  // Add players
        Save(); // Save player data

        option = ShowMenu(); // Show the menu and store the chosen option

        switch (option)
        {
        case 1:
            RunningBingo(); // Load player data and get bets
            BingoCards();   // Generate bingo cards
            RandomNumber(); // Generate first random number
            Boards();       // Display boards and current scores
            Play();         // Start game loop
            Sleep(4000);
            break;

        case 2:
            cout << "Dice" << endl;
            runTheHouseofDice(); // Run "The House of Dice" game
            Sleep(4000);
            break;

        case 3:
            SetConsoleOutputCP(CP_UTF8); // Para que los símbolos como ♠ funcionen

            ReadFiles();                         // 1. Primero cargar el archivo
            StartPokerBet();                     // 2. Luego pedir apuestas
            dealCards();      
                           // 3. Repartir cartas una vez cargadas
            printHandHorizontal(player1Hand, 5); // 4. Mostrar
            printHandHorizontal(player2Hand, 5);

            changeCards(player1Hand, data[0].name);
            changeCards(player2Hand, data[1].name);

            printHandHorizontal(player1Hand, 5);
            printHandHorizontal(player2Hand, 5);

            evaluateHands();
            Sleep(4000);
            break;

        case 4:
            cout << "Roulette" << endl;
            playRoulette();
            Sleep(4000);
            break;

        case 5:
            exit(0); // Exit the program
            break;

        default:
            break;
        }

    } while (option != 5); // Empty loop to keep console open if not exiting

    system("pause"); // Pause before closing the console
    return 0;
}