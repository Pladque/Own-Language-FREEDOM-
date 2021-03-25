#include "Parser.h"

void Parser::InitializeOperatorsPriorityHashMap()
{
	this->operatorsPriority["PLUS"] = 1;
	this->operatorsPriority["MINUS"] = 1;
	this->operatorsPriority["MUL"] = 2;
	this->operatorsPriority["DIV"] = 2;
}

Parser::Parser(std::deque < Token* > tokens)
{
	this->tokens = tokens;
	this->tok_idx = 1;
	this->advance();
}

Token Parser::advance()
{
	this->tok_idx++;
	if (this->tok_idx < this->tokens.size())
	{
		this->curr_tok = *this->tokens.at(this->tok_idx);
	}

	return this->curr_tok;
}

double Parser::Split(short curr_prior, std::deque < Token* > tokens)
{
	int start = 0;
	std::deque < Token* > tokensSubsetLeft;
	std::deque < Token* > tokensSubsetRight = tokens;

	if (tokens.size() == 1) return tokens[0]->Value;

	while (curr_prior != this->PriorMax)
	{
		for (int i = 0; i < tokens.size(); i++)
		{
			if (tokens[i]->Value == "LPAREN")
			{
				while()
			}
			if (this->operatorsPriority[tokens[i]->Value] == curr_prior)
			{
				switch (tokens[i]->Type)
				{
				case "PLUS": return this->Split(curr_prior, tokensSubsetLeft) + this->Split(curr_prior, tokensSubsetRight);
					break;
				case "MINUS": return this->Split(curr_prior, tokensSubsetLeft) - this->Split(curr_prior, tokensSubsetRight);
					break;
				case "MUL": return this->Split(curr_prior, tokensSubsetLeft) * this->Split(curr_prior, tokensSubsetRight);
					break;
				case "DIV": return this->Split(curr_prior, tokensSubsetLeft) / this->Split(curr_prior, tokensSubsetRight);
					break;
				}
				
			}
			else
			{
				tokensSubsetRight.erase(i);
				tokensSubsetLeft.insert(tokens[i]);
			}
		}
		curr_prior++;
	}
}