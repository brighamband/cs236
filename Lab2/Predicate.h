// Contains these objects:
//     Schemes
//     Facts
//     Rules
//     Queries

#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
using namespace std;

class Predicate {
   private:
    string name;
    string parameterList;  // FIXME - What is the right type?

   public:
    Predicate() {}
    Predicate(string predicateName, string listOfParameters) {
        name = predicateName;
        parameterList = listOfParameters;
    }
    string toString() const {
        return name + parameterList;
        // string tokenStr = " Test Vector:\n";
        // for (unsigned int i = 0; i < tokenVctr.size(); i++) {
        //     tokenStr += tokenVctr.at(i).toString() + "\n";
        // };
        // tokenStr += "Total Tokens = " + to_string(tokenVctr.size()) + "\n";
        // return tokenStr;
    }
};

#endif