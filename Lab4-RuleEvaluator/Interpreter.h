#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include <set>
#include <string>
#include <vector>

#include "Database.h"
#include "DatalogProgram.h"

class Interpreter {
   private:
    DatalogProgram datalog;
    Database database;
    int numPasses = 0;

   public:
    Interpreter(DatalogProgram d) {
        datalog = d;
        database = makeDatabase();
    }
    // ~Interpreter() {
    //     // DELETE NEW RELATIONS MADE
    // }
    Relation* processSchemes(size_t index, std::string key) {
        Relation* relation = new Relation(key);
        Header header(datalog.convertSchemeParams(index));
        relation->setHeader(header);
        return relation;
    }
    Relation* processFacts(DatalogProgram datalog, Relation* relation, std::string key) {
        for (size_t j = 0; j < datalog.getNumFacts(); j++) {
            std::vector<std::string> vec;
            if (datalog.getFactName(j) == key) {
                relation->addTuple(Tuple(datalog.convertFactParams(j)));
            }
        }
        return relation;
    }
    Database makeDatabase() {
        std::string key;
        std::map<std::string, Relation*> newDb;

        for (size_t i = 0; i < datalog.getNumSchemes(); i++) {
            key = datalog.getSchemeName(i);
            Relation* relation = processSchemes(i, key);
            relation = processFacts(datalog, relation, key);
            newDb.insert({key, relation});
        }
        return newDb;
    }
    int seenBefore(std::vector<std::string> vs, std::string toMatch) const {
        for (size_t i = 0; i < vs.size(); i++) {
            if (toMatch == vs.at(i)) {
                return i;
            }
        }
        return -1;
    }
    Relation* evaluatePredicate(Predicate p) {
        std::string name = p.getName();
        Relation* relation = database.getRelation(name);
        std::vector<std::string> vs;
        std::vector<int> vi;

        for (size_t i = 0; i < p.getSize(); i++) {
            int spotSeen = seenBefore(vs, p.getParam(i));

            if (p.isParamConstant(i)) {  // Case 1 - Constant
                relation = relation->select(i, p.getParam(i));
            } else if (spotSeen != -1) {  // Case 2 - Seen Variable
                relation = relation->select(vi.at(spotSeen), i);
            } else {  // Case 3 - New Variable
                vs.push_back(p.getParam(i));
                vi.push_back(i);
            }
        }

        if (vi.size() != 0) {
            relation = relation->project(vi);
            relation = relation->rename(vs);
        }

        return relation;
    }
    std::string evaluateQueries() {
        std::string queriesStr = "Query Evaluation\n";
        for (size_t i = 0; i < datalog.getNumQueries(); i++) {
            queriesStr += toStringQuery(i);
            Relation* relation = evaluatePredicate(datalog.getQuery(i));
            queriesStr += toStringResults(relation);
        }
        return queriesStr;
    }
    std::vector<Predicate> getRHRelation(size_t index) {
        return datalog.getRule(index).getPredicateList();
    }
    std::string evaluateRule(size_t index) {
        std::string ruleStr = "";
        std::vector<Predicate> vp = getRHRelation(index);
        std::vector<Relation*> vr;
        // FIXME
        Relation* result = new Relation("test");
        for (size_t i = 0; i < datalog.getRule(index).getSize(); i++) {
            Relation* relation = evaluatePredicate(vp.at(i));
            // if (i == 0) {
            //     result = relation;
            // }
            relation->unionize(*result);
            //  else {
            // result = relation->naturalJoin(result);
            // }
            // Join the relations that result
            // Project the columns that appear in the head predicate
            // Rename the relation to make it union-compatible
            // Union with the relation in the database
            vr.push_back(relation);
        }
        // if (vr.size() > 0) {
        //     // join

        //     for (size_t i = 1; i < vr.size(); i++) {

        //     }
        // }
        ruleStr += toStringRule(index) + "\n";
        return ruleStr;
    }
    std::string evaluateRules() {  // MAKE FIXED POINT ALGORITHM
        numPasses = 0;
        std::string rulesStr = "Rule Evaluation\n";
        for (size_t i = 0; i < datalog.getNumRules(); i++) {
            rulesStr += evaluateRule(i);
            numPasses++;
        }
        rulesStr += "\n\nSchemes populated after " + to_string(numPasses) + " passes through the Rules.\n\n";
        return rulesStr;
    }
    std::string interpret() {
        std::string interpretStr = "";
        interpretStr += evaluateRules() += evaluateQueries();
        return interpretStr;
    }
    std::string toStringRule(size_t index) {
        return datalog.getRule(index).toString() + ".";
    }
    std::string toStringQuery(size_t index) {
        return datalog.getQuery(index).toString() + "? ";
    }
    std::string toStringResults(Relation* relation) {
        std::string resultsStr = "";
        int results = relation->getBodySize();
        if (results > 0) {
            resultsStr += "Yes(" + to_string(results) + ")\n";
            if (relation->getShowResults()) {
                resultsStr += relation->toString();
            }
        } else {
            resultsStr += "No\n";
        }
        return resultsStr;
    }
};

#endif