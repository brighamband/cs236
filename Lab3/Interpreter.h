#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Database.h"
#include "DatalogProgram.h"

class Interpreter {
   private:
    DatalogProgram datalog;
    Database database;

   public:
    Interpreter(DatalogProgram d) {
        datalog = d;
        //  Makes a Database using the schemes and the facts, and stores it as a data member
    }
};

#endif