#include <fstream>
#include <iostream>
#include <map>  //FIXME
#include <string>

#include "DatalogProgram.h"
#include "Interpreter.h"
#include "Lexer.h"
#include "Parser.h"
// DELETE THESE
#include "Header.h"
#include "Relation.h"
#include "Tuple.h"

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
    DatalogProgram datalog;
    try {
        datalog = parser.parse();
        std::cout << "Success!\n";
        std::cout << datalog.toString();
    } catch (Token badToken) {
        std::cerr << "Failure!\n  " << badToken.toString() << "\n";
        return 0;
    }

    // run interpreter
    Interpreter interpreter(datalog);

    Header header({"S", "N", "A", "P"});
    Tuple t1({"12345", "Charlie", "12 Apple St.", "555-1234"});
    Tuple t2({"33333", "Snoopy", "12 Apple St.", "555-1234"});
    Tuple t3({"67890", "Lucy", "34 Pear Ave.", "555-5678"});
    Tuple t4({"12345", "Charlie", "12 Apple St.", "Charlie"});

    Relation relation("snap", header);
    relation.addTuple(t1);
    relation.addTuple(t2);
    relation.addTuple(t3);
    relation.addTuple(t4);
    // std::cout << relation.toString() << std::endl
    //           << std::endl;

    std::cout << relation.select(1, "Snoopy")->toString();
    // std::cout << relation.select(1, 3)->toString();

    // Header newHeader({"S", "N", "O", "P"});
    // std::cout << relation.rename(newHeader)->toString();

    // TESTING
    std::cout << relation.project({1, 2})->toString();

    // std::map<std::string, Relation *> myMap;
    // myMap["first"] = &relation;
    // myMap["second"] = 2;
    // myMap["third"] = 3;

    // cout << myMap["third"] << "\n";

    //   if (it != mymap.end()) cout <<
    // string toFind = "first";
    // if (myMap.find(toFind) != myMap.end()) {
    //     cout << myMap.find(toFind)->second << "\n";
    // }
    // std::cout << it << endl;

    return 0;
}