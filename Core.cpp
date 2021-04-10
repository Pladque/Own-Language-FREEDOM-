#include "Core.h"

void Core::SetOpSymbls(std::unordered_map<std::string, std::string> newOpSym)
{
	this->OperationSymbols = newOpSym;

}

void Core::SetKeyWords(std::unordered_map<std::string, std::string> newkeywords)
{
	this->KeyWords = newkeywords;
}

std::unordered_map<std::string, std::string> Core::GetOpSymbls()
{
	return this->OperationSymbols;
}

std::unordered_map<std::string, std::string> Core::GetKeyWords()
{
	return this->KeyWords;
}

void Core::SetVarables(std::unordered_map<std::string, Token> newVariables)
{
	this->variables = newVariables;
}

std::unordered_map<std::string, Token> Core::GetVarables()
{
	return this->variables;
}

void Core::SetTokens(std::deque < Token > newTokens)
{
	this->TokensDeque = newTokens;
}

std::deque < Token > Core::GetTokens()
{
	return this->TokensDeque;
}