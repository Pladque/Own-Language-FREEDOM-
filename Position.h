#include <iostream>

#ifndef POSITION_H // include guard
#define POSITION_H
#pragma once
#pragma once
class Position
{
public:
	// public variables //
	int idx;
	int ln;
	int col;
	std::string fn;
	std::string ftxt;

	// public methods //
	Position(int idx, int ln, int col, std::string fn, std::string ftx);
	Position advance(char curr_char);
	Position copy();

	// overwrited "<<" operator
	friend std::ostream& operator<<(std::ostream& os, const Position& token);
};

#endif