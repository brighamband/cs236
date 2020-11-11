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

int main(int argc, char *argv[]) {
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

    // Header header({"S", "N", "A", "P"});
    // Tuple t1({"12345", "Charlie", "12 Apple St.", "555-1234"});
    // Tuple t2({"33333", "Snoopy", "12 Apple St.", "555-1234"});
    // Tuple t3({"67890", "Lucy", "34 Pear Ave.", "555-5678"});
    // Tuple t4({"12345", "Charlie", "12 Apple St.", "Charlie"});

    // Relation relation("snap", header);
    // relation.addTuple(t1);
    // relation.addTuple(t2);
    // relation.addTuple(t3);
    // relation.addTuple(t4);

    // Tuple t5({"12845", "Charlie", "12 Apple St.", "Charlie"});

    // Relation relation2("snap2", header);
    // relation2.addTuple(t1);
    // relation2.addTuple(t2);
    // relation2.addTuple(t3);
    // relation2.addTuple(t5);

    // relation.unionize(relation2);

    return 0;
}