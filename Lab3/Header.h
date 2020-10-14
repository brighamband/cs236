#ifndef HEADER_H
#define HEADER_H

#include <string>
using namespace std;

class Header {
   private:
    string value;

   public:
    Header(string paramVal) {
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