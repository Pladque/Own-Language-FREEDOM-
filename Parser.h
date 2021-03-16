#include <deque>
#include "Token.h"

#pragma once
class Parser
{
public:
	std::deque < Token* > tokens;
	int tok_idx;
	Token curr_tok;
	Parser(std::deque < Token* > tokens);
	Token advance();

	void factor();
	void term();
	void expr();
};

