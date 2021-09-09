#include <iostream>
#include <queue>
#include "Token.h"
#include "Position.h"
#include <unordered_map>
#include <memory>

#ifndef LEXER_H
#define LEXER_H

class Lexer
{
public:
	///////////// TOKEN TITLES ///////////////
	const std::string TT_INT = "INT";
	const std::string TT_FLOAT = "FLOAT";

	const std::string TT_PLUS = "PLUS";
	const std::string TT_MINUS = "MINUS";
	const std::string TT_MUL = "MUL";
	const std::string TT_DIV = "DIV";
	const std::string TT_POWER= "POW";
	const std::string TT_MOD= "MOD";

	const std::string TT_LPAREN = "LPAREN";
	const std::string TT_RPAREN = "RPAREN";

	const std::string TT_NEWVAR = "NEWVAR";
	const std::string TT_NEWLN = "NEWLINE";
	const std::string TT_VARNAME= "VARNAME";

	const std::string TT_VOID= "VOID";

	const std::string TT_NOTEQ = "NOT_EQ";
	const std::string TT_EQ = "EQ";
	const std::string TT_2EQ = "DOUBLE_EQ";
	const std::string TT_3EQ = "TRIPLE_EQ";
	const std::string TT_STREQ = "STRING_EQ";
	const std::string TT_LESSEQ = "LESS_OR_EQ_THEN";
	const std::string TT_LESS= "LESS_THEN";
	const std::string TT_MORE= "MORE_THEN";
	const std::string TT_MOREEQ = "MORE_OR_EQ_THEN";

	const std::string TT_LOOP = "LOOP";
	const std::string TT_LOOPSTOP = "STOPLOOP";

	const std::string TT_IFSTOP = "IFLOOP";

	const std::string TT_IF = "IF";

	const std::string TT_EOF = "EOF";

	const std::string TT_COMMENT = "SHORT_COMM";
	const std::string TT_LONGCOMMENT = "LONG_COMM";
	////////////////////////////////////////////////////////

	Position pos = Position(0, 0, 0,"","");
	std::string fn;
	
	Lexer(std::string text, std::string fn);

	std::unordered_map<std::string, bool> Variables;

	std::string ReadKeyWord();
	std::deque < Token > make_tokens();
	std::unordered_map<std::string, std::string> GetOpSymb();
	std::unordered_map<std::string, std::string> GetKeyWords();
	
	void SetOpSymbls(std::unordered_map<std::string, std::string> newOpSym);
	void SetKeyWords(std::unordered_map<std::string, std::string> newkeywords);

private:
	char curr_char;

	std::unordered_map<std::string, std::string> OperationSymbols;
	std::unordered_map<std::string, std::string> KeyWords;
	std::unordered_map<char, bool> SkipSymbols;
	std::unordered_map<char, bool> Digids;
	std::string text;

	Token make_number();
	void advance();

	//INITS
	void InitializeOperationSymbolsHashMap();
	void InitializeSkipSymbolsHashMap();
	void InitializeDigidsHashMap();
	void InitializeKeyWordsHashMap();
};

#endif