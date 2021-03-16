#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include "Token.h"
#include "Lexer.h"

//https://www.youtube.com/watch?v=RriZ4q4z9gU&t=622s&ab_channel=CodePulse  -- 5:40

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