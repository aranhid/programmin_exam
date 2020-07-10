#include "Man.h"
#include "GameField.h"

Man::Man(Position position, CheckerColor color)
{
    this->position = position;
    this->color = color;
}

Man::Man(const Checker& man)
{
    this->color = man.color;
    this->position = man.position;
}

vector<Step> Man::getPosiblePositions(GameField field)
{
    vector<Step> positions;

    for (int dY = -1; dY <= 1; dY += 2)
    {
        for (int dX = -1; dX <= 1; dX += 2)
        {
            if (position.x + dX >= 0 && position.x + dX < field.sizeX &&
                position.y + dY >= 0 && position.y + dY < field.sizeY)
            {
                if (field.data[position.y + dY][position.x + dX]->color == this->getEnemy())
                {
                    if (field.data[position.y + dY * 2][position.x + dX * 2]->getType() == CheckerType::NONE)
                    {
                        positions.push_back(Step(position, Position(position.x + dX * 2, position.y + dY * 2), Position(position.x + dX, position.y + dY)));
                    }
                }
            }
        }
    }

    if (positions.size() > 0)
        return positions;

    if (this->color == CheckerColor::WHITE)
    {
        int dY = 1;
        {
            for (int dX = -1; dX <= 1; dX += 2)
            {
                if (position.x + dX >= 0 && position.x + dX < field.sizeX &&
                    position.y + dY >= 0 && position.y + dY < field.sizeY)
                {
                    if (field.data[position.y + dY][position.x + dX]->getType() == CheckerType::NONE)
                    {
                        positions.push_back(Step(position, Position(position.x + dX, position.y + dY)));
                    }
                }
            }
        }
    }

    if (this->color == CheckerColor::BLACK)
    {
        int dY = -1;
        for (int dX = -1; dX <= 1; dX += 2)
        {
            if (position.x + dX >= 0 && position.x + dX < field.sizeX &&
                position.y + dY >= 0 && position.y + dY < field.sizeY)
            {
                if (field.data[position.y + dY][position.x + dX]->getType() == CheckerType::NONE)
                {
                    positions.push_back(Step(position, Position(position.x + dX, position.y + dY)));
                }
            }
        }
    }

    return positions;
}

CheckerType Man::getType()
{
    return this->type;
}
