#include <iostream>
#include "Game.h"

void recursion(int depth, Game* game);

CheckerColor colorForAnalize;

int main()
{
    colorForAnalize = CheckerColor::WHITE;
    Game *game = new Game("field.txt");
    game->printField();
    recursion(2, game);
}

void recursion(int depth, Game* game)
{
    if (depth == 0)
    {
        cout << " --- no luck " << endl;
        return;
    }
    else
    {
        vector<Step> allSteps = game->getAllPossiblePositions();
        for (Step step : allSteps)
        {
            Game* localgame = new Game(*game);

            cout << (localgame->turn == CheckerColor::WHITE ? "W " : "BL ");
            cout << step.from.x << " " << step.from.y << " ";
            cout << step.to.x << " " << step.to.y << endl;

            localgame->makeStep(step);
            if (localgame->getEnemyCount() == 0)
            {
                cout << " --- luck " << endl;
                return;
            }
            if (localgame->isTurnChanged)
            {
                localgame->changeTurn();
                if (localgame->turn == colorForAnalize)
                    recursion(depth - 1, localgame);
                else recursion(depth, localgame);
            }
            else recursion(depth, localgame);
            /*localgame->printField();
            if (localgame->isTurnChanged)
            {
                if(localgame->turn == colorForAnalize)
                    recursion(depth - 1, localgame);
            }
            else recursion(depth, localgame);*/
        }
        
    }
}