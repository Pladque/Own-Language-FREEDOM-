#include <iostream>


#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
	int idx;
	int ln;
	int col;
	std::string fn;
	std::string ftxt;

	Position(int idx, int ln, int col, std::string fn, std::string ftx) : idx(idx), ln(ln), col(col), fn(fn), ftxt(ftx) {};
	Position advance(char curr_char);
	Position copy();

	friend std::ostream& operator<<(std::ostream& os, const Position& token);
};

#endif