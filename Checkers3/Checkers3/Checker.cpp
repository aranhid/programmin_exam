#include "Checker.h"
#include "GameField.h"

Checker::Checker()
{
    this->position = Position(0, 0);
}

Checker::Checker(const Checker& checker)
{
    this->position = checker.position;
}

vector<Step> Checker::getPosiblePositions(GameField field)
{
    return vector<Step>();
}

CheckerColor Checker::getEnemy()
{
    if (color == CheckerColor::NONE)
        return CheckerColor::NONE;
    return color == CheckerColor::WHITE ? CheckerColor::BLACK : CheckerColor::WHITE;
}

CheckerType Checker::getType()
{
    return this->type;
}
