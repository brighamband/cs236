#ifndef MATCHERAUTOMATON_H
#define MATCHERAUTOMATON_H

#include <string>

#include "Automaton.h"

class MatcherAutomaton : public Automaton {
   private:
    std::string toMatch;

   public:
    MatcherAutomaton(tokenType typeOfToken, std::string stringToMatch)
        : Automaton(typeOfToken) {
        toMatch = stringToMatch;
    }
    int read(const std::string &input) {
        bool isMatch = true;
        unsigned int inputRead = 0;
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
};

#endif