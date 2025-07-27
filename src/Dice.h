#ifndef DICE_H
#define DICE_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <fstream>
#include <windows.h>
#include <limits>

#include "Player_profiles.h"
extern Player data[2];

using namespace std;

string dice[6][5] = {
    {" ------- ", "|       |", "|   *   |", "|       |", " ------- "},
    {" ------- ", "| *     |", "|       |", "|     * |", " ------- "},
    {" ------- ", "| *     |", "|   *   |", "|     * |", " ------- "},
    {" ------- ", "| *   * |", "|       |", "| *   * |", " ------- "},
    {" ------- ", "| *   * |", "|   *   |", "| *   * |", " ------- "},
    {" ------- ", "| *   * |", "| *   * |", "| *   * |", " ------- "}};

// Console color definitions for Windows
enum ConsoleColor {
    DEFAULT = 7,
    GREEN = 10,
    RED = 12,
    YELLOW = 14,
    CYAN = 11,
    MAGENTA = 13
};

void setColor(ConsoleColor color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void centerText(const string &text, int width = 60, ConsoleColor color = DEFAULT)
{
    setColor(color);
    int spaces = max(0, (width - static_cast<int>(text.length())) / 2);
    for (int i = 0; i < spaces; i++)
        cout << " ";
    cout << text << endl;
    setColor(DEFAULT);
}

void centerDiceLine(const string &line, int width = 60)
{
    int spaces = max(0, (width - static_cast<int>(line.length())) / 2);
    for (int i = 0; i < spaces; i++)
        cout << " ";
    cout << line << endl;
}

int rollDice()
{
    return rand() % 6 + 1;
}

void showDiceHorizontal(int d1, int d2)
{
    for (int i = 0; i < 5; i++)
    {
        string line = dice[d1 - 1][i] + "   " + dice[d2 - 1][i];
        centerDiceLine(line);
    }
}

// Robust input validation for bets
float getValidBet(float maxBet, const string& playerName)
{
    float bet;
    while (true)
    {
        centerText(playerName + ", you have $" + to_string(maxBet) + ". Enter your bet:", 60, CYAN);
        cout << "\t\t\t";
        cin >> bet;
        if (cin.fail() || bet > maxBet || bet <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            centerText("Invalid bet! A minimum bet of $1 was assigned.", 60, YELLOW);
            bet = 1;
            break;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    return bet;
}

// Show quick rules before each round
void showShortRules()
{
    setColor(MAGENTA);
    cout << "\n";
    centerText("QUICK RULES:", 60, MAGENTA);
    centerText("1. Both players bet each round.", 60, MAGENTA);
    centerText("2. Each rolls 2 dice.", 60, MAGENTA);
    centerText("3. Highest total wins the round and the opponent's bet.", 60, MAGENTA);
    centerText("4. Tie: no money exchanged.", 60, MAGENTA);
    centerText("5. First to 3 wins or most wins after 6 rounds is the winner.", 60, MAGENTA);
    setColor(DEFAULT);
}

void showStats()
{
    ifstream file("Dice_scores.txt");
    if (!file.is_open()) return;
    string line;
    centerText("=== GAME HISTORY ===", 60, CYAN);
    int count = 0;
    while (getline(file, line) && count < 10) // Show only last 10 games
    {
        cout << line << endl;
        if (line.find("-----------------------------------------") != string::npos)
            count++;
    }
    file.close();
    cout << endl;
}

void playVsComputer()
{
    srand(time(0));
    int wins[2] = {0, 0};
    add();
    Save();

    system("cls");
    centerText("SINGLE PLAYER MODE: You play against the computer.", 60, CYAN);
    centerText("Your name: " + data[0].name, 60, CYAN);
    data[1].name = "Computer";

    int round = 1;
    while (wins[0] < 3 && wins[1] < 3 && round <= 6)
    {
        system("cls");
        showShortRules();
        cout << endl;
        centerText("ROUND " + to_string(round), 60, YELLOW);
        cout << endl;

        float bet[2];
        bet[0] = getValidBet(data[0].balance, data[0].name);
        bet[1] = min(1.0f + rand() % int(data[1].balance), data[1].balance); // Computer random bet

        int sum[2];
        for (int i = 0; i < 2; i++)
        {
            cout << endl;
            centerText("Rolling dice for " + data[i].name + "...", 60, CYAN);
            int d1 = rollDice();
            int d2 = rollDice();
            sum[i] = d1 + d2;
            showDiceHorizontal(d1, d2);
            centerText("Total: " + to_string(sum[i]), 60, CYAN);
        }

        if (sum[0] > sum[1])
        {
            cout << endl;
            centerText(data[0].name + " wins the round!", 60, GREEN);
            wins[0]++;
            data[0].balance += bet[1];
            data[1].balance -= bet[1];
        }
        else if (sum[1] > sum[0])
        {
            cout << endl;
            centerText(data[1].name + " wins the round!", 60, RED);
            wins[1]++;
            data[1].balance += bet[0];
            data[0].balance -= bet[0];
        }
        else
        {
            cout << endl;
            centerText("It's a tie! No money exchanged.", 60, YELLOW);
        }

        cout << endl;
        centerText("Current Scores:", 60, CYAN);
        centerText(data[0].name + " [" + to_string(wins[0]) + " wins, $" + to_string(data[0].balance) + "]", 60, CYAN);
        centerText("VS", 60, CYAN);
        centerText(data[1].name + " [" + to_string(wins[1]) + " wins, $" + to_string(data[1].balance) + "]", 60, CYAN);

        centerText("Press any key to continue...", 60, CYAN);
        system("pause >nul");

        round++;

        if (data[0].balance <= 0 || data[1].balance <= 0)
        {
            cout << endl;
            centerText("A player has run out of money! Ending game...", 60, RED);
            break;
        }
    }

    cout << endl;
    centerText("==================== FINAL RESULT ====================", 60, YELLOW);
    if (wins[0] > wins[1])
        centerText(data[0].name + " wins the game with $" + to_string(data[0].balance) + " remaining.", 60, GREEN);
    else if (wins[1] > wins[0])
        centerText(data[1].name + " wins the game with $" + to_string(data[1].balance) + " remaining.", 60, RED);
    else
        centerText("The game ended in a tie.", 60, YELLOW);
    centerText("======================================================", 60, YELLOW);
    centerText("Thank you for playing The House of Dice!", 60, CYAN);

    ofstream file("Dice_scores.txt", ios::app);
    file << "=== THE HOUSE OF DICE (vs Computer) ===\n";
    file << "Player: " << data[0].name << " - Wins: " << wins[0] << " - Balance: $" << data[0].balance << endl;
    file << "Computer - Wins: " << wins[1] << " - Balance: $" << data[1].balance << endl;
    if (wins[0] > wins[1])
        file << "Winner: " << data[0].name << "\n";
    else if (wins[1] > wins[0])
        file << "Winner: Computer\n";
    else
        file << "Result: Tie\n";
    file << "-----------------------------------------\n";
    file.close();
}

// Main improved game
void runTheHouseofDice()
{
    srand(time(0));
    int wins[2] = {0, 0};
    add();
    Save();

    while (true) {
        system("cls");
        setColor(CYAN);
        cout << R"(

                   ╔════════════════════════════════════════════════════════════════════════╗
      ▓▓           ║                                                                        ║
    ▓▓▓▓▓▓         ║   █████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█████     ║
  ▓▓▓▓▓▓▓▓▓▓       ║   █    ▒▒▒▒▒▒▒▒▒▒▒▒▒ ▄ THE HOUSE OF DICE ▄ ▒▒▒▒▒▒▒▒▒▒▒▒▒    █     ║
▓▓▓▓▓▓▓▓▓▓▓▓▓▓     ║   █    ▒▒▒▒▒▒▒▒▒▒▒▒▒                     ▒▒▒▒▒▒▒▒▒▒▒▒▒    █     ║
  ▓▓▓▓▓▓▓▓▓▓       ║   █████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█████     ║
    ▓▓▓▓▓▓         ║                                                                        ║
      ▓▓           ║                    WELCOME TO THE HOUSE OF DICE                        ║          ▓▓
                   ║                                                                        ║        ▓▓▓▓▓▓
                   ║   1. Play 2 players                                                    ║      ▓▓▓▓▓▓▓▓▓▓
                   ║   2. Play against the computer                                         ║    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓
                   ║   3. View game history                                                 ║      ▓▓▓▓▓▓▓▓▓▓
                   ║   4. Exit                                                             ║        ▓▓▓▓▓▓
                   ║                                                                        ║          ▓▓
                   ╚════════════════════════════════════════════════════════════════════════╝

)" << endl;
        setColor(DEFAULT);
        centerText("Select an option (1-4):", 60, CYAN);
        int option;
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (option == 1) {
            // 2 player game
            int round = 1;
            wins[0] = wins[1] = 0;
            add();
            Save();
            data[1].name = data[1].name; // Ensure name is not overwritten
            while (wins[0] < 3 && wins[1] < 3 && round <= 6)
            {
                system("cls");
                showShortRules();
                cout << endl;
                centerText("ROUND " + to_string(round), 60, YELLOW);
                cout << endl;

                float bet[2];
                for (int i = 0; i < 2; i++)
                    bet[i] = getValidBet(data[i].balance, data[i].name);

                int sum[2];
                for (int i = 0; i < 2; i++)
                {
                    cout << endl;
                    centerText("Rolling dice for " + data[i].name + "...", 60, CYAN);
                    int d1 = rollDice();
                    int d2 = rollDice();
                    sum[i] = d1 + d2;
                    showDiceHorizontal(d1, d2);
                    centerText("Total: " + to_string(sum[i]), 60, CYAN);
                }

                if (sum[0] > sum[1])
                {
                    cout << endl;
                    centerText(data[0].name + " wins the round!", 60, GREEN);
                    wins[0]++;
                    data[0].balance += bet[1];
                    data[1].balance -= bet[1];
                }
                else if (sum[1] > sum[0])
                {
                    cout << endl;
                    centerText(data[1].name + " wins the round!", 60, RED);
                    wins[1]++;
                    data[1].balance += bet[0];
                    data[0].balance -= bet[0];
                }
                else
                {
                    cout << endl;
                    centerText("It's a tie! No money exchanged.", 60, YELLOW);
                }

                cout << endl;
                centerText("Current Scores:", 60, CYAN);
                centerText(data[0].name + " [" + to_string(wins[0]) + " wins, $" + to_string(data[0].balance) + "]", 60, CYAN);
                centerText("VS", 60, CYAN);
                centerText(data[1].name + " [" + to_string(wins[1]) + " wins, $" + to_string(data[1].balance) + "]", 60, CYAN);

                centerText("Press any key to continue...", 60, CYAN);
                system("pause >nul");

                round++;

                if (data[0].balance <= 0 || data[1].balance <= 0)
                {
                    cout << endl;
                    centerText("A player has run out of money! Ending game...", 60, RED);
                    break;
                }
            }

            cout << endl;
            centerText("==================== FINAL RESULT ====================", 60, YELLOW);
            if (wins[0] > wins[1])
                centerText(data[0].name + " wins the game with $" + to_string(data[0].balance) + " remaining.", 60, GREEN);
            else if (wins[1] > wins[0])
                centerText(data[1].name + " wins the game with $" + to_string(data[1].balance) + " remaining.", 60, RED);
            else
                centerText("The game ended in a tie.", 60, YELLOW);
            centerText("======================================================", 60, YELLOW);
            centerText("Thank you for playing The House of Dice!", 60, CYAN);

            ofstream file("Dice_scores.txt", ios::app);
            file << "=== THE HOUSE OF DICE ===\n";
            file << "Player 1: " << data[0].name << " - Wins: " << wins[0] << " - Balance: $" << data[0].balance << endl;
            file << "Player 2: " << data[1].name << " - Wins: " << wins[1] << " - Balance: $" << data[1].balance << endl;
            if (wins[0] > wins[1])
                file << "Winner: " << data[0].name << "\n";
            else if (wins[1] > wins[0])
                file << "Winner: " << data[1].name << "\n";
            else
                file << "Result: Tie\n";
            file << "-----------------------------------------\n";
            file.close();

            centerText("Do you want to play again? (y/n):", 60, CYAN);
            char again;
            cin >> again;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (again == 'n' || again == 'N') break;
        }
        else if (option == 2) {
            playVsComputer();
            centerText("Do you want to play again? (y/n):", 60, CYAN);
            char again;
            cin >> again;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (again == 'n' || again == 'N') break;
        }
        else if (option == 3) {
            system("cls");
            showStats();
            centerText("Press any key to return to the main menu...", 60, CYAN);
            system("pause >nul");
        }
        else if (option == 4) {
            break;
        }
        else {
            centerText("Invalid option. Try again.", 60, RED);
            system("pause >nul");
        }
    }
}

#endif