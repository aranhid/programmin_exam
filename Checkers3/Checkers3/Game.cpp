#include "Game.h"

Game::Game(string path)
{
    ifstream inputStream(path);
    for (int y = FIELD_HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            char inputChar = 0;
            inputStream >> inputChar;
            switch (inputChar)
            {
            case '~':
                this->field.data[y][x] = new Checker(Position(x, y));
                break;
            case '#':
                this->field.data[y][x] = new Man(Position(x, y), CheckerColor::BLACK);
                this->blackCount++;
                break;
            case 'o':
                this->field.data[y][x] = new Man(Position(x, y), CheckerColor::WHITE);
                this->whiteCount++;
                break;
            }
        }
    }
}

Game::Game(const Game& game)
{
    this->turn = game.turn;
    this->blackCount = game.blackCount;
    this->whiteCount = game.whiteCount;
    this->currentPos = game.currentPos;

    for (int y = 0; y < game.field.sizeY; y++)
    {
        for (int x = 0; x < game.field.sizeX; x++)
        {
            switch (game.field.data[y][x]->type)
            {
            case CheckerType::NONE:
                this->field.data[y][x] = new Checker(*game.field.data[y][x]);
                break;
            case CheckerType::MAN:
                this->field.data[y][x] = new Man(*game.field.data[y][x]);
                break;
            case CheckerType::KING:
                break;
            }
        }
    }
}

void Game::printField()
{
    cout << (this->turn == CheckerColor::WHITE ? "White turn" : "Black turn") << endl;
    for (int y = FIELD_HEIGHT - 1; y >= 0; y--)
    {
        cout << y + 1 << "|";
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            switch (this->field.data[y][x]->color)
            {
            case CheckerColor::NONE:
                cout << "~" << " ";
                break;
            case CheckerColor::BLACK:
                cout << "#" << " ";
                break;
            case CheckerColor::WHITE:
                cout << "o" << " ";
                break;
            }
        }
        cout << endl;
    }
    cout << "  ";
    for (int x = 0; x < FIELD_WIDTH; x++)
    {
        char temp = x + 65;
        cout << temp << " ";
    }
    cout << endl;
}

void Game::changeTurn()
{
    this->turn = this->turn == CheckerColor::WHITE ? CheckerColor::BLACK : CheckerColor::WHITE;
}

vector<Step> Game::getAllPossiblePositions()
{
    bool priority = false;
    vector<Step> allPositions;

    if (this->currentPos.x >= 0)
    {
        allPositions = this->field.data[currentPos.y][currentPos.x]->getPosiblePositions(this->field);
    }
    else
    {
        for (int y = 0; y < field.sizeY; y++)
        {
            for (int x = 0; x < field.sizeX; x++)
            {
                if (this->turn == this->field.data[y][x]->color)
                {
                    vector<Step> onePositions = this->field.data[y][x]->getPosiblePositions(this->field);

                    for (Step position : onePositions)
                    {
                        if (position.beatedChecker.x >= 0)
                            priority = true;
                        allPositions.push_back(position);
                    }
                }
            }
        }
    }

    if (priority)
    {
        for (int i = 0; i < allPositions.size(); i++)
        {
            if (allPositions[i].beatedChecker.x < 0)
            {
                allPositions.erase(allPositions.begin() + i);
                i = -1;
            }
        }
    }

    return allPositions;
}

void Game::makeStep(Step step)
{
    Checker *takenChecker = this->field.data[step.from.y][step.from.x];
    takenChecker->position = step.to;
    delete this->field.data[step.to.y][step.to.x];
    field.data[step.to.y][step.to.x] = takenChecker;
    this->field.data[step.from.y][step.from.x] = new Checker(Position(step.from.x, step.from.y));

    if (step.beatedChecker.x >= 0)
    {
        delete this->field.data[step.beatedChecker.y][step.beatedChecker.x];
        this->field.data[step.beatedChecker.y][step.beatedChecker.x] = new Checker(Position(step.beatedChecker.x, step.beatedChecker.y));
        this->turn == CheckerColor::WHITE ? blackCount-- : whiteCount--;
    }

    bool nextTurn = true;

    vector<Step> check = takenChecker->getPosiblePositions(this->field);

    for (Step step : check)
    {
        if (step.beatedChecker.x >= 0)
        {
            nextTurn = false;
            currentPos = takenChecker->position;
        }
    }

    if (nextTurn)
    {
        this->changeTurn();
        this->isTurnChanged = true;
        currentPos = Position();
    }
    else this->isTurnChanged = false;
}
