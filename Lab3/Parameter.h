#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
using namespace std;

class Parameter {
   private:
    string value;
    bool isConstant;

   public:
    Parameter(string paramVal) {
        value = paramVal;
    }
    void setIsConstant(bool isC) {
        isConstant = isC;
    }
    void setValue(string paramVal) {
        value = paramVal;
    }
    string toString() const {
        return value;
    }
};

#endif