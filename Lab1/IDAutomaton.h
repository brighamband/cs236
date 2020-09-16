#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H

#include <cctype>
#include <string>

#include "Automaton.h"
using namespace std;

class IDAutomaton : public Automaton {
   public:
    IDAutomaton(tokenType typeOfToken) : Automaton(typeOfToken) {}
    int read(const string &input) {
        int inputRead = 0;
        bool terminated = false;

        if (isalpha(input.front())) {
            inputRead++;

            // start at second value
            unsigned int currIndex = 1;

            while ((currIndex < input.size()) && !terminated) {
                if (isalnum(input.at(currIndex))) {
                    inputRead++;
                    currIndex++;
                } else {
                    terminated = true;
                }
            }
        }

        return inputRead;
    }
};

#endif