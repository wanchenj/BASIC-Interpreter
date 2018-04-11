#include <sstream>
#include "ArithmeticExpression.h"

//ADDITION
Addition::Addition (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Addition::~Addition ()
{
  delete _ae1;
  delete _ae2;
}
  
void Addition::print (std::ostream & o)
{
    o << "(";
    _ae1->print (o);
    o << " + ";
    _ae2->print (o);
    o << ")";
}
int Addition::evaluate () const{
  return _ae1->evaluate() + _ae2->evaluate();
}

//SUBSTRACTION
Subtraction::Subtraction (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Subtraction::~Subtraction ()
{
  delete _ae1;
  delete _ae2;
}
  
void Subtraction::print (std::ostream & o)
{
  o << "(";
  _ae1->print (o);
  o << " - ";
  _ae2->print (o);
  o << ")";
}
int Subtraction::evaluate () const{
  return _ae1->evaluate() - _ae2->evaluate();
}

//MULTIPLICATION
Multiplication::Multiplication (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Multiplication::~Multiplication ()
{
  delete _ae1;
  delete _ae2;
}
  
void Multiplication::print (std::ostream & o) 
{
  o << "(";
  _ae1->print (o);
  o << " * ";
  _ae2->print (o);
  o << ")";
}
int Multiplication::evaluate () const{
  return _ae1->evaluate() * _ae2->evaluate();
}

//DIVISION
Division::Division (ArithmeticExpression *ae1, ArithmeticExpression *ae2, int lineNumber)
{
    _ae1 = ae1;
    _ae2 = ae2;
    _lineNumber = lineNumber;
}

Division::~Division ()
{
  delete _ae1;
  delete _ae2;
}
  

void Division::print (std::ostream & o)
{
    o << "(";
    _ae1->print (o);
    o << " / ";
    _ae2->print (o);
    o << ")";
}

int Division::evaluate () const throw(int)
{
  if (_ae2->evaluate() == 0)
  {
      cout << "Error in Line " << to_string(_lineNumber) << ": Division by 0: ";
      _ae1->print(std::cout);
      cout << " = " << to_string(_ae1->evaluate());
      cout << ", ";
      _ae2->print(std::cout);
      cout << " = 0." << endl;

      throw -1;
  }  

  return _ae1->evaluate() / _ae2->evaluate();
}

//Constant
Constant::Constant (int Number)
{
  _Number = Number;
}
Constant::~Constant ()
{
}

void Constant::print (std::ostream & o) 
{
  o << _Number;
}
int Constant::evaluate () const{
  return _Number;
}

//Variable Do i need another one for ArrayVariables???????????
Variable::Variable (string VariableName, map<string,int> *MapVariable)
{
  _VariableName = VariableName;
  _MapVariable = MapVariable;
  //how to implement this part??????????????????????????????
}

Variable::~Variable ()
{
  //delete _VariableName;
}
  
void Variable::print (std::ostream & o) 
{
  o << _VariableName;
}
int Variable::evaluate () const{
  map<string,int>::iterator it;
  it = _MapVariable -> find(_VariableName);
  if(it != _MapVariable -> end())
  {
    return it -> second;
  }
  return 0;
}

void Variable::setValue (int value){
  map<string,int>::iterator it;
  it = _MapVariable -> find(_VariableName);
  if(it != _MapVariable -> end())
  {
    it -> second = value;
    return;
  }
  _MapVariable -> insert(pair<string,int>(_VariableName,value));
  return;
}

//ArrayVariable
ArrayVariable::ArrayVariable (string ArrayName, ArithmeticExpression *ae, map<string,int> *MapArrayVariable)
{
  _ArrayName = ArrayName;
  _ae = ae;
  _MapArrayVariable = MapArrayVariable;
}

ArrayVariable::~ArrayVariable ()
{
  delete _ae;
}
  
void ArrayVariable::print (std::ostream & o) 
{
  o << _ArrayName << "[";
  _ae->print (o);
  o << "]";
}
int ArrayVariable::evaluate () const{
  int tem = _ae->evaluate();
  stringstream ss;
  ss << tem;
  string valueString = ss.str();
  string _key = _ArrayName + "[" + valueString  + "]";

  map<string,int>::iterator it;
  it =_MapArrayVariable -> find(_key);
  if(it != _MapArrayVariable -> end())
  {
    return it->second;
  }
  return 0;
}

void ArrayVariable::setValue (int value){
  int tem = _ae->evaluate();
  stringstream ss;
  ss << tem;
  string valueString = ss.str();
  string _key = _ArrayName + "[" + valueString  + "]";

  map<string,int>::iterator it;
  it = _MapArrayVariable -> find(_key);
  if(it != _MapArrayVariable -> end())
  {
    it -> second = value;
    return;
  }
  _MapArrayVariable -> insert(pair<string,int>(_key,value));
  return;
}
