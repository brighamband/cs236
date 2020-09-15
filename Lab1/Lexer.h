#ifndef LEXER_H
#define LEXER_H

#include <cctype>
#include <string>
#include <vector>

#include "MatcherAutomaton.h"
#include "Token.h"
using namespace std;

class Lexer {
   private:
    vector<Automaton *> automatonVector;
    vector<Token> tokenVector;
    int lineNumber = 0;  // what line you're on

   public:
    Lexer() {
        automatonVector.push_back(new MatcherAutomaton(COMMA, ","));
        automatonVector.push_back(new MatcherAutomaton(PERIOD, "."));
        automatonVector.push_back(new MatcherAutomaton(Q_MARK, "?"));
        automatonVector.push_back(new MatcherAutomaton(LEFT_PAREN, "("));
        automatonVector.push_back(new MatcherAutomaton(RIGHT_PAREN, ")"));
        automatonVector.push_back(new MatcherAutomaton(COLON, ":"));
        automatonVector.push_back(new MatcherAutomaton(COLON_DASH, ":-"));
        automatonVector.push_back(new MatcherAutomaton(MULTIPLY, "*"));
        automatonVector.push_back(new MatcherAutomaton(ADD, "+"));
        automatonVector.push_back(new MatcherAutomaton(SCHEMES, "SCHEMES"));
        automatonVector.push_back(new MatcherAutomaton(FACTS, "FACTS"));
        automatonVector.push_back(new MatcherAutomaton(RULES, "RULES"));
        automatonVector.push_back(new MatcherAutomaton(QUERIES, "QUERIES"));

        // FIXME - Below are custom automata
        /* automatonVector.push_back(new IDAutomaton(ID);
    automatonVector.push_back(new StringAutomaton(STRING);
    automatonVector.push_back(new CommentAutomaton(COMMENT); */
    }
    ~Lexer() {
        // for (unsigned int i = 0; i < automatonVector.size(); i++)
        // {
        //     delete automatonVector.at(i);
        // }

        // for (const auto &machine : automatonVector) {
        //     delete machine;
        // }
    }
    void run(string input) {
        // int maxRead = 0;
        // int inputRead = 0;
        // int maxNewLines = 0;
        // lineNumber = 1;
        // Automaton* maxMachine = automatonVector.at(0);
        Token newToken;

        /* TESTING */
        newToken = Token(COMMA, "test", 4);
        tokenVector.push_back(newToken);
        newToken = Token(LEFT_PAREN, "test2", 6);
        tokenVector.push_back(newToken);
        /* DONE TESTING */

        // while (!input.empty()) {
        //     maxRead = 0;
        //     maxNewLines = 0;

        //     // while current char is whitespace, move on to next char
        //     while (isspace(input.at(i)) {
        //         i++;
        //     }

        //     for (const auto& machine : automatonVector)
        //     {
        //         inputRead = machine->read(input);
        //         if (inputRead > maxRead) {
        //             maxRead = inputRead;
        //             maxMachine = machine;
        //             maxNewLines = machine->newLinesRead();
        //         }
        //     }

        //     if (maxRead > 0)
        //     {
        //         newToken = maxMachine->createToken();
        //         lineNumber += maxNewLines;
        //         tokenVector.push_back(newToken);
        //     }
        //     else
        //     { // No machine accepted the input, so it is invalid   HANDLES
        //         UNDEFINED
        //         maxRead = 1;
        //         newToken = Token(UNDEFINED, input.at(0), lineNumber);
        //         tokenVector.push_back(newToken);
        //     }
        //     // remove maxRead characters from input
        //     input.erase(0, maxRead + 1);
        // }
        // make an EOF Token
        newToken = Token(END_OF_FILE, "\"\"", lineNumber);
        tokenVector.push_back(newToken);
    }

    string toString() const {
        string tokensString = "";
        for (unsigned int i = 0; i < tokenVector.size(); i++) {
            tokensString += tokenVector.at(i).toString() + "\n";
        };
        return tokensString;
    }
};

#endif