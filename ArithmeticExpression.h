#ifndef ARITHMETICEXPRESSION_H
#define ARITHMETICEXPRESSION_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

// This file is for classes that have to do with arithmetic expressions

class ArithmeticExpression {
  // abstract class for an arithmetic expression

 public:
  virtual void print (std::ostream & o) = 0;
  // pure virtual print function. Don't implement!
  virtual ~ArithmeticExpression(){};
  virtual int evaluate () const = 0;
  virtual void setValue (int value){};
};

class Addition : public ArithmeticExpression {
 public:
  Addition (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Addition ();
  
  virtual void print (std::ostream & o);
  // because the class is not abstract, we must implement print
  virtual int evaluate () const;

 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};

// add below other classes that are needed

class Subtraction : public ArithmeticExpression {
public:
  Subtraction (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Subtraction ();

  virtual void print (std::ostream & o);
  virtual int evaluate () const;

private:
  ArithmeticExpression *_ae1, *_ae2;
  int _lineNumber;
};

class Multiplication : public ArithmeticExpression {
public:
   Multiplication (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Multiplication ();

  virtual void print (std::ostream & o);
  virtual int evaluate () const;

private:
  ArithmeticExpression *_ae1, *_ae2;
};

class Division : public ArithmeticExpression {
public:
   Division (ArithmeticExpression *ae1, ArithmeticExpression *ae2 , int lineNumber);
  ~Division ();

  virtual void print (std::ostream & o);
  virtual int evaluate () const throw(int);


  ArithmeticExpression *_ae1, *_ae2;
private:
  int _lineNumber = 0;
};



//Above: Binary expressions... Below: Constant, Variable, ArrayVariable
class Constant : public ArithmeticExpression {
public:
 Constant (int Number);
 ~Constant ();
 
 virtual void print (std::ostream & o);
 virtual int evaluate () const;
 // because the class is not abstract, we must implement print
 
private:
 int _Number;
 stringstream ss;
};

class Variable : public ArithmeticExpression { // USE PROTECTED HERE?????????????????
public:
 Variable (string VariableName, map<string,int> *MapVariable);
 ~Variable ();
 virtual void print (std::ostream & o);
 // because the class is not abstract, we must implement print
 virtual int evaluate () const;
 virtual void setValue (int value);
 
private:
 string _VariableName; // the left and right term
 map <string, int>* _MapVariable;
};

class ArrayVariable : public ArithmeticExpression {
public:
  ArrayVariable (string ArrayName, ArithmeticExpression *ae, map<std::string,int> *MapArrayVariable); //??????????????
  ~ArrayVariable ();
  virtual void print (std::ostream & o);
  virtual int evaluate () const;
  virtual void setValue (int value);

private:
  string _ArrayName;
  ArithmeticExpression *_ae;
  map <string, int>* _MapArrayVariable;
  string _key;
};

#endif