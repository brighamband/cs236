#ifndef RELATION_H
#define RELATION_H

#include <string>
using namespace std;

class Relation {
   private:
    string value;

   public:
    Relation(string paramVal) {
        value = paramVal;
    }
    void setValue(string paramVal) {
        value = paramVal;
    }
    string toString() const {
        return value;
    }
};

#endif