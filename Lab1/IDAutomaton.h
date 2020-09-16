#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H

#include <cctype>
#include <string>

#include "Automaton.h"
#include "Token.h"
using namespace std;

class IDAutomaton : public Automaton {
   public:
    IDAutomaton(tokenType typeOfToken) : Automaton(typeOfToken) {}
    int read(const string &input) {
        int inputRead = 0;

        if (isalpha(input.front())) {
            inputRead++;
            // start at second value
            for (unsigned int i = 1; i < input.size(); i++) {
                if (isalnum(input.at(i))) {
                    inputRead++;
                } else {
                    break;
                }
            }
        }

        return inputRead;
    }
    Token createToken(string input, int lineNumber) {
        return Token(type, input, lineNumber);
    }
    int newLinesRead() const { return newLines; }
};

#endif