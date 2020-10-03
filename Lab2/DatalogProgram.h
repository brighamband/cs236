// Data Members:

#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include <Predicate.h>
#include <Rule.h>

#include <string>
#include <vector>
using namespace std;

class DatalogProgram {
   private:
    vector<Predicate> schemeVctr;
    vector<Predicate> factVctr;
    vector<Predicate> queryVctr;
    vector<Rule> ruleVctr;

   public:
    DatalogProgram() {}
    // DatalogProgram(string predicateName, string listOfParameters) {
    //     name = predicateName;
    //     parameterList = listOfParameters;
    // }
    string toString() const {  // for all scheme predicates, call predicate to string
        // string tokenStr = " Test Vector:\n";
        // for (unsigned int i = 0; i < tokenVctr.size(); i++) {
        //     tokenStr += tokenVctr.at(i).toString() + "\n";
        // };
        // tokenStr += "Total Tokens = " + to_string(tokenVctr.size()) + "\n";
        // return tokenStr;
    }
};

#endif