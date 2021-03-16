#include "BinOpNode.h"


BinOpNode::BinOpNode(NumberNode left_node, Token op_tok, NumberNode right_node)
{
	this->left_node = left_node;
	this->op_tok = op_tok;
	this->right_node = right_node;
}

std::ostream& operator<<(std::ostream& os, const BinOpNode& binOpNode)
{
	os << binOpNode.left_node << ' ' << binOpNode.op_tok << binOpNode.right_node;
	return os;
}