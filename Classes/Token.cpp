#include "../Headers/Token.h"
#include <iostream>
/////////////////////////////////////////////
////                TOKEN               ////
///////////////////////////////////////////

Token::Token(std::string Token_Type, std::string Token_value)
{
	this->Type = Token_Type;
	this->Value = Token_value;
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
	if (token.Value != "None") os << token.Type + ':' + token.Value;
	else os << token.Type;
	return os;
}
