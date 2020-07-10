#include <iostream>
#include "Game.h"

void recursion(int depth, Game* game);

int main()
{
    Game *game = new Game("field.txt");
    game->printField();
    recursion(2, game);
}

void recursion(int depth, Game* game)
{
    if (depth == 0)
    {
        return;
    }
    else
    {
        vector<Step> allSteps = game->getAllPossiblePositions();
        for (Step step : allSteps)
        {
            cout << step.from.x << " " << step.from.y << " ";
            cout << step.to.x << " " << step.to.y << endl;
            Game* localgame = new Game(*game);
            localgame->makeStep(step);
            if (localgame->isTurnChanged)
            {
                recursion(depth - 1, localgame);
            }
        }
        
    }
}