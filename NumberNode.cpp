#include "NumberNode.h"


NumberNode::NumberNode(Token tok)
{
	this->tok = tok;
}

std::ostream& operator<<(std::ostream& os, const NumberNode& numNode)
{
	if (numNode.tok.Value != "None") os << numNode.tok.Type + ':' + numNode.tok.Value;
	else os << numNode.tok.Type;
	return os;
}