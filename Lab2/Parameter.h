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