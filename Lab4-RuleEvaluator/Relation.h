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
    void addTuple(Tuple newTuple) {
        body.insert(newTuple);
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
        for (int i = 0; i < header.getSize(); i++) {
            for (size_t j = 0; j < columnsToKeep.size(); j++) {
                if (i == columnsToKeep.at(j)) {
                    vs.push_back(header.getName(columnsToKeep.at(j)));
                }
            }
        }
        Header newHeader(vs);
        relation->setHeader(newHeader);

        for (Tuple row : body) {
            std::vector<std::string> vs;
            for (int i = 0; i < header.getSize(); i++) {
                for (size_t j = 0; j < columnsToKeep.size(); j++) {
                    if (i == columnsToKeep.at(j)) {
                        vs.push_back(row.getValue(columnsToKeep.at(j)));
                    }
                }
            }
            relation->addTuple(Tuple(vs));
        }
        return relation;
    }
    void unionize(Relation relation) {  // SHOULD THAT BE A POINTER?
        }
    // Relation* naturalJoin() {
    //     for (Tuple t1 : r1) {
    //         for (Tuple t2 : r2) {
    //             if (joinable(t1, t2)) {
    //                 cout << "found a joinable pair" << endl;
    //             }
    //         }
    //     }
    // }
    std::string toString() const {
        std::string relationStr = "";
        for (Tuple row : body) {
            for (int i = 0; i < header.getSize(); i++) {
                if (i > 0) {
                    relationStr += ", ";
                }
                relationStr += "  " + header.getName(i) + "=" + row.getValue(i);
            }
            relationStr += "\n";
        }
        return relationStr;
    }
};

#endif