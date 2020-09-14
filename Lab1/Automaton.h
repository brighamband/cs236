#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>
using namespace std;

class Automaton
{
protected:
    int newLines = 0;
    TokenType type;

public:
    Automaton(TokenType tokenType) { type = tokenType; }
    virtual int Read(const string &input) = 0;
    virtual Token *CreateToken(string input, int lineNumber)
    {
        return new Token(type, input, lineNumber);
    }
    virtual int NewLinesRead() const { return newLines; }
};

#endif