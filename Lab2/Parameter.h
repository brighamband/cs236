// Maybe break down into 2 subclasses (this would become abstract):
//     Expression
//     PlainParameter

#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
using namespace std;

class Parameter {
   private:
    // string name;
    // string value;

   public:
    Parameter() {}
    // Parameter(string predicateName, string listOfParameters) {
    //     name = predicateName;
    //     parameterList = listOfParameters;
    // }
    string toString() const {
        return "FIXME";
        // string paramStr = "";
    }
};

#endif