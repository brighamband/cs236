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
    DatalogProgram datalog = parser.parse();

    // run interpreter
    Interpreter interpreter(datalog);
    std::cout << interpreter.interpret();

    // Header header1({"S", "N", "A", "P"});
    // Tuple ta1({"12345", "C. Brown", "12 Apple St.", "555-1234"});
    // Tuple ta2({"22222", "P. Patty", "56 Grape Blvd", "555-9999"});
    // Tuple ta3({"33333", "Snoopy", "12 Apple St.", "555-1234"});

    // Header header2({"C", "S", "G"});
    // Tuple tb1({"CS101", "12345", "A"});
    // Tuple tb2({"CS101", "22222", "B"});
    // Tuple tb3({"CS101", "33333", "C"});
    // Tuple tb4({"EE200", "12345", "B+"});
    // Tuple tb5({"EE200", "22222", "B"});

    // Relation relation1("snap", header1);
    // relation1.addTuple(ta1);
    // relation1.addTuple(ta2);
    // relation1.addTuple(ta3);

    // Relation* relation2 = new Relation("csg", header2);
    // relation2->addTuple(tb1);
    // relation2->addTuple(tb2);
    // relation2->addTuple(tb3);
    // relation2->addTuple(tb4);
    // relation2->addTuple(tb5);

    // Relation* ans = relation1.naturalJoin(relation2, "newname");
    // cout << ans->toString();
    // relation1.unionize(relation2);

    return 0;
}