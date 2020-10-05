// EXAMPLE

// Rules(7):
//   before(C1,C2) :- cp(C2,C1).
//   before(C1,C2) :- cp(C3,C1),before(C3,C2).
//   tthCourses(C) :- cdh(C,'Tu',H).
//   tthCourses(C) :- cdh(C,'Th',H).
//   Schedule(N,C,R,D,H) :- snap(S,N,A,P),csg(C,S,G),cr(C,R),cdh(C,D,H).
//   Grades(N,C,G) :- snap(S,N,A,P),csg(C,S,G).
//   Students(C,R,N,G) :- snap(S,N,A,P),csg(C,S,G),cr(C,R).

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
    string toString() const {
        string ruleStr = "";
        ruleStr += headPredicate.toString() + " :- ";
        for (unsigned int i = 0; i < predicateList.size(); i++) {
            if (i > 0) {
                ruleStr += ",";
            }
            ruleStr += predicateList.at(i).toString();
        };
        ruleStr += ".";
        return ruleStr;
    }
};

#endif