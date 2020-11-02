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

   public:
    Relation() {}
    Relation(std::string n) {
        name = n;
    }
    Relation(std::string n, Header h) {
        name = n;
        header = h;
    }
    Relation(std::string n, Header h, std::set<Tuple> b) {
        name = n;
        header = h;
        body = b;
    }
    void setHeader(Header h) {
        header = h;
    }
    void addTuple(Tuple newTuple) {
        body.insert(newTuple);
    }
    Header getHeader() const {
        return header;
    }
    std::set<Tuple> getBody() const {
        return body;
    }
    Relation* select(int column, std::string value) {
        Relation* newRelation = new Relation(name, header);

        for (Tuple row : body) {
            if (row.getValue(column) == value) {
                newRelation->addTuple(row);
            }
        }
        return newRelation;
    }
    Relation* select(int column1, int column2) {
        Relation* newRelation = new Relation(name, header);

        for (Tuple row : body) {
            if (row.getValue(column1) == row.getValue(column2)) {
                newRelation->addTuple(row);
            }
        }
        return newRelation;
    }
    Relation* rename(Header newHeader) {
        Relation* newRelation = new Relation(name, newHeader);
        for (Tuple row : body) {
            newRelation->addTuple(row);
        }
        return newRelation;
    }
    Relation* project(std::vector<int> columnsToKeep) {
        Relation* newRelation = new Relation(name);
        std::vector<std::string> vs;
        for (int i = 0; i < header.getSize(); i++) {
            for (size_t j = 0; j < columnsToKeep.size(); j++) {
                if (i == columnsToKeep.at(j)) {
                    vs.push_back(header.getName(columnsToKeep.at(j)));
                }
            }
        }
        Header newHeader(vs);
        newRelation->setHeader(newHeader);

        for (Tuple row : body) {
            std::vector<std::string> vs;
            for (int i = 0; i < header.getSize(); i++) {
                for (size_t j = 0; j < columnsToKeep.size(); j++) {
                    if (i == columnsToKeep.at(j)) {
                        vs.push_back(row.getValue(columnsToKeep.at(j)));
                    }
                }
            }
            newRelation->addTuple(Tuple(vs));
        }
        return newRelation;
    }
    std::string toString() const {
        std::string relationStr = "";
        for (Tuple row : body) {
            for (int i = 0; i < header.getSize(); i++) {
                if (i > 0) {
                    relationStr += ", ";
                }
                relationStr += header.getName(i) + "=\'" + row.getValue(i) + "\'";
            }
            relationStr += "\n";
        }
        return relationStr;
    }
};

#endif