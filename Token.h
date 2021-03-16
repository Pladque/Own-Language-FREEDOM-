#include <iostream>

#ifndef TOKEN_H // include guard
#define TOKEN_H
#pragma once
class Token
{
private:
public:
	std::string Type;
	std::string Value;
	friend std::ostream& operator<<(std::ostream& os, const Token& token);
	Token(std::string Token_Type, std::string Token_value = "None");
};

#endif 