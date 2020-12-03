#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "Database.h"
#include "DatalogProgram.h"
#include "Graph.h"

class Interpreter {
   private:
    DatalogProgram datalog;
    Database database;
    int numPasses = 0;
    Graph forwardGraph;
    Graph reverseGraph;

   public:
    Interpreter(DatalogProgram d) {
        datalog = d;
        database = makeDatabase();
    }
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
        std::string ruleStr = toStringRule(index) + "\n";
        Rule rule = datalog.getRule(index);
        std::string newRelationName = rule.getHeadPredicateName();
        std::vector<Predicate> rHPredicates = rule.getPredicateList();
        std::vector<int> projectIndices;
        Relation* resultRelation = new Relation();

        for (size_t i = 0; i < rHPredicates.size(); i++) {
            if (i == 0) {
                resultRelation = evaluatePredicate(rHPredicates.at(i));
            } else {
                resultRelation = resultRelation->naturalJoin(evaluatePredicate(rHPredicates.at(i)), newRelationName);
            }
        }

        for (size_t i = 0; i < rule.getHeadPredicate().convertParams().size(); i++) {
            for (int j = 0; j < resultRelation->getHeader().getSize(); j++) {
                if (rule.getHeadPredicate().getParam(i) == resultRelation->getHeader().getName(j)) {
                    projectIndices.push_back(j);
                }
            }
        }
        resultRelation = resultRelation->project(projectIndices);
        resultRelation = resultRelation->rename(database.getHeader(newRelationName));
        ruleStr += database.getRelation(newRelationName)->unionize(resultRelation);
        return ruleStr;
    }
    std::string evaluateRules() {
        std::string rulesStr = optimizeRules();

        numPasses = 0;
        rulesStr += "Rule Evaluation\n";
        bool tuplesChanged = true;
        while (tuplesChanged) {
            size_t sizeBefore = 0;
            size_t sizeAfter = 0;
            // FIXME - ONLY LOOP THROUGH STRONGLY CONNECTED COMPONENTS
            for (size_t i = 0; i < datalog.getNumRules(); i++) {
                std::string relationName = datalog.getRule(i).getHeadPredicateName();
                sizeBefore += database.getRelationBodySize(relationName);
                rulesStr += evaluateRule(i);
                sizeAfter += database.getRelationBodySize(relationName);
            }
            if (sizeAfter == sizeBefore) {
                tuplesChanged = false;
            }
            numPasses++;
        }
        rulesStr += "\nSchemes populated after " + to_string(numPasses) + " passes through the Rules.\n\n";
        return rulesStr;
    }
    std::string interpret() {
        std::string interpretStr = "";
        interpretStr += evaluateRules();
        interpretStr += evaluateQueries();
        return interpretStr;
    }
    void buildGraphs() {
        // Initialize empty graphs based on size
        forwardGraph.addNodes(datalog.getNumRules());
        reverseGraph.addNodes(datalog.getNumRules());

        // Add dependencies
        for (size_t i = 0; i < datalog.getNumRules(); i++) {
            Rule rule = datalog.getRule(i);
            std::vector<Predicate> rHPredicates = rule.getPredicateList();
            for (size_t j = 0; j < rHPredicates.size(); j++) {
                for (size_t k = 0; k < datalog.getNumRules(); k++) {
                    Rule compareRule = datalog.getRule(k);
                    if (rule.getPredicateItemName(j) == compareRule.getHeadPredicateName()) {
                        forwardGraph.addEdge(i, k);
                        reverseGraph.addEdge(k, i);
                    }
                }
            }
        }
    }
    std::string optimizeRules() {
        buildGraphs();
        std::stack<int> postorder = reverseGraph.getPostorderDFSForest();
        std::vector<std::set<int>> sCCs = forwardGraph.findSCCsDFSForest(postorder);

        return forwardGraph.toString() + "\n";
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