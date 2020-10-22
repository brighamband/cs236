#include <fstream>
#include <iostream>
#include <string>

#include "DatalogProgram.h"
#include "Interpreter.h"
#include "Lexer.h"
#include "Parser.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Please provide the name of input file.";
        return 1;
    }

    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 1;
    }

    // get input, add to string
    std::string line = "";
    std::string inputString = "";
    char inputChar = '\0';

    while (in.get(inputChar)) {
        inputString += inputChar;
    }

    // run lexer
    Lexer lexer;
    vector<Token> lexerTokens = lexer.run(inputString);

    // run parser (exit program if fails)
    Parser parser(lexerTokens);
    DatalogProgram datalog;
    try {
        datalog = parser.parse();
        cout << "Success!\n";
        cout << datalog.toString();
    } catch (Token badToken) {
        cerr << "Failure!\n  " << badToken.toString() << "\n";
        return 0;
    }

    // run interpreter
    Interpreter interpreter(datalog);

    return 0;
}