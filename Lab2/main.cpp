#include <fstream>
#include <iostream>
#include <string>

// #include "DatalogProgram.h"
#include "Lexer.h"
#include "Parameter.h"
#include "Parser.h"
#include "Predicate.h"
using namespace std;

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
    string line = "";
    string inputString = "";
    char inputChar = '\0';

    while (in.get(inputChar)) {
        inputString += inputChar;
    }

    // run lexer
    Lexer lexer;
    vector<Token> lexerTokens = lexer.run(inputString);

    // run parser (exit program if fails)
    Parser parser(lexerTokens);
    if (!parser.parse()) {
        return 0;
    }

    vector<Parameter> vctr;
    Parameter p1("hello");
    Parameter p2("guys");
    Parameter p3("heyyo");
    vctr.push_back(p1);
    vctr.push_back(p2);
    vctr.push_back(p3);
    Predicate predicate("student", vctr);
    cout << predicate.toString();

    // cout << parser.toString();
    // cout << DatalogProgam::toString();

    return 0;
}