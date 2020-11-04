#ifndef DATABASE_H
#define DATABASE_H

#include <map>

#include "Relation.h"

class Database {
   private:
    std::map<std::string, Relation*> db;

   public:
    Database() {}
    Database(std::map<std::string, Relation*> d) {
        db = d;
    }
    // ONLY USE FOR Database in Project 3 -- Look up a relation when you are given the relation's name
    Relation* getRelation(std::string name) {  // FIXME - Should this be *pointer?  Should this be const?
        Relation* relPtr = db[name];
        return relPtr;
    }
    Header getHeader(std::string name) {
        Relation* relPtr = db[name];
        return relPtr->getHeader();
    }
    std::set<Tuple> getBody(std::string name) {
        Relation* relPtr = db[name];
        return relPtr->getBody();
    }
};

#endif