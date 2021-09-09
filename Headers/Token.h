#include <iostream>

#ifndef TOKEN_H 
#define TOKEN_H

class Token
{
private:
public:
	std::string Type;
	std::string Value;
	friend std::ostream& operator<<(std::ostream& os, const Token& token);
	Token(std::string Token_Type = "None", std::string Token_value = "None");
};

#endif 