#include "Position.h"

/////////////////////////////////////////////
////              POSITION              ////
///////////////////////////////////////////

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