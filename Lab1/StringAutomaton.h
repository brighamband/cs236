#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H

#include <string>

#include "Automaton.h"
using namespace std;

class StringAutomaton : public Automaton {
   public:
    StringAutomaton(tokenType typeOfToken) : Automaton(typeOfToken) {}
    int read(const string &input) {
        bool accepted = false;
        int inputRead = 0;

        if (input.front() == '\'') {
            inputRead++;
            // start from second value
            for (unsigned int i = 1; i < input.size(); i++) {
                if (input.at(i) == '\'') {
                    accepted = !accepted;
                }
                inputRead++;
            }

            // while () {}
        }

        // if (!accepted) {
        //     type = UNDEFINED;
        // }
        return inputRead;
    }
};

#endif