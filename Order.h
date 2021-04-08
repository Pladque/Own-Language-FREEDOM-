#include <deque>
#include "Token.h"
#include "Lexer.h"
 
#ifndef ORDER_H
#define ORDER_H

#pragma once
#pragma once
class Order
{

public:
	std::deque < Token > tokens;
	enum Type { term, declar, loop_start, loop_stop, if_statement, if_stop, print, printValues, revalue, revalueSTR, skip};
	Type type;

	std::string GetTypeSTR()
	{
		switch (type)
		{
		case term:
			return "term";
		case declar:
			return "declar";
		case loop_start:
			return "loop_start";
		case loop_stop:
			return "loop_stop";
		case if_statement:
			return "if_statement";
		case if_stop:
			return "if_stop";
		case print:
			return "print";
		case revalue:
			return "revalue";
		default:
			return "Unknown type";
		}
	}

	void printTokens()
	{
		for (int i = 0; i < tokens.size(); i++)
		{
			if (tokens[i].Value != "None")
				std::cout << tokens[i].Value << ' ';
			else
			{
				bool found = false;
				Lexer lexer("", "");
				for (auto const& x : lexer.GetOpSymb())
				{
					if (x.second == tokens[i].Type)
					{
						std::cout << x.first << ' ';
						found = true;
						break;
					}
				}

				if (!found)
					for (auto const& x : lexer.GetKeyWords())
					{
						if (x.second == tokens[i].Type)
						{
							std::cout << x.first << ' ';
							break;
						}
					}
			}

		}
		std::cout << std::endl;
	}
};

#endif


