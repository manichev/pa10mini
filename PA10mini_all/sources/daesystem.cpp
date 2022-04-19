#include "daesystem.h"


//ctor
DAESystem::DAESystem(void)
{
}


//dctor
DAESystem::~DAESystem(void)
{
    std::list<Expression*>::iterator it;
    for (it = equals.begin(); it != equals.end(); ++it)
        delete *it;
}


//add new variable to system
int DAESystem::addVariable(string& name_, bool isDerivative_)
{
    bool exists = false;
    std::list<Variable>::iterator it;
    if (name_.compare(string("t")) == 0)
        return 0;
    for (it = variables.begin(); it != variables.end(); ++it)
        if (it->name.compare(name_) == 0)
        {
            exists = true;
            break;
        }

    if (exists == true)
    {
        it->isDerivative |= isDerivative_;
        return it->id;
    }
    else
    {
        variables.push_back(Variable(name_, variables.size() + 1, isDerivative_));
        return variables.back().id;
    }
}

bool DAESystem::constantExists(string& name_, double& value_)
{
    std::list<Constant>::iterator it;
    for (it = constants.begin(); it != constants.end(); ++it)
        if (it->name.compare(name_) == 0)
        {
            value_ = it->value;
            return true;
        }
    return false;
}

void DAESystem::addConstant(string& name_, double value_)
{
    constants.push_back(Constant(name_, value_));
}

//get variable name
string DAESystem::getVariableName(int id_)
{
    std::list<Variable>::iterator it;
    for (it = variables.begin(); it != variables.end(); ++it)
        if (it->id == id_)
            return it->name;
    return "";
}

string DAESystem::getVariableDerivativeName(int id_)
{
    std::list<Variable>::iterator it;
    for (it = variables.begin(); it != variables.end(); ++it)
        if (it->id == id_)
            if (it->isDerivative)
                return it->name + "'";
    return "";
}

//add equal to system
void DAESystem::addEqual(Expression* equal)
{
    equals.push_back(equal);
}


void DAESystem::setInitial(string& name, double value)
{
    std::list<Variable>::iterator it;
    for (it = variables.begin(); it != variables.end(); ++it)
        if (it->name.compare(name) == 0)
            it->initial = value;
}


//sort variables
bool compareTypes(Variable first, Variable second)
{
    return first.isDerivative > second.isDerivative;
}
bool compareNames(Variable first, Variable second)
{
    return first.name < second.name;
}
//
void DAESystem::sortVariables()
{
    variables.sort(compareNames);
    variables.sort(compareTypes);
}


//count derivative
int DAESystem::countDerivatives()
{
    std::list<Variable>::iterator it;
    int count = 0;
    for (it = variables.begin(); it != variables.end(); ++it)
        if (it->isDerivative == true)
            ++count;
    return count;
}
//count variables
int DAESystem::countVariables()
{
    std::list<Variable>::iterator it;
    int count = 0;
    for (it = variables.begin(); it != variables.end(); ++it)
        ++count;
    return count;
}

int DAESystem::countEquals()
{
    return equals.size();
}


void DAESystem::updateExprIds(Expression* expr)
{
    if (expr!=0)
    {
        if (expr->type == _variable)
        {
            std::list<Variable>::iterator it;
            int count = 1;
            for (it = variables.begin(); it != variables.end(); ++it)
            {
                if (it->id == expr->id || it->id == -expr->id)
                {
                    expr->id = (expr->id<0)?-count:count;
                    break;
                }
                count++;
            }
        }
        updateExprIds(expr->getLeft());
        updateExprIds(expr->getRight());
    }
}


void DAESystem::updateAllIds()
{
    sortVariables();
    std::list<Expression*>::iterator eqIt;
    for (eqIt = equals.begin(); eqIt != equals.end(); ++eqIt)
    {
        updateExprIds(*eqIt);
    }
    std::list<Variable>::iterator it;
    int count = 1;
    for (it = variables.begin(); it != variables.end(); ++it)
    {
            it->id = count;
            count++;
    }
}
