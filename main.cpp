// FreedomLanguage.cpp : Defines the entry point for the application.
//

#include "FreedomLanguage.h"



std::tuple<std::string, std::string> __GET_OVERPARSER_FUNCS__(std::string input, Core* core, std::deque < Order >* orders);

void run(std::string fn, std::string text, Core* core)
{
	auto lexer = Lexer(text, fn);

	for (auto const& x : core->GetVarables())
	{
		lexer.Variables[x.first] = true;
	}

	//to avoid deleting at the first run
	if (core->GetOpSymbls().size() > 0 && core->GetKeyWords().size() > 0)
	{
		lexer.SetOpSymbls(core->GetOpSymbls());
		lexer.SetKeyWords(core->GetKeyWords());
	}

	auto tokens = lexer.make_tokens();

	core->SetOpSymbls(lexer.GetOpSymb());
	core->SetKeyWords(lexer.GetKeyWords());


	core->SetTokens(tokens);
}

int main()
{
	Core core;
	auto parser = Parser(&core.GetTokens());
	std::deque < Order > orders;

	std::string text;
	std::string cinName = "";
	do
	{
		text = "";
		std::cout << "freedom >>";
		std::getline(std::cin, text);

		auto __over_funcs_result__ = __GET_OVERPARSER_FUNCS__(text, &core, &orders);
		cinName = std::get<0>(__over_funcs_result__);
		text = std::get<1>(__over_funcs_result__);

		run("<" + cinName + ">", text, &core);
		parser.SetVariables(core.GetVarables());
		orders = parser.parse(core.GetTokens());
		core.SetVarables(parser.GetVariables());



	} while (text != "q");
}

std::tuple<std::string, std::string> __GET_OVERPARSER_FUNCS__(std::string input, Core* core, std::deque < Order >* orders)
{
	//special functions:
	if (input == "actvars")
	{
		for (auto const& x : core->GetVarables())
		{
			std::cout << x.first  // string (key)
				<< ':'
				<< x.second.Type
				<< " = "
				<< x.second.Value
				<< std::endl;
		}
	}
	else if (input == "toks")
	{
		for (auto const& x : core->GetTokens())
		{
			std::cout << x.Type  // string (key)
				<< ':'
				<< x.Value
				<< std::endl;
		}
	}
	else if (input == "ordrs")
	{
		for (auto x : *orders)
		{
			std::cout << x.GetTypeSTR()// string (key)
				<< std::endl;
		}
	}
	else if (input == "clrvars")
	{
		std::unordered_map<std::string, Token> emptyMap;
		core->SetVarables(emptyMap);
	}
	else if (input == "rstrt")
	{
		Core newCore;
		*core = newCore;
	}
	else if (input.substr(0, 4) == "opnf")
	{
		std::string parameters[16];
		short flagsSmount = 0;

		int flagsIreator = 5;
		for (; flagsIreator < input.size(); flagsIreator++)
		{
			if (input[flagsIreator] != ' ')
				parameters[flagsSmount] += input[flagsIreator];
			else
				flagsSmount++;
		}

		//properties:
		std::string fileName = "";
		bool runFromFIle = false;


		short paramCounter = 0;

		int flagsfinINX = -1;
		//going to the end of flags
		while (parameters[++flagsfinINX][0] == '-') {}

		for (int i = 0; i <= flagsSmount; i++)
		{
			if (parameters[i] == "-n")
			{
				fileName = parameters[flagsfinINX + paramCounter];

				paramCounter++;
			}
			else if (parameters[i] == "-rn")
			{
				runFromFIle = true;
			}
		}

		if (runFromFIle)
		{
			Lexer lexer("", "");
			std::ifstream programFile(fileName);

			std::string programInpuitFromFile = "";
			std::string line = "";
			while (std::getline(programFile, line))
			{
				programInpuitFromFile += line;

				for (auto const& x : lexer.GetKeyWords())
				{
					if (x.second == lexer.TT_NEWLN)
					{
						programInpuitFromFile += "     " + x.first + "   ";
						break;
					}
				}
			}
			return std::make_tuple(fileName, programInpuitFromFile);
		}




	}
	else
		return std::make_tuple("frdm", input);

	return std::make_tuple("", "");
}
