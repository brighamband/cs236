#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>
using namespace std;

#include "Parameter.h"

class Predicate {
   private:
    string name;
    vector<Parameter> paramList;

   public:
    Predicate() {}
    Predicate(string predicateName, vector<Parameter> listOfParameters) {
        name = predicateName;
        paramList = listOfParameters;
    }
    string getName() const {
        return name;
    }
    string getParam(size_t index) const {
        return paramList.at(index).toString();
    }
    vector<string> convertParamsToVS() {
        vector<string> vs;
        for (size_t i = 0; i < paramList.size(); i++) {
            vs.push_back(paramList.at(i).toString());
        }
        return vs;
    }
    string toString() const {
        string predStr = "";
        predStr += name + "(";
        for (unsigned int i = 0; i < paramList.size(); i++) {
            if (i > 0) {
                predStr += ",";
            }
            predStr += paramList.at(i).toString();
        };
        predStr += ")";
        return predStr;
    }
};

#endif