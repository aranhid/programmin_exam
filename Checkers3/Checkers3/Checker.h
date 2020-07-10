#pragma once

#include <vector>
#include "Position.h"
#include "Step.h"

class GameField;

using namespace std;

enum class CheckerColor
{
    NONE,
    BLACK,
    WHITE
};

enum class CheckerType
{
    NONE,
    MAN,
    KING
};

class Checker
{
public:
    const CheckerType type = CheckerType::NONE;
    CheckerColor color = CheckerColor::NONE;
    Position position;

    Checker();
    Checker(Position position) : position(position) {};
    Checker(const Checker& checker);

    virtual vector<Step> getPosiblePositions(GameField field);

    CheckerColor getEnemy();
    virtual CheckerType getType();
};

