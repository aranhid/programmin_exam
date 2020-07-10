#pragma once

#include "Position.h"

class Step
{
public:
    Position from;
    Position to;
    Position beatedChecker;

    Step();

    Step(Position from, Position to, Position beated = Position(-1, -1)) :
        from(from), to(to), beatedChecker(beated) {};
};

