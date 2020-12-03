#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>

#include "Token.h"

class Automaton {
   protected:
    int newLines = 0;
    tokenType type;

   public:
    Automaton(tokenType typeOfToken) { type = typeOfToken; }
    virtual ~Automaton() {}
    virtual int read(const std::string &input) = 0;
    virtual Token createToken(std::string input, int lineNumber) {
        return Token(type, input, lineNumber);
    }
    virtual int newLinesRead() const { return newLines; }
};

#endif