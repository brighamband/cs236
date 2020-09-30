#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "Token.h"
using namespace std;

class Parser {
   private:
    vector<Token> tokenVctr;

   public:
    Parser(vector<Token> lexerTokens) {
        tokenVctr = lexerTokens;
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