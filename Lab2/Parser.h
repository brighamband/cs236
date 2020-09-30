#ifndef PARSER_H
#define PARSER_H

// #include <string>
#include <vector>

#include "Token.h"
using namespace std;

class Parser {
   private:
    // vector<Token> tokenVector;
    vector<Token> testVctr;

   public:
    Parser(vector<Token> vTkns) {
        testVctr = vTkns;
        // automatonVector.push_back(new MatcherAutomaton(COMMA, ","));
        // automatonVector.push_back(new MatcherAutomaton(PERIOD, "."));
        // automatonVector.push_back(new MatcherAutomaton(Q_MARK, "?"));
        // automatonVector.push_back(new MatcherAutomaton(LEFT_PAREN, "("));
        // automatonVector.push_back(new MatcherAutomaton(RIGHT_PAREN, ")"));
        // automatonVector.push_back(new MatcherAutomaton(COLON, ":"));
        // automatonVector.push_back(new MatcherAutomaton(COLON_DASH, ":-"));
        // automatonVector.push_back(new MatcherAutomaton(MULTIPLY, "*"));
        // automatonVector.push_back(new MatcherAutomaton(ADD, "+"));
        // automatonVector.push_back(new MatcherAutomaton(SCHEMES, "Schemes"));
        // automatonVector.push_back(new MatcherAutomaton(FACTS, "Facts"));
        // automatonVector.push_back(new MatcherAutomaton(RULES, "Rules"));
        // automatonVector.push_back(new MatcherAutomaton(QUERIES, "Queries"));
        // // custom automata
        // automatonVector.push_back(new IDAutomaton(ID));
        // automatonVector.push_back(new StringAutomaton(STRING));
        // automatonVector.push_back(new CommentAutomaton(COMMENT));
    }
    void parse() {
        // FIXME
    }

    string toString() const {
        // FIXME
        string tokensString = " Test Vector:\n";
        for (unsigned int i = 0; i < testVctr.size(); i++) {
            tokensString += testVctr.at(i).toString() + "\n";
        };
        tokensString += "Total Tokens = " + to_string(testVctr.size()) + "\n";
        return tokensString;
    }
};

#endif