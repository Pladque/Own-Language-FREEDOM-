#include "../Headers/Lexer.h"
#include <string>
#include <iostream>

/////////////////////////////////////////////
////                LEXER               ////
///////////////////////////////////////////



void Lexer::InitializeSkipSymbolsHashMap()
{
	this->SkipSymbols[' '] = true;
	this->SkipSymbols['\t'] = true;
	this->SkipSymbols['\n'] = true;

}

void Lexer::InitializeOperationSymbolsHashMap()
{
	this->OperationSymbols["+"] = this->TT_PLUS;
	this->OperationSymbols["-"] = this->TT_MINUS;
	this->OperationSymbols["*"] = this->TT_MUL;
	this->OperationSymbols["/"] = this->TT_DIV;
	this->OperationSymbols["^"] = this->TT_POWER;
	this->OperationSymbols["%"] = this->TT_MOD;

	this->OperationSymbols["("] = this->TT_LPAREN;
	this->OperationSymbols[")"] = this->TT_RPAREN;

	this->OperationSymbols["!="] = this->TT_NOTEQ;

	this->OperationSymbols["="] = this->TT_EQ;

	this->OperationSymbols["=="] = this->TT_2EQ;

	this->OperationSymbols["==="] = this->TT_3EQ;

	this->OperationSymbols["~~"] = this->TT_STREQ;

	this->OperationSymbols["<"] = this->TT_LESSEQ;
	this->OperationSymbols["<="] = this->TT_LESS;
	this->OperationSymbols[">"] = this->TT_MORE;
	this->OperationSymbols[">="] = this->TT_MOREEQ;
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

void Lexer::InitializeKeyWordsHashMap()
{
	this->KeyWords["var"] = this->TT_NEWVAR;

	this->KeyWords["while"] = this->TT_LOOP;
	this->KeyWords["stop"] = this->TT_LOOPSTOP;
	this->KeyWords["stopif"] = this->TT_IFSTOP;

	this->KeyWords["if"] = this->TT_IF;

	this->KeyWords[";"] = this->TT_NEWLN;

	this->KeyWords["//"] = this->TT_LONGCOMMENT;
	this->KeyWords["'"] = this->TT_COMMENT;
	//this->KeyWords["\n"] = this->TT_NEWLN;
}

Lexer::Lexer(std::string text, std::string fn)
{
	// inits //
	this->InitializeSkipSymbolsHashMap();
	this->InitializeOperationSymbolsHashMap();
	this->InitializeDigidsHashMap();
	this->InitializeKeyWordsHashMap();

	// Setting properties //
	this->text = text;
	this->fn = fn;
	this->pos = Position(0, 0, 0, fn, text);
	this->curr_char = this->pos.idx < this->text.length() ? this->text[0] : NULL;
}

// moves input reader forward by 1
void Lexer::advance()
{
	this->pos.advance(this->curr_char);
	this->curr_char = this->pos.idx < this->text.size() ? this->text[this->pos.idx] : NULL;
}

// makes queue of tokens from text input
std::string Lexer::ReadKeyWord()
{
	std::string keywordTemp = "";
	while (!SkipSymbols[this->curr_char] && this->curr_char != 0)
	{
		//if short comment sign, then skip rest of the word
		std::string temp;
		temp.insert(0,1,this->curr_char);
		if (KeyWords.count(temp) > 0 && KeyWords[temp] == this->TT_COMMENT)
			while (!SkipSymbols[this->curr_char] && this->curr_char != 0)
			{
				this->advance();
			}
		else
		{
			keywordTemp += this->curr_char;
			this->advance();
		}

		//added this, to allow make varaibles etc with white spaces
		if (this->curr_char == ' ')
		{
			this->advance();
			//if after white space there is another space, then break, if not then add space to keywordTemp
			if (this->curr_char == ' ')
				break;
			else
				keywordTemp += ' ';
		}
	}

	return keywordTemp;
}

std::deque < Token > Lexer::make_tokens()
{
	std::deque < Token > Tokens;

	while (this->curr_char != NULL)
	{
		if (this->SkipSymbols[this->curr_char])
		{
			this->advance();
		}
		else if (Digids[this->curr_char] == true)
		{
			Tokens.push_back(Token(make_number()));
		}
		else if (this->curr_char == '\n' || this->curr_char == ';')
		{
			Tokens.push_back(Token(this->TT_NEWLN, "None"));
			this->advance();
		}
		//reading operators that are longer than one char:
		else
		{
			std::string keywordTemp = ReadKeyWord();

			if (OperationSymbols.count(keywordTemp) > 0)
			{
				Tokens.push_back(Token(OperationSymbols[keywordTemp]));
				this->advance();

				if (Tokens[Tokens.size() - 1].Type == this->TT_3EQ
					&& Tokens.size() >= 2 && Tokens[Tokens.size() - 2].Type != TT_NEWLN)
				{
					std::string symToRedefine = "";
					bool itsOpSymb = false;
					for (auto const& x : this->GetOpSymb())
					{
						if (x.second == Tokens[Tokens.size() - 2].Type)
						{
							symToRedefine = x.first;
							itsOpSymb = true;
							break;
						}
					}
					if (symToRedefine == "")
						for (auto const& x : this->GetKeyWords())
						{
							if (x.second == Tokens[Tokens.size() - 2].Type)
							{
								symToRedefine = x.first;
								break;
							}
						}

					while (this->curr_char == ' ')
						this->advance();

					std::string newKewWord = ReadKeyWord();

					if (itsOpSymb)
					{
						this->OperationSymbols[newKewWord] = this->OperationSymbols[symToRedefine];
						this->OperationSymbols.erase(symToRedefine);
					}
					else
					{
						this->KeyWords[newKewWord] = this->KeyWords[symToRedefine];
						this->KeyWords.erase(symToRedefine);
					}


				}

			}
			else if (KeyWords.count(keywordTemp) > 0 && KeyWords[keywordTemp] == this->TT_NEWVAR)	//new varaible keyword
			{
				Tokens.push_back(Token(this->TT_NEWVAR));

				while (SkipSymbols[this->curr_char])
					this->advance();

				std::string varName = ReadKeyWord();

				if (OperationSymbols.count(varName) > 0)
				{
					if (OperationSymbols[varName] == this->TT_3EQ)
					{
						while (SkipSymbols[this->curr_char])
							this->advance();

						std::string newKeyWord = ReadKeyWord();;

						this->KeyWords[newKeyWord] = this->TT_NEWVAR;

						std::string symToRedefine;
						for (auto const& x : this->GetKeyWords())
						{
							if (x.second == this->TT_NEWVAR)
							{
								symToRedefine = x.first;
								break;
							}
						}


						this->KeyWords.erase(symToRedefine);

						Tokens.push_back(Token(this->TT_3EQ, "None"));	//pushing TT_3EQ bd I want to skip it in parser
					}
					else
					{

						this->Variables[varName] = true;
						Tokens.push_back(Token(TT_VARNAME, varName));

					}
				}
				else
				{
					this->Variables[varName] = true;
					Tokens.push_back(Token(TT_VARNAME, varName));

				}
			
			}
			else if (OperationSymbols.count(keywordTemp) > 0)
			{
				Tokens.push_back(Token(OperationSymbols[keywordTemp], "None"));
				this->advance();
			}
			else if (KeyWords.count(keywordTemp) > 0)
			{
				if(KeyWords[keywordTemp] == this->TT_LONGCOMMENT)
					while (true)
					{
						this->advance();
						keywordTemp = ReadKeyWord();

						if (KeyWords.count(keywordTemp) > 0)
							if (KeyWords[keywordTemp] == this->TT_NEWLN)
								break;
					}

				Tokens.push_back(Token(KeyWords[keywordTemp], "None"));
				this->advance();
			}
			//look for a keywordTemp in varaibles
			else if (this->Variables.count(keywordTemp) > 0)
			{
				Tokens.push_back(Token(TT_VARNAME, keywordTemp));
				this->advance();
			}
			else
			{
				Tokens.push_back(Token(TT_VOID, keywordTemp));
			}

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

std::unordered_map<std::string, std::string> Lexer::GetOpSymb()
{
	return this->OperationSymbols;
}

std::unordered_map<std::string, std::string> Lexer::GetKeyWords()
{
	return this->KeyWords;
}

void Lexer::SetOpSymbls(std::unordered_map<std::string, std::string> newOpSym)
{
	this->OperationSymbols = newOpSym;

}

void Lexer::SetKeyWords(std::unordered_map<std::string, std::string> newkeywords)
{
	this->KeyWords = newkeywords;
}