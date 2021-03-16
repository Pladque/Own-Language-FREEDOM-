#include "Parser.h"

Parser::Parser(std::deque < Token* > tokens)
{
	this->tokens = tokens;
	this->tok_idx = 1;
	this->advance();
}

Token Parser::advance()
{
	this->tok_idx++;
	if (this->tok_idx < this->tokens.size())
	{
		this->curr_tok = *this->tokens.at(this->tok_idx);
	}

	return this->curr_tok;
}