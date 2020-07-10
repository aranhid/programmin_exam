#pragma once

#include "Checker.h"

class GameField;

class Man : public Checker
{
public:
    const CheckerType type = CheckerType::MAN;
    Man(Position position, CheckerColor color);
    Man(const Checker& man);

    virtual vector<Step> getPosiblePositions(GameField field) override;
    virtual CheckerType getType() override;
};

