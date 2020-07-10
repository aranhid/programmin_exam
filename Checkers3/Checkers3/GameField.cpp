#include "GameField.h"

GameField::GameField()
{
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            data[y][x] = nullptr;
        }
    }
}

Checker GameField::get(int x, int y)
{
    return *data[y][x];
}

void GameField::set(int x, int y, Checker value)
{
    data[y][x] = new Checker(value);
}
