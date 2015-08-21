#ifndef __EXPRESSION_HPP__ 
#define __EXPRESSION_HPP__ -356
#include <string>
#include <vector>

using namespace std;

class Expression {
  public:
    virtual ~Expression(){}
    virtual string toString() const = 0;
};

class ConstantNumber : public Expression {
public:
  ConstantNumber(string num)
  : _num(num)
  {}
  string toString() const ;
private:
  string _num;
};

class StringExpression : public Expression {
public:
  StringExpression(string s)
    :_string(s)
    {}
  virtual string toString() const;
protected:
  string _string;
};

class Variable : public Expression {
public:
  Variable (string varName)
  :_variable(varName)
  {}
  virtual string toString() const ;
protected:
  string _variable;
};

class BracketExpression : public Expression {
public:
  BracketExpression(Expression* expression)
  :_expression(expression)
  {}
  virtual string toString() const;
  ~BracketExpression(){
    delete _expression;
  }
protected:
  Expression* _expression;
};

class FunctionExpression : public Expression {
public:
	FunctionExpression(string name, vector<string*> list):
	_name(name),
	_list(list)
	{}
	virtual string toString() const;
protected:
	string _name;
	vector<string*> _list;	
};

class BinaryOperator : public Expression {
public:
  BinaryOperator(Expression *left, Expression *right)
  : _left(left), _right(right)
  {}
  ~BinaryOperator(){
    delete _left;
    delete _right;
  }
  BinaryOperator(const BinaryOperator& b);
protected:
  Expression* _left;
  Expression* _right;
};

class Addition : public BinaryOperator {
public:
  Addition(Expression *left, Expression* right)
  :BinaryOperator(left, right)
  {}
  string toString() const ;
private:
  Addition operator = (const Addition& p);  
};

class Subtraction : public BinaryOperator {
public:
  Subtraction(Expression *left, Expression* right)
  : BinaryOperator(left, right)
  {}
  string toString() const ;
private:
  Subtraction operator = (const Subtraction& p);
};

class Or : public BinaryOperator {
public:
  Or(Expression *left, Expression* right)
  : BinaryOperator(left, right)
  {}
  string toString() const ;
private:
  Or operator = (const Or& p);
};

class Multiplication : public BinaryOperator {
public:
  Multiplication(Expression *left, Expression* right)
  : BinaryOperator(left, right)
  {}
  string toString() const ;
private:
  Multiplication operator = (const Multiplication& p);
};

class Division : public BinaryOperator {
public:
  Division(Expression *left, Expression* right)
  : BinaryOperator(left, right)
  {}
  string toString() const ;
private:
  Division operator = (const Division& p);
};

class Div : public BinaryOperator {
public:
  Div(Expression *left, Expression* right)
  : BinaryOperator(left, right)
  {}
  string toString() const ;
private:
  Div operator = (const Div& p);
};

class And : public BinaryOperator {
public:
  And(Expression *left, Expression* right)
  : BinaryOperator(left, right)
  {}
  string toString() const ;
private:
  And operator = (const And& p);
};

class Mod : public BinaryOperator {
public:
  Mod(Expression *left, Expression* right)
  : BinaryOperator(left, right)
  {}
  string toString() const ;
private:
  Mod operator = (const Mod& p);
};

class LessThan : public BinaryOperator {
public:
  LessThan(Expression* left, Expression* right)
  : BinaryOperator(left, right)
  {}
  string toString() const ;
private:
  LessThan operator = (const LessThan& p);
};

class LessOrEqualThan : public BinaryOperator {
public:
  LessOrEqualThan(Expression* left, Expression* right)
  : BinaryOperator(left, right)
  {}
  string toString() const ;
private:
  LessOrEqualThan operator = (const LessOrEqualThan& p);
};

class GreaterThan : public BinaryOperator {
public:
  GreaterThan(Expression* left, Expression* right)
  : BinaryOperator(left, right)
  {}
  
  string toString() const ;
private:
  GreaterThan operator = (const GreaterThan& p);
};

class GreaterOrEqualThan : public BinaryOperator {
public:
  GreaterOrEqualThan(Expression* left, Expression* right)
  : BinaryOperator(left, right)
  {}
  string toString() const ;
private:
  GreaterOrEqualThan operator = (const GreaterOrEqualThan& p);
};

class Equal : public BinaryOperator {
public:
  Equal(Expression* left, Expression* right)
  : BinaryOperator(left, right)
  {}
  string toString() const ;
private:
  Equal operator = (const Equal& p);
};

class NotEqual : public BinaryOperator {
public:
  NotEqual(Expression* left, Expression* right)
  : BinaryOperator(left, right)
  {} 
  string toString() const ;
private:
  NotEqual operator = (const NotEqual& p);
};

#endif
