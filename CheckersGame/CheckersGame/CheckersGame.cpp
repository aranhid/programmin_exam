#include <iostream>
#include <Windows.h>
#include "Checkers.h"

int main()
{
   /* system("color 5F");
    Checker checker("2A", CheckerColor::COLOR_WHITE, CheckerStatus::NORMAL);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << endl << "TEXT";*/
    Checkers game("input.txt");

    while (true)
    {
        switch (game.getTurn())
        {
        case CheckerColor::WHITE:
            cout << "White turn" << endl;
            break;
        case CheckerColor::BLACK:
            cout << "Black turn" << endl;
            break;
        }
        game.printGameField();
        /*game.move("3A", "4A");
        game.printGameField();*/
        string from = "";
        string to = "";
        cin >> from;
        if (from == "q")
            break;
        cin >> to;
        if (to == "q")
            break;
        if (game.move(from, to))
        {
            game.changeTurn();
        }
    }
}
