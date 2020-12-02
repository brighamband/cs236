#include <fstream>
#include <iostream>
#include <string>

#include "DatalogProgram.h"
#include "Graph.h"
#include "Interpreter.h"
#include "Lexer.h"
#include "Node.h"
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


    // GRAPH TESTING - FIXME TODO - Remove include graph.h at top
//    Graph graph;
//    Node node(1);
//    node.addAdjacentNodes();
//    //    std::cout << node.toString();
//    graph.addNode(node);
//    Node node2(2);
//    node2.addAdjacentNodes();
//    //    std:cout << std::endl << node2.toString();
//    graph.addNode(node2);
//    std::cout << graph.toString();

    return 0;
}