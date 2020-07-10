#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <string>

#include "Position.h"
#include "Checker.h"
#include "Man.h"
#include "GameField.h"

using namespace std;

class Game
{
public:
    GameField field;
    int blackCount = 0;
    int whiteCount = 0;
    CheckerColor turn = CheckerColor::WHITE;
    bool isTurnChanged = false;

    Position currentPos;

    Game(string path);
    Game(const Game& game);

    void printField();
    void changeTurn();
    vector<Step> getAllPossiblePositions();
    void makeStep(Step step);
    int getEnemyCount();
};

