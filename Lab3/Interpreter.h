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
    // Interpreter() {}
    Interpreter(DatalogProgram d) {
        datalog = d;
        database = makeDatabase();
    }
    // ~Interpreter() {
    //     // DELETE NEW RELATIONS MADE
    // }
    Database makeDatabase() {
        std::string key;
        std::map<std::string, Relation*> newDb;

        for (size_t i = 0; i < datalog.getNumSchemes(); i++) {
            key = datalog.getSchemeName(i);
            Relation* newRelation = new Relation(key);
            Header newHeader(datalog.convertSchemeParams(i));
            newRelation->setHeader(newHeader);

            for (size_t j = 0; j < datalog.getNumFacts(); j++) {
                std::vector<std::string> vec;
                if (datalog.getFactName(j) == key) {
                    newRelation->addTuple(Tuple(datalog.convertFactParams(j)));
                }
            }
            newDb.insert({key, newRelation});
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
        Header header = database.getHeader(name);
        std::set<Tuple> body = database.getBody(name);
        Relation* newRelation = new Relation(name, header, body);
        std::vector<std::string> vs;
        std::vector<int> vi;

        for (size_t i = 0; i < p.getSize(); i++) {
            int spotSeen = seenBefore(vs, p.getParam(i));

            if (p.isParamConstant(i)) {  // Case 1 - Constant
                newRelation = newRelation->select(i, p.getParam(i));
            } else if (spotSeen != -1) {  // Case 2 - Seen Variable
                newRelation = newRelation->select(vi.at(spotSeen), i);
            } else {  // Case 3 - New Variable
                vs.push_back(p.getParam(i));
                vi.push_back(i);
            }
        }

        if (vi.size() != 0) {
            newRelation = newRelation->project(vi);
            newRelation = newRelation->rename(vs)
        }

        return newRelation;
    }
    void evaluateQueries() {
        for (size_t i = 0; i < datalog.getNumQueries(); i++) {
            evaluatePredicate(datalog.getQuery(i));)
        }
    }
    std::string toString() const {
        database.toString();
        return "FIXME";
    }
};

#endif