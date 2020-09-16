#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H

#include <string>

#include "Automaton.h"
using namespace std;

class StringAutomaton : public Automaton {
   public:
    StringAutomaton(tokenType typeOfToken) : Automaton(typeOfToken) {}
    int read(const string &input) {
        int inputRead = 0;
        bool terminated = false;

        if (input.front() == '\'') {
            inputRead++;

            // start loop at 2nd value
            for (unsigned int i = 1; i < input.size() && !terminated; i++) {
                if (input.at(i) == '\'') {
                    // If it's not an apostrophe, then string is done and terminated
                    if (input.at(i + 1) != '\'') {
                        terminated = true;
                        // FIXME - ANY OTHER WAY TO DO THIS?
                        type = STRING;
                    }
                } else if (input.at(i) == '\n') {
                    newLines++;
                }
                inputRead++;
            }
        }

        if (!terminated) {
            type = UNDEFINED;
        }

        return inputRead;
    }
};

#endif