#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"
using namespace std;

class Lexer
{
private:
    vector<Token> tokenVector;

public:
    Lexer() {}

    // 	Course() {
    // 		course = "Unspecified Course";
    // 	}
    // 	Course(string course) {
    // 		this->course = course;
    // 	}
    // 	string getCourse() const {
    // 		return course;
    // 	}
    // private:
    // 	string course;
};

#endif