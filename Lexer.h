#include <iostream>
#include <queue>
#include "Token.h"
#include "Position.h"
#include <unordered_map>

#ifndef LEXER_H // include guard
#define LEXER_H
#pragma once
class Lexer
{
public:
	// TOKEN TITLES //
	const std::string TT_INT = "TT_INT";
	const std::string TT_FLOAT = "FLOAT";
	const std::string TT_PLUS = "PLUS";
	const std::string TT_MINUS = "MINUS";
	const std::string TT_MUL = "MUL";
	const std::string TT_DIV = "DIV";
	const std::string TT_LPAREN = "LPAREN";
	const std::string TT_RPAREN = "RPAREN ";

	// public variables //
	Position pos = Position(0, 0, 0,"","");
	std::string fn;
	
	// public methods //
	Lexer(std::string text, std::string fn);
	std::queue < Token > make_tokens();
private:
	// private variables //
	std::string text;
	char curr_char;
	std::unordered_map<char, bool> SkipSymbols;
	std::unordered_map<char, bool> Digids;
	std::unordered_map<char, std::string> OperationSymbols;

	// private methods //
	void advance();
	void InitializeOperationSymbolsHashMap();
	void InitializeSkipSymbolsHashMap();
	void InitializeDigidsHashMap();
	Token make_number();
};

#endif