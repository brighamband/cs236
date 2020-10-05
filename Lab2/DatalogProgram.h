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
    vector<Rule> ruleVctr;
    vector<Predicate> queryVctr;

   public:
    // DatalogProgram() {}
    // DatalogProgram(string predicateName, string listOfParameters) {
    //     name = predicateName;
    //     parameterList = listOfParameters;
    // }
    string toString() const {  // for all scheme predicates, call predicate to string
        string dPStr = "";
        dPStr += "Schemes(" + schemeVctr.size() + "):\n";
        for (unsigned int i = 0; i < schemeVctr.size(); i++) {
            dPStr += "  " + schemeVctr.at(i).toString() + "\n";
        }
        dPStr += "Facts(" + factVctr.size() + "):\n";
        for (unsigned int i = 0; i < factVctr.size(); i++) {
            dPStr += "  " + factVctr.at(i).toString() + ".\n";
        }
        dPStr += "Rules(" + ruleVctr.size() + "):\n";
        for (unsigned int i = 0; i < ruleVctr.size(); i++) {
            dPStr += "  " + ruleVctr.at(i).toString() + ".\n";
        }
        dPStr += "Queries(" + queryVctr.size() + "):\n";
        for (unsigned int i = 0; i < queryVctr.size(); i++) {
            dPStr += "  " + queryVctr.at(i).toString() + "?\n";
        }
        dPStr += "Domain -- FIXME\n";
        return dPStr;
    }
};

#endif