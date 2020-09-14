#ifndef MATCHERAUTOMATON_H
#define MATCHERAUTOMATON_H

// #include <string>
using namespace std;

class MatcherAutomaton : public Automaton
{
private:
    std::string toMatch;

public:
    MatcherAutomaton(std::string toMatch, TokenType tokenType);
    int Read(const std::string &input);
};
and int MatcherAutomaton::Read(const std::string &input)
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

#endif