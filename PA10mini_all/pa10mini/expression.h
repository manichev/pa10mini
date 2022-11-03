#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

enum ContentType
{
    _variable,
    _constant,
    _operator,
    _function
};


enum Operator
{
    _plus,
    _minus,
    _division,
    _multiplication,
    _power
};


enum Function
{
    _ln,
    _sin,
    _cos
};


class Expression
{
public:
//ctors
    //void ctor
    Expression(void);

    //variable node ctor
    Expression(int id_);

    //constant node ctor
    Expression(double value_);

    //function node ctor
    Expression(Function fn_, Expression* left_ = nullptr, Expression* right_ = nullptr);

    //operator node ctor
    Expression(Operator op_, Expression* left_ = nullptr, Expression* right_ = nullptr);

    //dctor
    ~Expression(void);

//functions
    //return pointer to copy of source tree
    Expression* copy(void);

    //get derivative
    Expression* derivative(int id_);

    //simplify tree
    void simplify();

    //return left
    Expression* getLeft(void);

    //return right
    Expression* getRight(void);

    //set left
    void setRight(Expression* right_);

    //set right
    void setLeft(Expression* left_);

    bool isConst(double value_);

    bool isConst();

    void print_c_ostream(std::ostream& file, bool isBracketsNeeded = false);

//public data
    ContentType type;
    union {
        //variable id
        int id;
        //constant value
        double value;
        //operator id
        Operator op;
        //function id
        Function fn;
    };

//private data
private:
    Expression* left = nullptr;
    Expression* right = nullptr;

    void toConst(double value_);
    void toLeft();
    void toRight();

    //return pointer to derivative of src tree
    void getderivative(int id_);
};
