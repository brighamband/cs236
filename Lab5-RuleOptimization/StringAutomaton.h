#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H

#include <string>

#include "Automaton.h"

class StringAutomaton : public Automaton {
   public:
    StringAutomaton(tokenType typeOfToken) : Automaton(typeOfToken) {}
    int read(const std::string &input) {
        type = STRING;
        newLines = 0;
        unsigned int inputRead = 0;
        char singleQuote = '\'';

        if (input.front() == singleQuote) {
            inputRead++;

            while (inputRead < input.size()) {
                if (input.at(inputRead) == singleQuote) {
                    // CASE 1 - valid string terminated (next is end of file or anything but a single quote)
                    if ((inputRead + 1) == input.size() || input.at(inputRead + 1) != singleQuote) {
                        inputRead++;
                        return inputRead;
                    }
                    // CASE 2 - apostrophe
                    if (input.at(inputRead + 1) == singleQuote) {
                        inputRead += 2;
                        continue;
                    }
                }

                // CASE 3 - new line
                if (input.at(inputRead) == '\n') {
                    newLines++;
                }
                // CASE 4 - characters within string
                inputRead++;
            }
        }
        // CASE 5 - unterminated string
        type = UNDEFINED;
        return inputRead;
    }
};

#endif