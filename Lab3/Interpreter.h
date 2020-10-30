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
        // datalog.getSchemes();
    }
    // DELETE NEW RELATIONS MADE

    // Algorithm

    // for each scheme ‘s’
    //      create a relation using name and parameter values from ‘s’
    // for each fact ‘f’
    //      make a tuple ‘t’ using the values from ‘f’
    //      add ‘t’ to relation with the same name as ‘f’
    // for each query ‘q’
    //      get the relation ‘r’ with the same name as the query ‘q’
    //      select for each constant in the query ‘q’
    //      select for each pair of matching variables in ‘q’
    //      project using the positions of the variables in ‘q’
    //      rename to match the names of variables in ‘q’
    //      print the resulting relation
};

#endif