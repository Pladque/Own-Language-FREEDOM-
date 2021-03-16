#include "Position.h"

/////////////////////////////////////////////
////              POSITION              ////
///////////////////////////////////////////

Position::Position(int idx, int ln, int col, std::string fn, std::string ftx)
{
	this->idx = idx;
	this->ln = ln;
	this->col = col;
	this->fn = fn;
	this->ftxt = ftx;
}

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
	os << pos.idx;
	os << pos.ln;
	os << pos.col;
	return os;
}

Position Position::advance(char curr_char)
{
	if (curr_char == '\n')
	{
		this->ln++;
		this->col = 0;
	}
	else
	{
		this->col++;
	}

	this->idx++;

	return Position(this->idx, this->col, this->ln, this->fn, this->ftxt);

}

Position Position::copy()
{
	return Position(this->idx, this->ln, this->col, this->fn, this->ftxt);
}