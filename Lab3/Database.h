#ifndef DATABASE_H
#define DATABASE_H

#include <string>
using namespace std;

class Database {
   private:
    string value;

   public:
    Database(string paramVal) {
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