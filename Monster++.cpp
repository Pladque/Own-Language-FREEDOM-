#include <iostream>
#include <unordered_map>
#include <deque>
#include <string>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

//https://www.youtube.com/watch?v=RriZ4q4z9gU&t=622s&ab_channel=CodePulse  -- 5:40

std::queue < Token* > Tokens;


std::queue < Token > run(std::string fn, std::string text)
{
    auto lexer = Lexer(text, fn);
    auto tokens = lexer.make_tokens();
    //auto parser = Parser()

    return tokens;
}


int main()
{
    std::string text = "";
    std::deque < Token > results = run("<stdin>", text);
    auto parser = Parser(results);

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