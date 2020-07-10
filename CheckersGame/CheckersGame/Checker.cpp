#include "Checker.h"

Checker::Checker()
{
	position = CheckerPosition(0, 0);
	color = CheckerColor::NONE;
	status = CheckerStatus::NONE;
}

Checker::Checker(std::string position, CheckerColor color, CheckerStatus status)
{
	setPosition(position);
	this->color = color;
	this->status = status;
}

Checker::Checker(int x, int y, CheckerColor color, CheckerStatus status)
{
	bool novalidate = color == CheckerColor::NONE ? true : false;
	CheckerPosition pos(x, y, novalidate);
	this->color = color;
	this->status = status;
}

void Checker::setPosition(std::string position)
{
	try
	{
		CheckerPosition pos(position);
		this->position = pos;
	}
	catch (PositionException& except)
	{
		cout << "ERROR! " << except.getError() << endl;
		exit(except.getErrorNumber());
	}
}

void Checker::setStatus(CheckerStatus status)
{
	this->status = status;
}

void Checker::setColor(CheckerColor color)
{
	this->color = color;
}

CheckerColor Checker::getColor()
{
	return this->color;
}

CheckerStatus Checker::getStatus()
{
	return this->status;
}
