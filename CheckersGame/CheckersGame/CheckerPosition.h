#pragma once

#include <string>

using namespace std;

class CheckerPosition
{
public:
	CheckerPosition();
	CheckerPosition(int x, int y, bool novalidate = false);
	CheckerPosition(string position);

	void setPosition(int x, int y, bool novalidate = false);
	void setPosition(string position);
	int getX();
	int getY();
	string getPosition();
	CheckerPosition diff(CheckerPosition right);

	friend CheckerPosition operator-(CheckerPosition left, CheckerPosition right);

private:
	int x;
	int y;
	
	bool validatePosition(int x, int y);
};

class PositionException
{
public:
	PositionException(string error, int error_num)
		: _error(error), _error_num(error_num) {}

	const char* getError() { return _error.c_str(); }
	const int getErrorNumber() { return _error_num; }
private:
	string _error;
	int _error_num;
};