#ifndef BOOLEANEXPRESSION_H
#define BOOLEANEXPRESSION_H

#include <iostream>
#include "ArithmeticExpression.h"

// This file is for classes that have to do with Boolean expressions

class BooleanExpression {
  // abstract class for a Boolean expression

 public:
  virtual ~BooleanExpression(){};
  virtual void print (std::ostream & o) const = 0;
  // pure virtual print function. Don't implement!
  virtual bool evaluate() const = 0;

};

// add below other classes that are needed
class IfEqual: public BooleanExpression {
public:
  IfEqual (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~IfEqual ();
  virtual void print(std::ostream & o) const;
  virtual bool evaluate() const;
private:
  ArithmeticExpression *_ae1, *_ae2;
};

class Greater: public BooleanExpression {
public:
  Greater (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Greater ();
  virtual void print(std::ostream & o) const;
  virtual bool evaluate() const;
private:
  ArithmeticExpression *_ae1, *_ae2;
};

class Less: public BooleanExpression {
public:
  Less (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Less ();
  virtual void print(std::ostream & o) const;
  virtual bool evaluate() const;
private:
  ArithmeticExpression *_ae1, *_ae2;
};

#endif