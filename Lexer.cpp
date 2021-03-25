#include "Lexer.h"
#include "Error.h"

/////////////////////////////////////////////
////                LEXER               ////
///////////////////////////////////////////


void Lexer::InitializeSkipSymbolsHashMap()
{
	this -> SkipSymbols[' '] = true;
	this -> SkipSymbols['\t'] = true;
}

void Lexer::InitializeOperationSymbolsHashMap()
{
	this->OperationSymbols['+'] = this->TT_PLUS;
	this->OperationSymbols['-'] = this->TT_MINUS;
	this->OperationSymbols['*'] = this->TT_MUL;
	this->OperationSymbols['/'] = this->TT_DIV;

	this->OperationSymbols['('] = this->TT_LPAREN;
	this->OperationSymbols[')'] = this->TT_RPAREN;
}

void Lexer::InitializeDigidsHashMap()
{
	this->Digids['0'] = true;
	this->Digids['1'] = true;
	this->Digids['2'] = true;
	this->Digids['3'] = true;
	this->Digids['4'] = true;
	this->Digids['5'] = true;
	this->Digids['6'] = true;
	this->Digids['7'] = true;
	this->Digids['8'] = true;
	this->Digids['9'] = true;
}

Lexer::Lexer(std::string text, std::string fn)
{
	// inits //
	this->InitializeSkipSymbolsHashMap();
	this->InitializeOperationSymbolsHashMap();
	this->InitializeDigidsHashMap();

	// Setting properties //
	this->text = text;
	this->fn = fn;
	this->pos = Position(0, 0, 0, fn,text);
	this->curr_char = this->pos.idx < this->text.length() ? this->text[0] : NULL;
}

// moves input reader forward by 1
void Lexer::advance()
{
	this->pos.advance(this->curr_char);
	this->curr_char = this->pos.idx < this->text.size() ? this->text[this->pos.idx] : NULL;
}

// makes queue of tokens from text input
std::queue < Token > Lexer::make_tokens()
{
	std::queue < Token > Tokens;

	while (this->curr_char != NULL)
	{
		if (this->SkipSymbols[this->curr_char])
		{
			this->advance();
		}
		else if (Digids[this->curr_char]==true)
		{
			Tokens.push(Token(make_number()));
		}
		else if (OperationSymbols.count(this->curr_char) > 0 )
		{
			Tokens.push(Token(OperationSymbols[this->curr_char]));
			this->advance();
		}
		else if (this->curr_char == '\n')
		{
			this->advance();
		}
		else
		{
			//TODO ERRORS!!
			//throw error
			//throw new Error("Illegal character", "Your input is not valid: " + this->curr_char);
			std::queue < Token > Empty;
			std::cout << "Illegal character Your input is not valid: "<< this->curr_char << std::endl;
			return Empty;
		}
	};
	return Tokens;
}

Token Lexer::make_number()
{
	std::string num_str = "";
	bool dot_appeared = false;

	while (this->curr_char != NULL && (Digids[this->curr_char] || this->curr_char == '.'))
	{
		if (this->curr_char == '.')
		{
			if (dot_appeared) break;
			dot_appeared = true;
		}
		num_str += this->curr_char;

		this->advance();
	}
	return dot_appeared ? Token(TT_FLOAT, num_str) : Token(TT_INT, num_str);
}