#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include <set>
#include <string>
#include <vector>

#include "Predicate.h"
#include "Rule.h"
using namespace std;

class DatalogProgram {
   private:
    vector<Predicate> schemesVctr;
    vector<Predicate> factsVctr;
    vector<Rule> rulesVctr;
    vector<Predicate> queriesVctr;
    set<string> domainSet;

   public:
    void addScheme(Predicate scheme) {
        schemesVctr.push_back(scheme);
    }
    void addFact(Predicate fact) {
        factsVctr.push_back(fact);
    }
    void addRule(Rule rule) {
        rulesVctr.push_back(rule);
    }
    void addQuery(Predicate query) {
        queriesVctr.push_back(query);
    }
    void addDomain(string domain) {
        domainSet.insert(domain);
    }
    string toStringSchemes() const {
        string schemesStr = "";
        schemesStr += "Schemes(" + to_string(schemesVctr.size()) + "):\n";
        for (unsigned int i = 0; i < schemesVctr.size(); i++) {
            schemesStr += "  " + schemesVctr.at(i).toString() + "\n";
        }
        return schemesStr;
    }
    string toStringFacts() const {
        string factsStr = "";
        factsStr += "Facts(" + to_string(factsVctr.size()) + "):\n";
        for (unsigned int i = 0; i < factsVctr.size(); i++) {
            factsStr += "  " + factsVctr.at(i).toString() + ".\n";
        }
        return factsStr;
    }
    string toStringRules() const {
        string rulesStr = "";
        rulesStr += "Rules(" + to_string(rulesVctr.size()) + "):\n";
        for (unsigned int i = 0; i < rulesVctr.size(); i++) {
            rulesStr += "  " + rulesVctr.at(i).toString() + ".\n";
        }
        return rulesStr;
    }
    string toStringQueries() const {
        string queriesStr = "";
        queriesStr += "Queries(" + to_string(queriesVctr.size()) + "):\n";
        for (unsigned int i = 0; i < queriesVctr.size(); i++) {
            queriesStr += "  " + queriesVctr.at(i).toString() + "?\n";
        }
        return queriesStr;
    }
    string toStringDomain() const {
        string domainStr = "";
        domainStr += "Domain(" + to_string(domainSet.size()) + "):\n";
        for (set<string>::iterator iter = domainSet.begin(); iter != domainSet.end(); ++iter) {
            domainStr += "  " + *iter + "\n";
        }
        return domainStr;
    }
    string toString() const {
        string combinedStr = "";
        combinedStr += toStringSchemes() + toStringFacts() + toStringRules() + toStringQueries() + toStringDomain();
        return combinedStr;
    }
};

#endif