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
    Relation* getRelation(std::string name) {
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