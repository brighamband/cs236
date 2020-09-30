#ifndef PARSER_H
#define PARSER_H

// #include <string>
#include <vector>

#include "Token.h"
using namespace std;

class Parser {
   private:
    vector<Token> tokenVctr;

   public:
    Parser(vector<Token> lexerTokens) {
        tokenVctr = lexerTokens;
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
        try {
            parseDatalogProgram();
        } catch (int errorNum) {
            cerr << "Yikes!  Error " << errorNum << " occurred." << endl;
            if (errorNum == 1) {
                cerr << "You messed up in parseSch." << endl;
            }
        }
    }
    void parseDatalogProgram() {
        cout << "done parsing datalogProgram." << endl;
        parseScheme();
    }
    void parseScheme() {
        throw 1;
        cout << "done parsing scheme." << endl;
        parseHeadPredicate();
    }
    void parseHeadPredicate() {
        parseIdList();
    }
    void parseIdList() {
        cout << "end of parsing." << endl;
    }
    string toString() const {
        string tokenStr = " Test Vector:\n";
        for (unsigned int i = 0; i < tokenVctr.size(); i++) {
            tokenStr += tokenVctr.at(i).toString() + "\n";
        };
        tokenStr += "Total Tokens = " + to_string(tokenVctr.size()) + "\n";
        return tokenStr;
    }
};

#endif