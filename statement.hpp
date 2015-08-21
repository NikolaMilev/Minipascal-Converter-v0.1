#ifndef __STATEMENT_HPP__
#define __STATEMENT_HPP__ 1

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "expression.hpp"

class Drawable {
public:
  virtual void draw() const = 0; 
  virtual int leftWidth() const = 0;
  virtual int rightWidth() const = 0;
  virtual ~Drawable() {}
};

extern int lastDrawnNode;
extern int numNodes;

class Statement : public Drawable{
public:
  virtual void draw() const = 0;
  virtual int leftWidth() const = 0;
  virtual int rightWidth() const = 0;
  virtual ~Statement() {

  }
};

class Assignment : public Statement {
public:
  Assignment(string s, Expression *i)
    :_s(s), _expression(i)
  {}
  void draw() const ;
  int leftWidth() const ;
  int rightWidth() const ;
  ~Assignment() {
    delete _expression;
  }
  string _s;
  Expression *_expression;
private:
  Assignment operator = (const Assignment& n);
  Assignment(const Assignment& n);
};

class OutputStatement : public Statement {
public:
  OutputStatement(Expression *i)
    :_expression(i)
  {}
  void draw() const ;
  int leftWidth() const ;
  int rightWidth() const ;
  ~OutputStatement () {
    delete _expression;
  }
private:
  OutputStatement operator = (const OutputStatement& n);
  OutputStatement(const OutputStatement& n);
  Expression *_expression;
};

class InputStatement : public Statement {
public:
  InputStatement(Expression *variable)
    :_variable(variable)
  {}
  ~InputStatement(){
    delete _variable;
  }
  void draw() const ;
  int leftWidth() const ;
  int rightWidth() const ;
private:
  InputStatement operator = (const InputStatement& n);
  InputStatement(const InputStatement& n);
  Expression *_variable;
};

class EmptyStatement : public Statement {
public:
  EmptyStatement()
  {}
  void draw() const ;
  int leftWidth() const ;
  int rightWidth() const ;
private:
  private:
  EmptyStatement operator = (const EmptyStatement& n);
  EmptyStatement(const EmptyStatement& n);
};

class BlockStatement : public Statement {
public:
  BlockStatement(vector<Statement *> *vec)
    :_vec(vec)
  {}
  void draw() const ;
  int leftWidth() const ;
  int rightWidth() const ;
  ~BlockStatement() {
    vector<Statement *>::iterator i;
    for (i = _vec->begin(); i!=_vec->end(); i++)
      delete(*i);
    delete _vec;
  }
private:
  BlockStatement operator = (const BlockStatement& n);
  BlockStatement(const BlockStatement& n);
  vector<Statement *> *_vec;
};

class IfThenStatement : public Statement {
public:
  IfThenStatement(Expression *i, Statement *n1)
    :_condition(i), _then_statement(n1)
  {}
  void draw() const ;
  int leftWidth() const ;
  int rightWidth() const ;
  ~IfThenStatement () {
    delete _condition;
    delete _then_statement;
  }
private:
  IfThenStatement operator = (const IfThenStatement& i);
  IfThenStatement(const IfThenStatement& i);
  Expression *_condition;
  Statement *_then_statement;
};

class IfThenElseStatement : public Statement {
public:
  IfThenElseStatement(Expression *i, Statement *n1, Statement *n2)
    :_condition(i), _then_statement(n1), _else_statement(n2)
  {}
  void draw() const ;
  int leftWidth() const ;
  int rightWidth() const ;
  ~IfThenElseStatement () {
    delete _condition;
    delete _then_statement;
    delete _else_statement;
  }
private:
  IfThenElseStatement operator = (const IfThenElseStatement& i);
  IfThenElseStatement(const IfThenElseStatement& i);
  Expression *_condition;
  Statement *_then_statement;
  Statement *_else_statement;
};

class WhileStatement : public Statement {
public:
  WhileStatement(Expression *i, Statement *n)
    :_condition(i), _loop(n)
  {}
  void draw() const ;
  int leftWidth() const ;
  int rightWidth() const ;
  ~WhileStatement () {
    delete _condition;
    delete _loop;
  }
private:
  WhileStatement operator = (const WhileStatement& w);
  WhileStatement(const WhileStatement& w);
  Expression *_condition;
  Statement *_loop;
};

class ForToStatement : public Statement {
public:
  ForToStatement(Assignment *begin_assignment, Expression *final_expression, Statement *loop)
  :_begin_assignment(begin_assignment),
   _final_expression(final_expression),
   _loop(loop)
   {}
   ~ForToStatement(){
     delete _begin_assignment;
     delete _final_expression;
     delete _loop;
   }
  void draw() const ;
  int leftWidth() const ;
  int rightWidth() const ;
private:
  ForToStatement operator = (const ForToStatement& w);
  ForToStatement(const ForToStatement& w);
  Assignment *_begin_assignment;
  Expression *_final_expression;
  Statement *_loop;
};

class ForDownToStatement : public Statement {
public:
  ForDownToStatement(Assignment *begin_assignment, Expression *final_expression, Statement *loop)
  :_begin_assignment(begin_assignment),
   _final_expression(final_expression),
   _loop(loop)
   {}
   ~ForDownToStatement(){
     delete _begin_assignment;
     delete _final_expression;
     delete _loop;
   }
  void draw() const ;
  int leftWidth() const ;
  int rightWidth() const ;
private:
  ForDownToStatement operator = (const ForDownToStatement& w);
  ForDownToStatement(const ForDownToStatement& w);
  Assignment *_begin_assignment;
  Expression *_final_expression;
  Statement *_loop;
};

class RepeatUntilStatement : public Statement {
public:
  RepeatUntilStatement(vector<Statement*> *statementSequence, Expression *i)
    :_condition(i), _statementSequence(statementSequence)
  {}
  void draw() const ;
  int leftWidth() const ;
  int rightWidth() const ;
  ~RepeatUntilStatement () {
    delete _condition;
    vector<Statement*>::iterator i;
    for (i = _statementSequence->begin(); i!=_statementSequence->end(); i++)
      delete (*i);
    delete _statementSequence;
  }
private:
  RepeatUntilStatement operator = (const RepeatUntilStatement& r);
  RepeatUntilStatement(const RepeatUntilStatement& r);
  Expression *_condition;
  vector<Statement*> *_statementSequence;
};

#endif