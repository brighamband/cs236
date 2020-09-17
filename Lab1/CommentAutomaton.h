#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H

#include <cctype>
#include <string>

#include "Automaton.h"
using namespace std;

class CommentAutomaton : public Automaton {
   public:
    CommentAutomaton(tokenType typeOfToken) : Automaton(typeOfToken) {}
    int read(const string &input) {
        unsigned int inputRead = 0;
        unsigned int currIndex = 0;
        bool terminated = false;

        if (input.front() == '#') {
            inputRead++;

            // CASE 1 - if single comment
            if (input.at(1) != '|') {
                currIndex = 1;  // start at 2nd value -- include rest of line (if not \n)
                while (currIndex < input.size()) {
                    if (input.at(currIndex) == '\n') {
                        break;
                    }
                    inputRead++;
                    currIndex++;
                }
            }
            // CASE 2 - if block comment
            else {
                inputRead++;

                currIndex = 2;  // start at 3rd value
                while (currIndex < input.size()) {
                    if (input.at(currIndex) == '\n') {
                        newLines++;
                        currIndex++;
                        continue;
                    }
                    if (input.at(currIndex) == '|') {
                        inputRead++;
                        // block comment is valid (closed)
                        if (input.at(currIndex + 1) == '#') {
                            inputRead++;
                            // inputRead += 2;
                            terminated = true;
                            break;
                        }
                    }
                    inputRead++;
                    currIndex++;
                }

                if (!terminated) {
                    type = UNDEFINED;
                }
            }
        }

        return inputRead;
    }
};

#endif