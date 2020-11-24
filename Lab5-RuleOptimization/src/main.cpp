/*
1   implement union
2   implement natural join
3   evaluate rules (query eval, nat join, project, rename, and union)
*/
#include <fstream>
#include <iostream>
#include <string>

#include "DatalogProgram.h"
#include "Interpreter.h"
#include "Lexer.h"
#include "Parser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Please provide the name of input file.";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Unable to open " << argv[1] << " for input";
        return 1;
    }

    // get input, add to string
    std::string line;
    std::string inputString;
    char inputChar;

    while (in.get(inputChar)) {
        inputString += inputChar;
    }

    // run lexer
    Lexer lexer;
    vector<Token> lexerTokens = lexer.run(inputString);

    // run parser (exit program if fails)
    Parser parser(lexerTokens);
    DatalogProgram datalog = parser.parse();

    // run interpreter
    Interpreter interpreter(datalog);
    std::cout << interpreter.interpret();

    return 0;
}