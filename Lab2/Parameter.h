// Maybe break down into 2 subclasses (this would become abstract):
//     Expression
//     PlainParameter

#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
using namespace std;

class Parameter {
   private:
    string value;

   public:
    Parameter(string predValue) {
        value = predValue;
    }
    string toString() const {
        return value;
    }
};

#endif