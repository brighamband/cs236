#include <fstream>
#include <iostream>
#include <string>

// #include "DatalogProgram.h"
#include "Lexer.h"
#include "Parameter.h"
#include "Parser.h"
#include "Predicate.h"
#include "Rule.h"
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

    vector<Parameter> paramV;
    Parameter param1("hello");
    Parameter param2("guys");
    Parameter param3("heyyo");
    paramV.push_back(param1);
    paramV.push_back(param2);
    paramV.push_back(param3);

    vector<Predicate> predV;
    Predicate hp("head", paramV);
    Predicate pred1("student1", paramV);
    Predicate pred2("student2", paramV);

    predV.push_back(hp);
    predV.push_back(pred1);
    predV.push_back(pred2);
    Rule rule(hp, predV);
    cout << rule.toString();

    // FIXME LATER
    // cout << parser.toString();
    // cout << DatalogProgam::toString();

    return 0;
}