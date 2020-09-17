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
        unsigned currIndex = 1;  // start loop at 2nd value
        bool terminated = false;

        if (input.front() == '\'') {
            inputRead++;

            while (currIndex < input.size()) {
                // CASE 1 - new line
                if (input.at(currIndex) == '\n') {
                    newLines++;
                }
                // CASE 2 - apostrophe
                else if (input.at(currIndex) == '\'' && input.at(currIndex + 1) == '\'') {
                    inputRead += 2;
                    currIndex += 2;
                }
                // CASE 3 - valid string terminated
                else if (input.at(currIndex) == '\'') {
                    if ((currIndex + 1) == input.size() || input.at(currIndex + 1) != '\'') {
                        inputRead++;
                        terminated = true;
                        break;
                    }
                }
                // CASE 4 - characters within string
                else {
                    inputRead++;
                    currIndex++;
                }
            }
        }

        if (!terminated) {
            type = UNDEFINED;
        }

        return inputRead;
    }
};

#endif