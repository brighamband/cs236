#ifndef MATCHERAUTOMATON_H
#define MATCHERAUTOMATON_H

#include <string>
#include "Automaton.h"
#include "Token.h"
using namespace std;

class MatcherAutomaton : public Automaton
{
private:
    std::string toMatch;

public:
    MatcherAutomaton(string toMatch, TokenType tokenType);
    int read(const string &input)
    {
        bool isMatch = true;
        int inputRead = 0;
        for (int i = 0; i < (int)toMatch.size() && isMatch; i++)
        {
            if (input[i] != toMatch[i])
            {
                isMatch = false;
            }
        }
        if (isMatch)
        {
            inputRead = toMatch.size();
        }
        return inputRead;
    }
};

#endif