#include "Token.h"
#include "NumberNode.h"

#pragma once
class BinOpNode
{
	NumberNode left_node;
	Token op_tok;
	NumberNode right_node;

	BinOpNode(NumberNode left_node, Token op_tok, NumberNode right_node);
	friend std::ostream& operator<<(std::ostream& os, const BinOpNode& token);

};

