#ifndef RELATION_H
#define RELATION_H

#include <set>
#include <string>
#include <vector>

#include "Header.h"
#include "Tuple.h"

class Relation {
   private:
    std::string name;
    Header header;
    std::set<Tuple> body;
    bool showResults = false;

   public:
    Relation() {}
    Relation(std::string n) {
        name = n;
    }
    Relation(std::string n, Header h) {
        name = n;
        header = h;
    }
    void setHeader(Header h) {
        header = h;
    }
    bool addTuple(Tuple newTuple) {
        return body.insert(newTuple).second;
    }
    void setShowResults(bool sr) {
        showResults = sr;
    }
    bool getShowResults() {
        return showResults;
    }
    Header getHeader() const {
        return header;
    }
    std::set<Tuple> getBody() const {
        return body;
    }
    size_t getBodySize() const {
        return body.size();
    }
    Relation* select(int column, std::string value) {
        Relation* relation = new Relation(name, header);

        for (Tuple row : body) {
            if (row.getValue(column) == value) {
                relation->addTuple(row);
            }
        }
        return relation;
    }
    Relation* select(int column1, int column2) {
        Relation* relation = new Relation(name, header);

        for (Tuple row : body) {
            if (row.getValue(column1) == row.getValue(column2)) {
                relation->addTuple(row);
            }
        }
        return relation;
    }
    Relation* rename(Header newHeader) {
        Relation* relation = new Relation(name, newHeader);
        for (Tuple row : body) {
            relation->addTuple(row);
        }
        relation->setShowResults(true);
        return relation;
    }
    Relation* project(std::vector<int> columnsToKeep) {
        Relation* relation = new Relation(name);
        std::vector<std::string> vs;
        for (size_t i = 0; i < columnsToKeep.size(); i++) {
            for (int j = 0; j < header.getSize(); j++) {
                if (j == columnsToKeep.at(i)) {
                    vs.push_back(header.getName(columnsToKeep.at(i)));
                }
            }
        }
        Header newHeader(vs);
        relation->setHeader(newHeader);

        for (Tuple row : body) {
            std::vector<std::string> vs;
            for (size_t i = 0; i < columnsToKeep.size(); i++) {
                for (int j = 0; j < header.getSize(); j++) {
                    if (j == columnsToKeep.at(i)) {
                        vs.push_back(row.getValue(columnsToKeep.at(i)));
                    }
                }
            }
            relation->addTuple(Tuple(vs));
        }
        return relation;
    }
    void unionize(Relation* resultRelation) {  // REMOVE THE & IF THERE'S ISSUES
        std::set<Tuple> resultBody = resultRelation->getBody();
        for (Tuple row : resultBody) {
            if (addTuple(row)) {
                std::cout << rowToString(row);
            }
        }
    }
    Header joinHeaders(Header resultHeader, Header headerToJoin, std::vector<int>& vi) {
        bool alreadyExists = false;
        for (int i = 0; i < headerToJoin.getSize(); i++) {
            alreadyExists = false;
            for (int j = 0; j < resultHeader.getSize(); j++) {
                if (headerToJoin.getName(i) == resultHeader.getName(j)) {
                    alreadyExists = true;
                    vi.push_back(j);
                }
            }
            if (!alreadyExists) {
                resultHeader.addName(headerToJoin.getName(i));
                vi.push_back(resultHeader.getSize() - 1);
            }
        }
        return resultHeader;
    }
    bool isJoinable(Tuple resultRow, Tuple rowToJoin, std::vector<int> vi) {
        for (size_t i = 0; i < vi.size(); i++) {
            if (vi.at(i) < resultRow.getSize()) {
                if (resultRow.getValue(vi.at(i)) != rowToJoin.getValue(i)) {
                    return false;
                }
            }
        }
        return true;
    }
    Tuple joinTuples(Tuple resultRow, Tuple rowToJoin, std::vector<int> vi) {
        for (size_t i = 0; i < vi.size(); i++) {
            if (vi.at(i) > (resultRow.getSize() - 1)) {
                resultRow.pushToTuple(rowToJoin.getValue(i));
            }
        }
        return resultRow;
    }
    Relation* naturalJoin(Relation* relationToJoin, std::string newName) {
        std::vector<int> vi;
        Header newHeader = joinHeaders(header, relationToJoin->getHeader(), vi);
        Relation* relation = new Relation(newName, newHeader);
        for (Tuple row : body) {
            for (Tuple joinRow : relationToJoin->getBody()) {
                if (isJoinable(row, joinRow, vi)) {
                    Tuple newTuple = joinTuples(row, joinRow, vi);
                    relation->addTuple(newTuple);
                }
            }
        }
        return relation;
    }
    std::string rowToString(Tuple row) const {
        std::string rowStr = "";
        for (int i = 0; i < header.getSize(); i++) {
            if (i > 0) {
                rowStr += ", ";
            }
            rowStr += "  " + header.getName(i) + "=" + row.getValue(i);
        }
        rowStr += "\n";
        return rowStr;
    }
    std::string toString() const {
        std::string relationStr = "";
        for (Tuple row : body) {
            relationStr += rowToString(row);
        }
        return relationStr;
    }
};

#endif