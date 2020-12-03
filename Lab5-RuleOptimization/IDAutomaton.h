#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H

#include <cctype>
#include <string>

#include "Automaton.h"

class IDAutomaton : public Automaton {
   public:
    IDAutomaton(tokenType typeOfToken) : Automaton(typeOfToken) {}
    int read(const std::string &input) {
        unsigned int inputRead = 0;
        unsigned int currIndex = 0;

        if (isalpha(input.front())) {
            inputRead++;

            currIndex = 1;  // start at second value

            while (currIndex < input.size()) {
                if (!isalnum(input.at(currIndex))) {
                    break;
                }
                inputRead++;
                currIndex++;
            }
        }

        return inputRead;
    }
};

#endif