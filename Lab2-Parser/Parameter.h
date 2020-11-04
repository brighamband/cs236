#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
using namespace std;

class Parameter {
   private:
    string value;

   public:
    Parameter(string paramVal) {
        value = paramVal;
    }
    void setValue(string paramVal) {
        value = paramVal;
    }
    string toString() const {
        return value;
    }
};

#endif