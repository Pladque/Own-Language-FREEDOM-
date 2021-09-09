#include <unordered_map>
#include <deque>

#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include "Order.h"

#ifndef CORE_H
#define CORE_H

class Core
{
	std::unordered_map<std::string, Token> variables;
	std::deque < Token > TokensDeque;
	std::unordered_map<std::string, std::string> OperationSymbols;
	std::unordered_map<std::string, std::string> KeyWords;

public:
	/// SETS ///
	void SetOpSymbls(std::unordered_map<std::string, std::string> newOpSym);
	void SetKeyWords(std::unordered_map<std::string, std::string> newkeywords);
	void SetTokens(std::deque < Token > newTokens);
	void SetVarables(std::unordered_map<std::string, Token> newVariables);
	/// GETS ///
	std::unordered_map<std::string, std::string> GetOpSymbls();
	std::unordered_map<std::string, std::string> GetKeyWords();
	std::unordered_map<std::string, Token> GetVarables();
	std::deque < Token > GetTokens();
};

#endif