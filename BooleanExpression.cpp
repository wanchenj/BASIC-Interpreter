#include "BooleanExpression.h"

//IfEqual
IfEqual::IfEqual (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

IfEqual::~IfEqual ()
{
  delete _ae1;
  delete _ae2;
}
  
void IfEqual::print (std::ostream & o) const
{
  o << "[";
  _ae1->print (o);
  o << " = ";
  _ae2->print (o);
  o << "]";
}
bool IfEqual::evaluate() const{
  if (_ae1->evaluate() == _ae2->evaluate()) return true;
  return false;
}

//Greater
Greater::Greater (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Greater::~Greater ()
{
  delete _ae1;
  delete _ae2;
}
  
void Greater::print (std::ostream & o) const
{
  o << "[";
  _ae2->print (o);
  o << " < ";
  _ae1->print (o);
  o << "]";
}
bool Greater::evaluate() const{
  //cout << "Hit Greater Evaluate ()" << endl;
  if (_ae1->evaluate() > _ae2->evaluate()){
    //cout << "Greater is true" << endl;
    return true;
  }
  return false;
}

//Less
Less::Less (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Less::~Less ()
{
  delete _ae1;
  delete _ae2;
}
  
void Less::print (std::ostream & o) const
{
  o << "[";
  _ae1->print (o);
  o << " < ";
  _ae2->print (o);
  o << "]";
}
bool Less::evaluate() const{
  if (_ae1->evaluate() < _ae2->evaluate()){
    return true;
  }
  return false;
}
