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
    // evalPredicates - first makeRHRelation function that converts Preds to vector of Relations
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
        std::string queryStr = "";
        for (size_t i = 0; i < datalog.getNumQueries(); i++) {
            queryStr += toStringQuery(i);
            Relation* relation = evaluatePredicate(datalog.getQuery(i));
            queryStr += toStringResults(relation);
        }
        return queryStr;
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