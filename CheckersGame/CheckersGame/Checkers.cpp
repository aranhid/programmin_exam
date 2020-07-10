#include "Checkers.h"

Checkers::Checkers()
{
	newGame();
}

Checkers::Checkers(std::string path)
{
	status = GameStatus::PLAYING;
	turn = CheckerColor::WHITE;
	ifstream inputFile(path);
	try
	{
		for (int y = 8; y >= 1; y--)
		{
			for (int x = 1; x <= 8; x++)
			{
				char temp = 0;
				inputFile >> temp;
				switch (temp)
				{
				case '_':
					gameField[y][x] = Checker(x, y, CheckerColor::NONE, CheckerStatus::NONE);
					break;
				case '*':
					gameField[y][x] = Checker(x, y, CheckerColor::BLACK, CheckerStatus::NORMAL);
					break;
				case 'o':
					gameField[y][x] = Checker(x, y, CheckerColor::WHITE, CheckerStatus::NORMAL);
					break;
				}
			}
		}
	}
	catch (PositionException& exception)
	{
		cout << "Error! " << exception.getError() << endl;
		exit(exception.getErrorNumber());
	}
}

void Checkers::printGameField()
{
	for (int y = 8; y >= 1; y--)
	{
		cout << y << "|";
		for (int x = 1; x <= 8; x++)
		{
			switch (gameField[y][x].getColor())
			{
			case CheckerColor::BLACK:
				cout << "*";
				break;
			case CheckerColor::WHITE:
				cout << "o";
				break;
			case CheckerColor::NONE:
				cout << "_";
				break;
			}
			cout << " ";
		}
		cout << endl;
	}
	cout << "  ";
	for (int x = 1; x <= 8; x++)
	{
		char temp = x + 64;
		cout << temp << " ";
	}
	cout << endl;
}

bool Checkers::move(string from, string to)
{
	try {
		CheckerPosition posFrom(from);
		CheckerPosition posTo(to);

		Checker takenChecker = gameField[posFrom.getY()][posFrom.getX()];
		Checker targetChecker = gameField[posTo.getY()][posTo.getX()];

		if (turn == takenChecker.getColor())
		{
			if (targetChecker.getStatus() == CheckerStatus::NONE)
			{
				CheckerPosition diff = posTo.diff(posFrom);

				if (takenChecker.getStatus() == CheckerStatus::NORMAL)
				{
					if (abs(diff.getX()) == 1 && abs(diff.getY()) == 1)
					{
						if (takenChecker.getColor() == CheckerColor::WHITE)
						{
							if (diff.getY() < 0)
								throw PositionException("No way!", -3);
						}

						if (takenChecker.getColor() == CheckerColor::BLACK)
						{
							if (diff.getY() > 0)
								throw PositionException("No way!", -3);
						}

						takenChecker.setPosition(to);
						gameField[posTo.getY()][posTo.getX()] = takenChecker;

						targetChecker.setPosition(from);
						gameField[posFrom.getY()][posFrom.getX()] = targetChecker;

						return true;
					}

					if (abs(diff.getX()) == 2 && abs(diff.getY()) == 2)
					{
						int enemyX = posFrom.getX() + diff.getX() / 2;
						int enemyY = posFrom.getY() + diff.getY() / 2;
						Checker enemy = gameField[enemyY][enemyX];
						if (enemy.getColor() != CheckerColor::NONE && enemy.getColor() != turn)
						{
							takenChecker.setPosition(to);
							gameField[posTo.getY()][posTo.getX()] = takenChecker;

							targetChecker.setPosition(from);
							gameField[posFrom.getY()][posFrom.getX()] = targetChecker;

							enemy.setColor(CheckerColor::NONE);
							enemy.setStatus(CheckerStatus::NONE);
							gameField[enemyY][enemyX] = enemy;

							return true;
						}
					}

					throw PositionException("Too long way!", -4);
				}
			}
			else throw PositionException("Not empty cell!", -2);
			return true;
		}
		else
		{
			cout << "Wrong color!" << endl;
			return false;
		}
	}
	catch (PositionException& exception)
	{
		cout << "Error! " << exception.getError() << endl;
		return false;
	}
}

CheckerColor Checkers::getTurn()
{
	return this->turn;
}

void Checkers::setTurn(CheckerColor color)
{
	this->turn = color;
}

void Checkers::changeTurn()
{
	switch (getTurn())
	{
	case CheckerColor::WHITE:
		setTurn(CheckerColor::BLACK);
		break;
	case CheckerColor::BLACK:
		setTurn(CheckerColor::WHITE);
		break;
	}
}

void Checkers::newGame()
{
	status = GameStatus::PLAYING;
	turn = CheckerColor::WHITE;

	for (int y = 1; y <= 8; y++)
	{
		for (int x = 1; x <= 8; x ++)
		{
			gameField[y][x] = Checker(x, y, CheckerColor::NONE, CheckerStatus::NONE);
		}
	}

	for (int y = 1; y <= 3; y++)
	{
		if (y % 2 == 1)
		{
			for (int x = 1; x <= 8; x+=2)
			{
				string position = "";
				position += (y + 48);
				position += (x + 64);
				gameField[y][x] = Checker(position, CheckerColor::WHITE, CheckerStatus::NORMAL);
			}
		}
		else
		{
			for (int x = 2; x <= 8; x += 2)
			{
				string position = "";
				position += (y + 48);
				position += (x + 64);
				gameField[y][x] = Checker(position, CheckerColor::WHITE, CheckerStatus::NORMAL);
			}
		}
	}

	for (int i = 6; i <= 8; i++)
	{
		if (i % 2 == 1)
		{
			for (int j = 1; j <= 8; j += 2)
			{
				string position = "";
				position += (i + 48);
				position += (j + 64);
				gameField[i][j] = Checker(position, CheckerColor::BLACK, CheckerStatus::NORMAL);
			}
		}
		else
		{
			for (int j = 2; j <= 8; j += 2)
			{
				string position = "";
				position += (i + 48);
				position += (j + 64);
				gameField[i][j] = Checker(position, CheckerColor::BLACK, CheckerStatus::NORMAL);
			}
		}
	}
}
