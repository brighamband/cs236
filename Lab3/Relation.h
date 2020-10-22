#ifndef RELATION_H
#define RELATION_H

#include <set>

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

    // FIXME -- MAKE SURE TO RETURN **NEW** RELATION
    // Relation* select(stuff){
    // Relation toReturn(stuff);
    // return &toReturn;

    // The select operation does not change the header of the relation. The header of the relation resulting from the select is the same as the header of the original relation.

    //  One version of select finds all the tuples that have a constant value in a certain column.
    //  This select function could take two parameters, a position and a value. The given position in a tuple would need to have a value equal to the given value for that tuple to be included
    Relation* selectValue() {}
    //  Another version of select finds all the tuples that have the same value in two different columns (it doesn't matter what the value is, as long as both columns have the same value).

    //  This select function could take two parameters that are both positions. The two given positions in a tuple would need to have equal values for that tuple to be included in the result.
    Relation* selectIndex() {}
    //  The project operation changes the number and order of columns in a relation. The resulting relation may have either the same number or fewer columns. Project changes the header and all the tuples in the relation.

    //  The parameter to the project function could be a list of the positions of the columns that should be included in the result.
    Relation* project() {}
    // The rename operation changes the header of the relation. The resulting relation has the same tuples as the original.

    //  Should rename change one attribute at a time, or replace the entire list of attributes at once?
    //  Replacing the entire list of attributes is easier and avoids issues with name conflicts.
    Relation* rename(std::vector<std::string> newHeader) {
        Relation newRelation(name, newHeader);
        // newRelation.addTuple(body);  // FIXME - Make sure to add back body to new relation
        return &newRelation;
    }

    std::string toString() const {
        std::string relationStr = "";
        // also print header
        for (Tuple row : body) {
            relationStr += row.toString();
        }
        return relationStr;
        // for (auto it = s.begin(); it != s.end(); it++)
        //     cout << *it << " ";
        // }
    }
};

#endif