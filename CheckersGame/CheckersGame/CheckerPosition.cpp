#include "CheckerPosition.h"

CheckerPosition::CheckerPosition()
{
	this->x = 0;
	this->y = 0;
}

CheckerPosition::CheckerPosition(int x, int y, bool novalidate)
{
	setPosition(x, y, novalidate);
}

CheckerPosition::CheckerPosition(string position)
{
	setPosition(position);
}

void CheckerPosition::setPosition(int x, int y, bool novalidate)
{
	if (validatePosition(x, y) || novalidate)
	{
		this->x = x;
		this->y = y;
	}
	else
		throw PositionException("Wrong position!", -1);
}

void CheckerPosition::setPosition(string position)
{
	int y = position[0] - 48;
	int x = position[1] - 64;
	setPosition(x, y);
}

int CheckerPosition::getX()
{
	return this->x;
}

int CheckerPosition::getY()
{
	return this->y;
}

string CheckerPosition::getPosition()
{
	return string();
}

CheckerPosition CheckerPosition::diff(CheckerPosition right)
{
	return CheckerPosition(this->getX() - right.getX(), this->getY() - right.getY(), true);
}

bool CheckerPosition::validatePosition(int x, int y)
{
	if (x % 2 == 1 && y % 2 == 1)
		return true;
	if (x % 2 == 0 && y % 2 == 0)
		return true;

	return false;
}

CheckerPosition operator-(CheckerPosition left, CheckerPosition right)
{
	CheckerPosition temp(left.getX() - right.getX(), left.getY() - right.getY());
	return temp;
}
