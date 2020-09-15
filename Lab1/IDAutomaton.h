#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H

#include <string>

#include "Automaton.h"
#include "Token.h"
using namespace std;

class IDAutomaton : public Automaton {
   private:
    string toMatch;

   public:
    int read(const string &input) {
        bool isMatch = true;
        int inputRead = 0;
        for (int i = 0; i < (int)toMatch.size() && isMatch; i++) {
            if (input[i] != toMatch[i]) {
                isMatch = false;
            }
        }
        if (isMatch) {
            inputRead = toMatch.size();
        }
        return inputRead;
    }
    Token createToken(string input, int lineNumber) {
        return Token(type, input, lineNumber);
    }
    int newLinesRead() const { return newLines; }
};

#endif