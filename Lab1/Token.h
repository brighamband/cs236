#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

enum tokenType
{
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    WHITESPACE,
    UNDEFINED,
    END_OF_FILE
};

class Token
{
private:
    tokenType type;
    string value;
    int line;

public:
    Token() {}
    Token(tokenType typeOfToken, string valueOfToken, int lineOfToken)
    {
        type = typeOfToken;
        value = valueOfToken;
        line = lineOfToken;
    }
    string typeToString(tokenType typeOfToken) const
    {
        switch (typeOfToken)
        {
        case COMMA:
            return "COMMA";
        case PERIOD:
            return "PERIOD";
        case Q_MARK:
            return "Q_MARK";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case COLON:
            return "COLON";
        case COLON_DASH:
            return "COLON_DASH";
        case MULTIPLY:
            return "MULTIPLY";
        case ADD:
            return "ADD";
        case SCHEMES:
            return "SCHEMES";
        case FACTS:
            return "FACTS";
        case RULES:
            return "RULES";
        case QUERIES:
            return "QUERIES";
        case ID:
            return "ID";
        case STRING:
            return "STRING";
        case COMMENT:
            return "COMMENT";
        case WHITESPACE:
            return "WHITESPACE";
        case UNDEFINED:
            return "UNDEFINED";
        case END_OF_FILE:
            return "EOF";
        default:
            return "ERROR - FIXME";
        }
    }
    string toString() const
    {
        return ("(" + typeToString(type) + "," + value + "," + to_string(line) + ")");
    }
};

#endif