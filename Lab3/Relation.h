#ifndef RELATION_H
#define RELATION_H

#include <set>
#include <string>

#include "Header.h"
#include "Tuple.h"

class Relation {
   private:
    std::string name;
    Header header;
    std::set<Tuple> body;

   public:
    Relation(std::string n, Header h) {
        name = n;
        header = h;
    }
    void addTuple(Tuple newTuple) {
        body.insert(newTuple);
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
    // The rename operation changes the header of the relation. The resulting relation has the same tuples as the original.
    //  Replacing the entire list of attributes is easier and avoids issues with name conflicts.
    Relation* rename(Header newHeader) {
        Relation* newRelation = new Relation(name, newHeader);
        for (Tuple row : body) {
            newRelation->addTuple(row);
        }
        return newRelation;
    }
    //  The project operation changes the number and order of columns in a relation. The resulting relation may have either the same number or fewer columns. Project changes the header and all the tuples in the relation.
    //  The parameter to the project function could be a list of the positions of the columns that should be included in the result.
    Relation* project() {
        Relation* newRelation = new Relation(name, header);
        return newRelation;
    }
    std::string toString() const {
        std::string relationStr = "";
        for (Tuple row : body) {
            for (size_t i = 0; i < header.getSize(); i++) {
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