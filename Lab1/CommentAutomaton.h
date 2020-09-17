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
        int inputRead = 0;
        bool terminated = false;
        unsigned int currIndex = 2;  // Start at 3rd value

        if (input.front() == '#') {
            inputRead++;

            // CASE 1 - if single comment
            if (input.at(1) != '|') {
                inputRead++;

                // include rest of line
                while ((currIndex < input.size()) && (input.at(currIndex) != '\n')) {
                    inputRead++;
                    currIndex++;
                }
            }
            // CASE 2 - if block comment
            else {
                inputRead++;

                while ((currIndex < input.size())) {
                    if (input.at(currIndex) == '\n') {
                        newLines++;
                    }
                    if (input.at(currIndex) == '|') {
                        inputRead++;
                        // block comment is valid (closed)
                        if (input.at(currIndex + 1) == '#') {
                            inputRead++;
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