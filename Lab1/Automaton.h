#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>

#include "Token.h"
using namespace std;

class Automaton {
   protected:
    int newLines = 0;  // how many lines did you see in the machine
    tokenType type;

   public:
    Automaton(tokenType typeOfToken) { type = typeOfToken; }
    virtual int read(const string &input) = 0;
    virtual Token createToken(string input, int lineNumber) = 0;
    virtual int newLinesRead() const = 0;
};

#endif