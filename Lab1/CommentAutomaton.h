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

        // FIXME
        // HANDLE SINGLE-LINE AND BLOCK COMMENTS

        return inputRead;
    }
};

#endif