#include "expression.hpp"

using namespace std;

extern int yyerror(string s);

string Variable::toString() const {
  return string(_variable);
}

string BracketExpression::toString() const {
  return "(" + string(_expression->toString()) + ")";
}

string FunctionExpression::toString() const {
	string s(_name);
	s.append("(");
	if(_list.size()==0){
		unsigned i;
		for(i=0; i < _list.size() - 1; i++){
			s.append(*(_list[i]));
			s.append(",");
		}
		s.append(*(_list[i]));
	}
	s.append(")");
	return s;
}

string ConstantNumber::toString() const {
  return string(_num);
}

string StringExpression::toString() const {
  return string(_string);
}

string Multiplication::toString() const {
  return string(_left->toString()) + " * " + string(_right->toString()); 
}

string Addition::toString() const {
  return string(_left->toString()) + " + " + string(_right->toString()); 
}

string Subtraction::toString() const {
  return string(_left->toString()) + " - " + string(_right->toString()); 
}

string Or::toString() const {
  return string(_left->toString()) + " OR " + string(_right->toString()); 
}

string Division::toString() const {
  return string(_left->toString()) + " / " + string(_right->toString()); 
}

string Div::toString() const {
  return string(_left->toString()) + " DIV " + string(_right->toString()); 
}

string And::toString() const {
  return string(_left->toString()) + " AND " + string(_right->toString()); 
}

string Mod::toString() const {
  return string(_left->toString()) + " MOD " + string(_right->toString()); 
}

string LessOrEqualThan::toString() const {
  return string(_left->toString()) + " <= " + string(_right->toString()); 
}

string GreaterThan::toString() const {
  return string(_left->toString()) + " > " + string(_right->toString()); 
}
string LessThan::toString() const {
  return string(_left->toString()) + " < " + string(_right->toString()); 
}

string GreaterOrEqualThan::toString() const {
  return string(_left->toString()) + " >= " + string(_right->toString()); 
}

string Equal::toString() const {
  return string(_left->toString()) + " = " + string(_right->toString()); 
}

string NotEqual::toString() const {
  return string(_left->toString()) + " <> " + string(_right->toString()); 
}
