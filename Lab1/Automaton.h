#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>
#include "Token.h"
using namespace std;

class Automaton
{
protected:
    int newLines = 0;
    TokenType type;

public:
    Automaton(TokenType tokenType) { type = tokenType; }
    virtual int read(const string &input) = 0;
    virtual Token *createToken(string input, int lineNumber)
    {
        return new Token(type, input, lineNumber);
    }
    virtual int newLinesRead() const { return newLines; }
};

#endif