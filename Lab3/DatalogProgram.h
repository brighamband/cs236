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
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domain;

   public:
    void addScheme(Predicate s) {
        schemes.push_back(s);
    }
    void addFact(Predicate f) {
        facts.push_back(f);
    }
    void addRule(Rule r) {
        rules.push_back(r);
    }
    void addQuery(Predicate q) {
        queries.push_back(q);
    }
    void addDomain(string d) {
        domain.insert(d);
    }
    vector<Predicate> getSchemes() const {
        return schemes;
    }
    string toStringSchemes() const {
        string schemesStr = "";
        schemesStr += "Schemes(" + to_string(schemes.size()) + "):\n";
        for (unsigned int i = 0; i < schemes.size(); i++) {
            schemesStr += "  " + schemes.at(i).toString() + "\n";
        }
        return schemesStr;
    }
    string toStringFacts() const {
        string factsStr = "";
        factsStr += "Facts(" + to_string(facts.size()) + "):\n";
        for (unsigned int i = 0; i < facts.size(); i++) {
            factsStr += "  " + facts.at(i).toString() + ".\n";
        }
        return factsStr;
    }
    string toStringRules() const {
        string rulesStr = "";
        rulesStr += "Rules(" + to_string(rules.size()) + "):\n";
        for (unsigned int i = 0; i < rules.size(); i++) {
            rulesStr += "  " + rules.at(i).toString() + ".\n";
        }
        return rulesStr;
    }
    string toStringQueries() const {
        string queriesStr = "";
        queriesStr += "Queries(" + to_string(queries.size()) + "):\n";
        for (unsigned int i = 0; i < queries.size(); i++) {
            queriesStr += "  " + queries.at(i).toString() + "?\n";
        }
        return queriesStr;
    }
    string toStringDomain() const {
        string domainStr = "";
        domainStr += "Domain(" + to_string(domain.size()) + "):\n";
        for (set<string>::iterator iter = domain.begin(); iter != domain.end(); ++iter) {
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