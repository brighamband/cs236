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

            // CASE 1 - if single comment
            if (input.at(1) != '|') {
                inputRead++;

                // include rest of line
                while ((currIndex < input.size()) && (input.at(currIndex) != '\n')) {
                    // if (input.at(currIndex) == '\n') {
                    //     // return inputRead;
                    //     break;
                    // }
                    inputRead++;
                    currIndex++;
                }
            }
            // CASE 2 - if block comment
            else {
                inputRead++;

                while ((currIndex < input.size()) && !invalid) {
                    if (input.at(currIndex) == '|') {
                        inputRead++;
                        if (input.at(currIndex + 1) == '#') {
                            // acceptable block comment
                            inputRead++;
                        } else {
                            invalid = true;
                        }
                        break;
                    } else if (input.at(currIndex) == '\n') {
                        newLines++;
                        // inputRead--;
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