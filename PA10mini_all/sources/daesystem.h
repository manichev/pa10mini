#pragma once

#include <list>
#include <map>
#include <fstream>

#include "expression.h"

using namespace std;


//structure for system variable
struct Variable {
    //ctor
    Variable(){}
    Variable(string& name_, int id_, bool isDerivative_):
        name(name_), id(id_), isDerivative(isDerivative_), initial(0.0) {}

    string name;
    int id;
    bool isDerivative;
    double initial;
};

struct Constant {
    Constant(string& name_, double value_):
        name(name_), value(value_) {}
    string name;
    double value;
};


class DAESystem
{
public:
    //ctor
    DAESystem(void);

    //dctor
    ~DAESystem(void);

    //add new variable to system
    int addVariable(string& name_, bool isDerivative_);

    //true if constant exists
    bool constantExists(string& name_, double& value_);
    //add new constant
    void addConstant(string& name_, double value_);

    //get variable name
    std::string getVariableName(int id_);
    std::string getVariableDerivativeName(int id_);

    //add equal to system
    void addEqual(Expression* equal);

    //sort variables
    void sortVariables();

    //count derivative
    int countDerivatives();

    //count variables
    int countVariables();

    //count equals
    int countEquals();
    //
    void updateExprIds(Expression *);
    //test trash
    void updateAllIds();
    void setInitial(string& name, double value);

public:
    //list of equals
    std::list <Expression*> equals;
    //list of variables
    std::list <Variable> variables;
    std::list <Constant> constants;
    //start values
    std::map <int, double> startValues;
};
