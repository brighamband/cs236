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

    Relation* selectValue() {}
    Relation* selectIndex() {}
    Relation* project() {}
    Relation* rename(std::vector<std::string> newHeader) {}

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