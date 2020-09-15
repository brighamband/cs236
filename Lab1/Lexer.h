#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"
#include "MatcherAutomaton.h"
using namespace std;

class Lexer
{
private:
    vector<Automaton *> automatonVector;
    vector<Token> tokenVector;
    int lineNumber = 0; // what line you're on

public:
    Lexer()
    {
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
        /* automatonVector.push_back(new IDAutomaton(ID,
    automatonVector.push_back(new StringAutomaton(STRING,
    automatonVector.push_back(new CommentAutomaton(COMMENT, */
        // FIXME - Add a block comment automaton?
        /* automatonVector.push_back(new MatcherAutomaton(WHITESPACE,
    automatonVector.push_back(new MatcherAutomaton(UNDEFINED,
    automatonVector.push_back(new MatcherAutomaton(END_OF_FILE */
    }
    void run(string input)
    {
        tokenVector.push_back(Token(COMMA, "test", 4));
        tokenVector.push_back(Token(LEFT_PAREN, "test2", 6));
        // NOTE: Lexer class needs a collection of machines and
        // an ordered collection to store the tokens generated
        // lineNumber = 1;
        // while
        // set lineNumber to 1 looop on input.size() > 0
        // {
        //     set maxRead to 0 set maxMachine to the first item in machines foreach machine in machines
        //     {
        //         inputRead = machine.Read(input) if (inputRead > maxRead)
        //         {
        //             set maxRead to inputRead
        //                 set maxMachine to machine
        //                     set maxNewLines to machine.NewLinesRead()
        //         }
        //     }
        // if
        //         maxRead > 0
        //         {
        //             set newToken to maxMachine.CreateToken(...)
        //                 increment lineNumber by maxNewLines
        //                     add newToken to collection of all tokens
        //         }
        //     else
        //     { // No machine accepted the input, so it is invalid
        //         set maxRead to 1 set newToken to a new invalid Token(with first character of input)
        //             add newToken to collection of all tokens
        //     }
        //     remove maxRead characters from input
        // }
    }
    string toString() const
    {
        string tokensString = "";
        for (unsigned int i = 0; i < tokenVector.size(); i++)
        {
            tokensString += tokensString + tokenVector.at(i).toString() + "\n";
        };
        return tokensString;
    }
};

#endif