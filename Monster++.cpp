#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include "Token.h"
#include "Lexer.h"

//https://www.youtube.com/watch?v=Eythq9848Fg&ab_channel=CodePulse  - 11:49

std::queue < Token* > Tokens;


std::queue < Token > run(std::string fn, std::string text)
{
    auto lexer = Lexer(text, fn);
    auto tokens = lexer.make_tokens();

    return tokens;
}


int main()
{
    std::string text = "";
    std::queue < Token > results = run("<stdin>", text);

    text = "2+2 \n 3*3";
    do
    {
        //printing results
        results = run("<stdin>", text);

        while (!results.empty())
        {
            std::cout << results.front() << std::endl;
            //delete results.front();
            results.pop();
        }

        std::cout << "bestia>>";
        std::getline(std::cin, text);
    } while (text != "q");
    
}

/*

std::string operation = "";

    do
    {
        for (int i = 0; i < operation.size(); i++)
        {
            if (operation[i] >= '0' and operation[i] <= '9')
            {
                Token* token = new Token("INT", std::string(1, operation[i]));
                Tokens.push(token);
            }
            else if (operation[i] =='+')
            {
                Token* token = new Token("PLUS");
                Tokens.push(token);
            }
        }


        

        std::cout << "monster>>";
        std::cin >> operation;

    } while (operation != "quit");

    //delete[] Tokens;
    
    */