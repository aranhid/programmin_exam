#pragma once
#include <string>
#include <iostream>
#include "CheckerPosition.h"

using namespace std;

enum class CheckerColor
{
	WHITE,
	BLACK,
	NONE
};

enum class CheckerStatus
{
	NONE,
	NORMAL,
	DAMKA
};

class Checker
{
public:
	Checker();
	Checker(std::string position, CheckerColor color, CheckerStatus status);
	Checker(int x, int y, CheckerColor color, CheckerStatus status);

	void setPosition(std::string position);
	void setStatus(CheckerStatus status);
	void setColor(CheckerColor color);

	CheckerColor getColor();
	CheckerStatus getStatus();


private:
	CheckerPosition position;
	CheckerColor color;
	CheckerStatus status;
};

