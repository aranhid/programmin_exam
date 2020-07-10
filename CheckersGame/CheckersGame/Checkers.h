#pragma once

#include <fstream>
#include "Checker.h"

enum class GameStatus
{
	PLAYING,
	END
};

class Checkers
{
public:
	Checkers();
	Checkers(std::string path);

	void printGameField();
	bool move(string from, string to);
	CheckerColor getTurn();
	void setTurn(CheckerColor color);
	void changeTurn();

private:
	Checker gameField[9][9];
	GameStatus status;
	CheckerColor turn;

	void newGame();

};

