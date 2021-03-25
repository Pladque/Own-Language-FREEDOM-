#include <deque>
#include <unordered_map>
#include "Token.h"

#pragma once
class Parser
{
protected:
	std::unordered_map<std::string, short> operatorsPriority;

public:
	short PriorMax = 2;
	std::deque < Token* > tokens;
	int tok_idx;
	Token curr_tok;
	Parser(std::deque < Token* > tokens);
	void Parser::InitializeOperatorsPriorityHashMap();
	Token advance();

	double Split(short curr_prior = 1, std::deque < Token* > tokens = this->tokens);

	void factor();
	void term();
	void expr();
};

