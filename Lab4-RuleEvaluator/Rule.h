#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>

#include "Predicate.h"
using namespace std;

class Rule {
   private:
    Predicate headPredicate;
    vector<Predicate> predicateList;

   public:
    Rule(Predicate headPred, vector<Predicate> listOfPredicates) {
        headPredicate = headPred;
        predicateList = listOfPredicates;
    }
    string getHeadPredicateName() const {
        return headPredicate.getName();
    }
    std::vector<Predicate> getPredicateList() const {
        return predicateList;
    }
    size_t getSize() const {
        return predicateList.size();
    }
    string toString() const {
        string ruleStr = "";
        ruleStr += headPredicate.toString() + " :- ";
        for (unsigned int i = 0; i < predicateList.size(); i++) {
            if (i > 0) {
                ruleStr += ",";
            }
            ruleStr += predicateList.at(i).toString();
        };
        return ruleStr;
    }
};

#endif