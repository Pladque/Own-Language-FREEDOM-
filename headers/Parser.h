#include <deque>
#include <string>		//stod
#include <sstream>		//stod
#include <unordered_map>
#include "Token.h"
#include "Order.h"
#include "Lexer.h"

#ifndef PARSER_H
#define PARSER_H

#pragma once
class Parser
{
protected:
	std::unordered_map<std::string, short> operatorsPriority;
	std::unordered_map<std::string, Token> Variables;

public:
	/// NA DOLE MAM JAK MG LEPIEJ ZADEKLAROWAC RZECZY:
	std::deque < Token > *tokens;
	Parser(std::deque < Token > *tokens);
	void SetVariables(std::unordered_map<std::string, Token> variables);
	std::unordered_map<std::string, Token> GetVariables();
	void InitializeOperatorsPriorityHashMap();
	std::deque < Order >  parse(std::deque < Token > tokens);
	Order interpretLine(std::deque < Token >* tokens, Lexer* lexer);
	bool LogicValueOf(std::deque < Token >* tokens, Lexer* lexer);

	const std::string  __DEFAULT_NUM_VALUE__ = "0";
	const std::string  __DEFAULT_STR_VALUE__ = "";
	
	Token curr_tok;
	const short __MAX_PRIOR__ = 4;
	int tok_idx;

	Token advance();

	double CalcExpr(short curr_prior, std::deque < Token > tokens);
	double SplitSubSetsAndDoMath(short curr_pior, std::deque < Token >* tokensLeft,
		Token* mathOperator, std::deque < Token >* tokensRight, double otherPart = 0);


};
#endif