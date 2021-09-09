#include "../Headers/Parser.h"

#include <math.h>
#include <stack>
#include<string>


bool is_number(const std::string s)
{
	std::string copied_str = "";
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] != '.')
			copied_str += s[i];
	}
	return !copied_str.empty() && std::find_if(copied_str.begin(),
		copied_str.end(), [](unsigned char c) { return !std::isdigit(c); }) == copied_str.end();
}



void Parser::InitializeOperatorsPriorityHashMap()
{
	this->operatorsPriority["PLUS"] = 1;
	this->operatorsPriority["MINUS"] = 1;
	this->operatorsPriority["MOD"] = 2;
	this->operatorsPriority["MUL"] = 3;
	this->operatorsPriority["DIV"] = 3;
	this->operatorsPriority["POW"] = 4;
}

Parser::Parser(std::deque < Token >* tokens)
{
	InitializeOperatorsPriorityHashMap();
	this->tokens = tokens;
	this->tok_idx = 1;
}

void Parser::SetVariables(std::unordered_map<std::string, Token> variables)
{
	this->Variables = variables;
}

std::unordered_map<std::string, Token> Parser::GetVariables()
{
	return this->Variables;
}

Token Parser::advance()
{
	this->tok_idx++;
	if (this->tok_idx < this->tokens->size())
	{
		this->curr_tok = this->tokens->at(this->tok_idx);
	}
	return this->curr_tok;
}

double Parser::SplitSubSetsAndDoMath(short curr_prior, std::deque < Token >* tokensLeft,
	Token* mathOperator, std::deque < Token >* tokensRight, double otherPart)
{
	if (mathOperator->Type == "PLUS")
		return this->CalcExpr(curr_prior, *tokensLeft) + this->CalcExpr(curr_prior, *tokensRight);
	else if (mathOperator->Type == "MINUS")
		return this->CalcExpr(curr_prior, *tokensLeft) - this->CalcExpr(curr_prior, *tokensRight);
	else if (mathOperator->Type == "MUL")
		return this->CalcExpr(curr_prior, *tokensLeft) * this->CalcExpr(curr_prior, *tokensRight);
	else if (mathOperator->Type == "DIV")
		return this->CalcExpr(curr_prior, *tokensLeft) / this->CalcExpr(curr_prior, *tokensRight);
	else if (mathOperator->Type == "POW")
		return pow(this->CalcExpr(curr_prior, *tokensLeft), this->CalcExpr(curr_prior, *tokensRight));
	else if (mathOperator->Type == "MOD")
	{
		int x1 = int(this->CalcExpr(curr_prior, *tokensLeft));
		int x2 = int(this->CalcExpr(curr_prior, *tokensRight));
		return int(this->CalcExpr(curr_prior, *tokensLeft)) % int(this->CalcExpr(curr_prior, *tokensRight));
	}

	return 0;
}

int SetSubTokensMiddleAndGetParanthesisBeginIndex(std::deque < Token > tokens, int curr_iterator, std::deque < Token >* tokensSubsetMiddle)
{
	short parathesisCounter = 0;
	int paranthesisBeginIndex;

	for (paranthesisBeginIndex = curr_iterator - 1; !(tokens[paranthesisBeginIndex].Type == "LPAREN" && parathesisCounter == 0);
		paranthesisBeginIndex--)
	{
		if (tokens[paranthesisBeginIndex].Type == "LPAREN")
			parathesisCounter++;
		else if (tokens[paranthesisBeginIndex].Type == "RPAREN")
			parathesisCounter--;

		if ((tokens[paranthesisBeginIndex].Type == "LPAREN" && parathesisCounter == 1) || paranthesisBeginIndex < 0)
			break;
		else
			tokensSubsetMiddle->push_front(tokens[paranthesisBeginIndex]);
	}

	return paranthesisBeginIndex;
}

//Returns value of logic tokens expresion
bool Parser::LogicValueOf(std::deque < Token >* tokens, Lexer* lexer)
{
	std::deque<std::deque < Token > > Expresions;	//deque of deque will allow me to use multiple comparision like 1==2==3
	std::stack<Token> operators;

	Expresions.push_back(std::deque < Token >());
	short iterator = 0;

	for (int i = 0; i < tokens->size(); i++)
	{
		//these are logic operators
		if (tokens->at(i).Type == lexer->TT_LESSEQ || tokens->at(i).Type == lexer->TT_LESS
			|| tokens->at(i).Type == lexer->TT_MORE || tokens->at(i).Type == lexer->TT_MOREEQ
			|| tokens->at(i).Type == lexer->TT_2EQ || tokens->at(i).Type == lexer->TT_NOTEQ)
		{
			iterator++;
			operators.push(tokens->at(i));
			Expresions.push_back(std::deque < Token >());
		}
		else
		{
			Expresions[iterator].push_back(tokens->at(i));
		}
	}

	bool check = true;
	while (operators.size() > 0 && iterator > 0)
	{
		Token temp = operators.top();
		if (temp.Type == lexer->TT_LESSEQ)
		{
			check = (CalcExpr(1, Expresions[iterator - 1]) < CalcExpr(1, Expresions[iterator]));
		}
		else if (temp.Type == lexer->TT_LESS)
		{
			check = (CalcExpr(1, Expresions[iterator - 1]) <= CalcExpr(1, Expresions[iterator]));
		}
		else if (temp.Type == lexer->TT_MORE)
		{
			check = (CalcExpr(1, Expresions[iterator - 1]) > CalcExpr(1, Expresions[iterator]));
		}
		else if (temp.Type == lexer->TT_MOREEQ)
		{
			check = (CalcExpr(1, Expresions[iterator - 1]) >= CalcExpr(1, Expresions[iterator]));
		}
		else if (temp.Type == lexer->TT_2EQ)
		{
			check = (CalcExpr(1, Expresions[iterator - 1]) == CalcExpr(1, Expresions[iterator]));
		}
		else if (temp.Type == lexer->TT_NOTEQ)
		{
			check = (CalcExpr(1, Expresions[iterator - 1]) != CalcExpr(1, Expresions[iterator]));
		}

		if (!check)
			return false;
		iterator--;
	}

	return true;
}

Order Parser::interpretLine(std::deque < Token >* tokens, Lexer* lexer)
{
	Order order;
	if (tokens->size() == 0)
	{
		order.type = Order::Type::skip;
		return order;
	}

	Token startToken = tokens->front();

	for (int i = 0; i < tokens->size(); i++)
	{
		//if there is TT_3EQ then skip it, bc it is redefinition of keyword so lexer already took care of that
		if (tokens->at(i).Type == lexer->TT_3EQ)
		{
			order.type = Order::Type::skip;
			break;
		}
	}
	if (order.type != Order::Type::skip)
		if (startToken.Type == lexer->TT_FLOAT || startToken.Type == lexer->TT_INT || startToken.Type == lexer->TT_VARNAME)
		{
			if (tokens->size() >= 2 && (tokens->at(1).Type == lexer->TT_EQ || (tokens->at(1).Type == lexer->TT_STREQ) ))// if there changing value of already delcared value;
			{
				order.type = Order::Type::revalue;
				order.tokens = *tokens;
			}
			else if (tokens->size() >= 2)		//bc for only variable I want to print its value
			{
				//if there is operator, then it is term, if not, print
				bool foundInOperators = false;
				for (int i = 0; i < tokens->size(); i++)
				{
					for (auto const& x : lexer->GetOpSymb())
					{
						if (x.second == tokens->at(i).Type)
						{
							order.type = Order::Type::term;
							order.tokens = *tokens;
							return order;
						}
					}
				}
				order.type = Order::Type::print;
				order.tokens = *tokens;
			}
			else
			{
				if (is_number(tokens->at(0).Value))
					order.type = Order::Type::term;
				else
					order.type = Order::Type::text;
				order.tokens = *tokens;
			}
		}
		else if (startToken.Type == lexer->TT_NEWVAR)
		{
			order.type = Order::Type::declar;
			order.tokens = *tokens;
		}
		else if (startToken.Type == lexer->TT_LOOP)
		{
			order.type = Order::Type::loop_start;

			for (int i = 1; i < tokens->size(); i++)
			{
				order.tokens.push_back(tokens->at(i));
			}
		}
		else if (startToken.Type == lexer->TT_LOOPSTOP)
		{
			order.type = Order::Type::loop_stop;
		}
		else if (startToken.Type == lexer->TT_IF)
		{
			order.type = Order::Type::if_statement;

			for (int i = 1; i < tokens->size(); i++)
			{
				order.tokens.push_back(tokens->at(i));
			}
		}
		else if (startToken.Type == lexer->TT_IFSTOP)
		{
			order.type = Order::Type::if_stop;
		}
		else
		{
			order.type = Order::Type::print;

			for (int i = 0; i < tokens->size(); i++)
			{
				order.tokens.push_back(tokens->at(i));
			}
		}

	return order;
}

std::deque < Order > Parser::parse(std::deque < Token > tokens)
{
	std::deque < Token > subTokens;
	std::deque < Order > orders;
	Lexer lexer("", "");

	//creating orders
	for (int i = 0; i < tokens.size(); i++)
	{
		if (i < tokens.size() && tokens[i].Type != lexer.TT_NEWLN)
		{
			subTokens.push_back(tokens[i]);
		}
		else
		{
			orders.push_back(interpretLine(&subTokens, &lexer));
			subTokens.clear();
		}
	}

	//Executing orders:
	for (int i = 0; i < orders.size(); i++)
	{
		if (orders[i].type == Order::Type::term)
		{
			try
			{
				std::cout << CalcExpr(1, orders[i].tokens) << std::endl;
			}
			catch (int error)
			{
				switch (error)
				{
				case 301:
					std::cout << "You cant add strings and numbers!" << std::endl;
					break;
				case 101:
					std::cout << "Unexpected error, check yout input" << std::endl;
					break;
				}
				std::cout << "Error: " << error << std::endl;
			}

		}
		else if (orders[i].type == Order::Type::text)
		{
			for (int j = 0; j < orders[i].tokens.size(); j++)
			{
				std::cout << this->Variables[orders[i].tokens[j].Value].Value;
			}
			std::cout << std::endl;
		}
		else if (orders[i].type == Order::Type::print)
		{
			orders[i].printTokens(this->Variables);
		}
		else if (orders[i].type == Order::Type::if_statement)
		{
			if (!LogicValueOf(&orders[i].tokens, &lexer))
			{
				short ifsAnsStops = 1;

				while (ifsAnsStops != 0)
				{
					i++;
					if ((orders[i].type == Order::Type::if_statement))
						ifsAnsStops++;
					else if ((orders[i].type == Order::Type::if_stop))
						ifsAnsStops--;
				}
			}
		}
		else if (orders[i].type == Order::Type::revalue)
		{

			std::deque < Token > subTokensExpr;

			bool foundVoid = false;
			bool foundOperator = false;
			bool foundString = false;
			for (int j = 2; j < orders[i].tokens.size(); j++) //i = 3 bc i want start with token after =
			{
				subTokensExpr.push_back(orders[i].tokens.at(j));
				if (orders[i].tokens.at(j).Type == lexer.TT_VOID)
				{
					foundVoid = true;
				}
				else if (orders[i].tokens.at(j).Type == lexer.TT_VARNAME &&
					!is_number(this->Variables[orders[i].tokens.at(j).Value].Value))
				{
					foundString = true;
				}
				else
				{
					for (auto const& x : lexer.GetOpSymb())
					{
						if (x.second == orders[i].tokens.at(j).Type)
						{
							foundOperator = true;
							break;
						}
					}
				}
			}

			bool ifExpr = (!foundVoid || foundOperator) && !foundString;

			//if it is expresion, then call expresion
			if (ifExpr)
				this->Variables[orders[i].tokens.at(0).Value] = Token(orders[i].tokens.at(0).Value, std::to_string(this->CalcExpr(1, subTokensExpr)));
			//else convert that voids to number
			else //if(!foundString)
			{
				if (orders[i].tokens[1].Type == lexer.TT_EQ)
				{

					int newValue = 0;
					int pow = 1;

					//std::string tempTestingHowStringWillWork;
					for (int i = subTokensExpr.size() - 1; i >= 0; i--)
					{
						newValue += subTokensExpr[i].Value.length() * pow;
						pow *= 10;
						//tempTestingHowStringWillWork += subTokensExpr[i].Value;
					}
					this->Variables[orders[i].tokens.at(0).Value] = Token(orders[i].tokens.at(0).Value, std::to_string(newValue));
					//this->Variables[orders[i].tokens.at(1).Value] = Token(orders[i].tokens.at(1).Value, tempTestingHowStringWillWork);
				}
				else if (orders[i].tokens[1].Type == lexer.TT_STREQ)
				{
					std::string newValue;
					for (int i = 0; i < subTokensExpr.size(); i++)
					{
						if (subTokensExpr[i].Type != lexer.TT_VARNAME)
							newValue += subTokensExpr[i].Value + " ";
						else
							newValue += this->Variables[subTokensExpr[i].Value].Value + " ";
					}
					this->Variables[orders[i].tokens.at(0).Value] = Token(orders[i].tokens.at(0).Value, newValue);
				}
			}


		}
		else if (orders[i].type == Order::Type::declar)
		{
			if (orders[i].tokens.size() > 3)
			{
				std::deque < Token > subTokensExpr;

				bool foundVoid = false;
				bool foundOperator = false;
				bool foundString = false;
				for (int j = 3; j < orders[i].tokens.size(); j++) //i = 3 bc i want start with token after =
				{
					subTokensExpr.push_back(orders[i].tokens.at(j));
					if (orders[i].tokens.at(j).Type == lexer.TT_VOID)
					{
						foundVoid = true;
					}
					else if (orders[i].tokens.at(j).Type == lexer.TT_VARNAME &&
						!is_number(this->Variables[orders[i].tokens.at(j).Value].Value))
					{
						foundString = true;
					}
					else
					{
						for (auto const& x : lexer.GetOpSymb())
						{
							if (x.second == orders[i].tokens.at(j).Type)
							{
								foundOperator = true;
								break;
							}
						}
					}
				}

				bool ifExpr = (!foundVoid || foundOperator) && !foundString;

				//if it is expresion, then call expresion
				if (ifExpr)
					this->Variables[orders[i].tokens.at(1).Value] = Token(orders[i].tokens.at(1).Value, std::to_string(this->CalcExpr(1, subTokensExpr)));
				//else convert that voids to number
				else //if(!foundString)
				{
					if (orders[i].tokens[2].Type == lexer.TT_EQ)
					{

						int newValue = 0;
						int pow = 1;

						//std::string tempTestingHowStringWillWork;
						for (int i = subTokensExpr.size() - 1; i >= 0; i--)
						{
							newValue += subTokensExpr[i].Value.length() * pow;
							pow *= 10;
							//tempTestingHowStringWillWork += subTokensExpr[i].Value;
						}
						this->Variables[orders[i].tokens.at(1).Value] = Token(orders[i].tokens.at(1).Value, std::to_string(newValue));
						//this->Variables[orders[i].tokens.at(1).Value] = Token(orders[i].tokens.at(1).Value, tempTestingHowStringWillWork);
					}
					else if (orders[i].tokens[2].Type == lexer.TT_STREQ)
					{
						std::string newValue;
						for (int i = 0; i < subTokensExpr.size(); i++)
						{
							if (subTokensExpr[i].Type != lexer.TT_VARNAME)
								newValue += subTokensExpr[i].Value + " ";
							else
								newValue += this->Variables[subTokensExpr[i].Value].Value + " ";
						}
						this->Variables[orders[i].tokens.at(1).Value] = Token(orders[i].tokens.at(1).Value, newValue);
					}
				}

			}
			else if (orders[i].tokens[2].Type == lexer.TT_STREQ)		//for fe. "var  str  ~~ " I will give str __DEFAULT_STR_VALUE__
				this->Variables[orders[i].tokens.at(1).Value] = Token(orders[i].tokens.at(1).Value, __DEFAULT_STR_VALUE__);
			else
				this->Variables[orders[i].tokens.at(1).Value] = Token(orders[i].tokens.at(1).Value, __DEFAULT_NUM_VALUE__);

		}
		else if (orders[i].type == Order::Type::loop_start)
		{
			if (!LogicValueOf(&orders[i].tokens, &lexer))
			{
				short loopStartsAndStops = 1;

				while (loopStartsAndStops != 0)
				{
					i++;
					if ((orders[i].type == Order::Type::loop_start))
						loopStartsAndStops++;
					else if ((orders[i].type == Order::Type::loop_stop))
						loopStartsAndStops--;
				}
			}
		}
		else if (orders[i].type == Order::Type::loop_stop)
		{
			short loopStartsAndStops = -1;

			while (loopStartsAndStops != 0)
			{
				i--;
				if ((orders[i].type == Order::Type::loop_start))
					loopStartsAndStops++;
				else if ((orders[i].type == Order::Type::loop_stop))
					loopStartsAndStops--;
			}

			i--;
		}
	}
	return orders;
}

double Parser::CalcExpr(short curr_prior, std::deque < Token > tokens)
{
	//returning single value
	if (tokens.size() == 1)
	{
		Lexer lexer("", "");
		if (tokens.front().Type == lexer.TT_NEWVAR || tokens.front().Type == lexer.TT_VARNAME)
		{
			if (!is_number(this->Variables[tokens.front().Value].Value))
			{
				std::string XD = this->Variables[tokens.front().Value].Value;
				bool test = is_number("7.00");

				throw 301;
			}
			tokens.front() = this->Variables[tokens.front().Value];
		}
		else if (tokens.front().Type == lexer.TT_VOID)
		{
			tokens.front() = Token(lexer.TT_FLOAT, std::to_string(tokens.front().Value.length()));
		}

		return std::stod(tokens.front().Value);

	}
	else if (tokens.size() == 0)
		return 0;

	while (curr_prior <= this->__MAX_PRIOR__)
	{
		std::deque < Token > tokensSubsetLeft;
		std::deque < Token > tokensSubsetRight;
		Lexer lexer("", "");

		for (int i = tokens.size() - 1; i >= 0; i--)
		{
			if (tokens[i].Type == lexer.TT_NEWVAR || tokens[i].Type == lexer.TT_VARNAME)
			{
				tokens[i] = this->Variables[tokens[i].Value];
			}

			if (tokens[i].Type == "RPAREN")
			{
				std::deque < Token > tokensSubsetMiddle;

				//add if it is not and of tokens
				Token* tokenAfter = nullptr;
				if (i + 1 != tokens.size())
				{
					tokenAfter = &tokensSubsetRight[0];
				}

				int paranthesisBeginIndex = SetSubTokensMiddleAndGetParanthesisBeginIndex(tokens, i, &tokensSubsetMiddle);
				double middResult = CalcExpr(1, tokensSubsetMiddle);
				tokens.erase(tokens.begin() + paranthesisBeginIndex, tokens.end());

				Token ParenthesisTokenResult = Token("FLOAT", std::to_string(middResult));

				tokens.push_back(ParenthesisTokenResult);

				//adding right part of all term to tokens
				for (int x = 0; x < tokensSubsetRight.size(); x++)
				{
					tokens.push_back(tokensSubsetRight[x]);
				}

				return CalcExpr(1, tokens);
			}

			if (this->operatorsPriority[tokens[i].Type] == curr_prior)
			{
				for (int h = 0; h < i; h++)
					tokensSubsetLeft.push_back(tokens[h]);

				return SplitSubSetsAndDoMath(curr_prior, &tokensSubsetLeft, &tokens[i], &tokensSubsetRight);
			}
			else
			{
				tokensSubsetRight.push_front(tokens[i]);
			}
		}
		curr_prior++;
	}

	//here, if not found that means it is wxpresion like "lalla   lalala   33"  so
	//there are several tokens, but no operaotr

	int pow = 1;
	double ReturnValue = 0;
	Lexer lexer("", "");
	for (int i = tokens.size() - 1; i >= 0; i--)
	{
		if (tokens[i].Type == lexer.TT_FLOAT || tokens[i].Type == lexer.TT_INT)
		{
			ReturnValue += std::stod(tokens[i].Value) * pow;
		}
		else
			ReturnValue += (double)tokens[i].Value.length() * pow;

		pow *= 10;
	}

	return ReturnValue;
}