#include "expression.h"
#include <cmath>
#include <limits>

//static const double DOUBLE_EPS = 1e-32;
auto DOUBLE_EPS = std::numeric_limits<double>::min();

//void ctor
Expression::Expression(void):left(0), right(0) {}


//variable node ctor
Expression::Expression(int id_):
type(_variable), id(id_), left(0), right(0) {};


//constant node ctor
Expression::Expression(double value_):
type(_constant), value(value_), left(0), right(0) {};


//function node ctor
Expression::Expression(Function fn_, Expression* left_, Expression* right_):
type(_function), fn(fn_), left(left_), right(right_) {};


//operator node ctor
Expression::Expression(Operator op_, Expression* left_, Expression* right_):
type(_operator), op(op_), left(left_), right(right_) {};


//dctor
Expression::~Expression(void)
{
    if(left)
        delete left;
    if(right)
        delete right;
}


//return pointer to copy of source tree
Expression* Expression::copy(void)
{
    Expression* tmp = 0;
    tmp = new Expression;
    *tmp = *this;
    if(left != 0)
        tmp->left = left->copy();
    if(right != 0)
        tmp->right = right->copy();
    return tmp;
}


Expression* Expression::derivative(int id_)
{
    Expression* tmp = copy();
    tmp->getderivative(id_);
    tmp->simplify();
    return tmp;
}


//return pointer to derivative of src tree
void Expression::getderivative(int id_)
{
    switch(type)
    {
    case _variable:
            type = _constant;
            value = (id == id_) ? 1.0 : 0.0;
    break;
    case _constant:
            value = 0;
    break;
    case _operator:
            switch(op)
            {
            case _plus:
            case _minus:
                {
                    if(left != 0)
                        left->getderivative(id_);
                    if(right != 0)
                        right->getderivative(id_);
            break;
                }
            case _multiplication:
                {
                    op = _plus;

                    Expression* tmp1 = new Expression(_multiplication, left->copy(), right->copy());
                    tmp1->left->getderivative(id_);

                    Expression* tmp2 = new Expression(_multiplication, left, right);
                    tmp2->right->getderivative(id_);

                    left = tmp1;
                    right = tmp2;
                    break;
                }
            case _division:
                {
                    Expression* tmp1 = new Expression(_multiplication, left->copy(), right->copy());
                    tmp1->left->getderivative(id_);

                    Expression* tmp2 = new Expression(_multiplication, left, right);
                    tmp2->right->getderivative(id_);

                    left = new Expression(_minus, tmp1, tmp2);

                    right = new Expression(_multiplication, right->copy(), right->copy());
                    break;
                }
            case _power:
                {
                    op = _multiplication;
                    Expression* tmp1 = new Expression(_power, left, right);
                    if(type == _constant && value != 1)
                    {
                        left = new Expression(right->value - 1);
                        right = tmp1;
                    }
                    else
                    {
                        left = tmp1;
                        right = new Expression(_plus);

                        tmp1 = new Expression(_multiplication);
                        tmp1->left = left->right->copy();
                        tmp1->left->getderivative(id_);
                        tmp1->right = new Expression(_ln);
                        tmp1->right->left = left->left->copy();

                        right->left = tmp1;

                        tmp1 = new Expression(_multiplication);
                        tmp1->left = left->right->copy();
                        tmp1->right = new Expression(_division);
                        tmp1->right->left = left->left->copy();
                        tmp1->right->left->getderivative(id_);
                        tmp1->right->right = left->left->copy();

                        right->right = tmp1;
                    }
                    break;
                }
            }
            break;
        case _function:
            switch(fn)
            {
            case _ln:
                right = copy();
                left = copy();
                left->getderivative(id_);
                type = _operator;
                op = _division;
                fn = _sin;
                break;
            case _sin:
                left = copy();
                right = left->left->copy();
                right->getderivative(id_);
                type = _operator;
                op = _multiplication;
                left->fn = _cos;
                break;
            case _cos:
                left =  new Expression(_multiplication, new Expression(-1.0), copy());
                left->right->fn = _sin;
                right = left->right->left->copy();
                right->getderivative(id_);
                type = _operator;
                op = _multiplication;
                break;
            }
            break;
    }
}


//simplify tree
void Expression::simplify()
{
    if(left != 0)
        left->simplify();
    if(right != 0)
        right->simplify();
    if(type == _operator)
    {
        switch(op)
        {
        case _plus:
            if(left->type == _constant && right->type == _constant)
                toConst(left->value + right->value);
            else if(left->isConst(0.0)) //0 + a = 0
                toRight();
            else if(right->isConst(0.0)) //a + 0 = 0
                toLeft();
            break;
        case _minus:
            if(left->type == _constant && right->type == _constant)
                toConst(left->value - right->value);
            else if(right->isConst(0.0)) //a - 0 = 0;
                toLeft();
            else if(left->isConst(0.0)) //0 - a = -1 * a
            {
                op = _multiplication;
                left->toConst(-1.0);
            }
            break;
        case _multiplication:
            if(left->type == _constant && right->type == _constant)
                toConst(left->value * right->value);
            else if(left->isConst(0.0))
                toLeft();
            else if(right->isConst(0.0)) //a * 0 = 0 * a = 0
                toRight();
            else if(left->isConst(1.0)) //a * 1 = a;
                toRight();
            else if(right->isConst(1.0)) //1 * a = a;
                toLeft();
            break;
        case _division:
            if(left->type == _constant && right->type == _constant)
                toConst(left->value / right->value);
            else if(left->isConst(0.0)) //0 / a = 0
                toConst(0.0);
            else if(right->isConst(1.0)) //a / 1 = a
                toRight();
            break;
        case _power:
            if(left->type == _constant && right->type == _constant)
                toConst(pow(left->value, right->value));
            if(right->isConst(0.0)) //a ^ 0 = 1
                toConst(1.0);
            else if(right->isConst(0.0)) //a ^ 1 = a
                toRight();
            break;
        }
    }
}

void Expression::toRight()
{
    Expression* tmp = right;
    *this = *right;
    tmp->left = nullptr;
    tmp->right = nullptr;
    delete tmp;
}

void Expression::toLeft()
{
    Expression* tmp = left;
    *this = *left;
    tmp->left = nullptr;
    tmp->right = nullptr;
    delete tmp;
}

bool Expression::isConst(double value_)
{
    return type == _constant && fabs(value - value_) < DOUBLE_EPS;
}

bool Expression::isConst()
{
    return type == _constant;
}


void Expression::toConst(double value_)
{
    delete left;
    delete right;
    left = nullptr;
    right = nullptr;
    type = _constant;
    value = value_;
}


//return left
Expression* Expression::getLeft(void)
{
    return left;
}


//return right
Expression* Expression::getRight(void)
{
    return right;
}


//set left
void Expression::setRight(Expression* right_)
{
    right = right_;
}


//set right
inline void Expression::setLeft(Expression* left_)
{
    left = left_;
}

//ostream& operator << (ostream& ostr, const Expression& expr)
//{
//}

void Expression::print_c_ostream(ostream& ostr, bool isBracketsNeeded)
{
    switch(type)
    {
    case _variable:
        if(id < 0)
            ostr << "px[" << -id << "]";
        else if (id > 0)
            ostr << "z[" << id << "]";
        else
            ostr << "t";
        break;
    case _constant:
        if(value < 0 && isBracketsNeeded)
            ostr << "(" << value << ")";
        else
            ostr << value;
        break;
    case _operator:
        switch(op)
        {
            case _plus:
                if(isBracketsNeeded)
                    ostr << "(";
                left->print_c_ostream(ostr);
                ostr << "+";
                right->print_c_ostream(ostr, true);
                if(isBracketsNeeded)
                    ostr << ")";
                break;
            case _minus:
                if(isBracketsNeeded)
                    ostr << "(";
                left->print_c_ostream(ostr);
                ostr << "-";
                right->print_c_ostream(ostr, true);
                if(isBracketsNeeded)
                    ostr << ")";
                break;
            case _multiplication:
                left->print_c_ostream(ostr, true);
                ostr << "*";
                right->print_c_ostream(ostr, true);
                break;
            case _division:
                left->print_c_ostream(ostr, true);
                ostr << "/";
                right->print_c_ostream(ostr, true);
                break;
            case _power:
                ostr << "pow(";
                left->print_c_ostream(ostr, true);
                ostr << ", ";
                right->print_c_ostream(ostr, true);
                ostr << ")";
                break;
        }
        break;
    case _function:
        switch(fn)
        {
            case _ln:
                ostr << "log(";
                break;
            case _sin:
                ostr << "sin(";
                break;
            case _cos:
                ostr << "cos(";
                break;
        }
        left->print_c_ostream(ostr);
        ostr << ")";
        break;
    }
}
