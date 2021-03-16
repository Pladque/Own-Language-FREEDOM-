#include "Token.h"


#pragma once
class NumberNode
{
public:
	Token tok;

	NumberNode(Token tok = Token());

	friend std::ostream& operator<<(std::ostream& os, const NumberNode& numNode);
};

