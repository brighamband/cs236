#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H

#include <string>

#include "Automaton.h"

class CommentAutomaton : public Automaton {
   public:
    CommentAutomaton(tokenType typeOfToken) : Automaton(typeOfToken) {}
    int read(const std::string &input) {
        type = COMMENT;
        newLines = 0;
        unsigned int inputRead = 0;

        if (input.front() == '#') {
            inputRead++;

            // CASE 1 - single comment
            if (input.at(1) != '|') {
                while (inputRead < input.size()) {
                    if (input.at(inputRead) == '\n') {
                        return inputRead;
                    }
                    inputRead++;
                }
            }
            // CASE 2 - block comment
            else {
                inputRead++;

                while (inputRead < input.size()) {
                    if (input.at(inputRead) == '|') {
                        // CASE 2A - valid block comment terminated
                        if (input.at(inputRead + 1) == '#') {
                            inputRead += 2;
                            return inputRead;
                        }
                    }
                    // CASE 2B - unterminated block comment
                    if ((inputRead + 1) == input.size()) {
                        type = UNDEFINED;
                    }
                    if (input.at(inputRead) == '\n') {
                        newLines++;
                    }
                    // CASE 2C - characters within block comment
                    inputRead++;
                }
            }
        }
        // CASE 3 - empty comment
        return inputRead;
    }
};

#endif