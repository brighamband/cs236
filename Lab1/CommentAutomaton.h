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
        bool invalid = false;
        unsigned int currIndex = 2;  // Start at 3rd value

        if (input.front() == '#') {
            inputRead++;

            // If single comment
            if (input.at(1) != '|') {
                inputRead++;

                while (currIndex < input.size()) {
                    // Start looking at 3rd char
                    if (input.at(currIndex) == '\n') {
                        // return inputRead;
                        break;
                    }
                    inputRead++;
                    currIndex++;
                }
            }
            // If block comment
            else {
                inputRead++;

                while ((currIndex < input.size()) && !invalid) {
                    if (input.at(currIndex) == '|') {
                        if (input.at(currIndex + 1) == '#') {
                            // acceptable block comment
                            inputRead++;
                        } else {
                            invalid = true;
                        }
                    }
                    inputRead++;
                    currIndex++;
                }
            }
        }

        if (invalid) {
            type = UNDEFINED;
        }

        return inputRead;
    }
};

#endif