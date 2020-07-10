#pragma once

#include "Checker.h"

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 8

class GameField
{
public:
    Checker *data[FIELD_HEIGHT][FIELD_WIDTH];
    int sizeX = FIELD_WIDTH;
    int sizeY = FIELD_HEIGHT;

    GameField();

    Checker get(int x, int y);
    void set(int x, int y, Checker value);
};

