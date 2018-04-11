#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
//#include "ArithmeticExpression.h"
#include "BooleanExpression.h"

class Command {
  // abstract class for a BASIC Command

 public:
  virtual ~Command(){};
  virtual void print (std::ostream & o) const = 0;
  // pure virtual print function. Don't implement!
  int getID(){
    return ID;
  }

  virtual int getLINENUMBER () const {return -1;};
  virtual ArithmeticExpression* getAE () const {return NULL;};
  virtual ArithmeticExpression* getVAR () const {return NULL;};
  virtual BooleanExpression* getBE() const {return NULL;};
  virtual int getGOTOLINE () const {return -1;};

 protected:
  int ID = 0;
};

// add below other classes that are needed
/*
<LINE> PRINT <AEXPR>: prints the value of the arithmetic expression.
<LINE> LET <VAR> <AEXPR>: writes the value of the arithmetic expression into the variable <VAR>.
<LINE> LET <VAR> [<AEXPR1>] <AEXPR2>: write the value of <AEXPR2> into the array <VAR> at the position <AEXPR1>.
<LINE> GOTO <LINEJ>: Jump to the line <LINEJ>
<LINE> IF <BEXPR> THEN <LINEJ>: if the Boolen expression <BEXPR> is true, then jump to the line <LINEJ>
<LINE> GOSUB <LINEJ>: Jump to the line <LINEJ>, and remember where you came from.
<LINE> RETURN: Go back to the line immediately after the line whence the most recent GOSUB jump started.
<LINE> END: Terminate the execution of the program.*/

class PrintCommand: public Command {
public:
  PrintCommand (int lineNumber,ArithmeticExpression *ae);
  ~PrintCommand ();
  virtual void print (std::ostream & o) const;

  virtual int getLINENUMBER () const;
  virtual ArithmeticExpression* getAE () const;
  
private:
  int _lineNumber;
  ArithmeticExpression *_ae;
};

class Let: public Command {
public:
  Let (int lineNumber, ArithmeticExpression *var, ArithmeticExpression *ae);
  ~Let ();
  virtual void print (std::ostream & o) const;

  virtual int getLINENUMBER () const;
  virtual ArithmeticExpression* getAE () const;
  virtual ArithmeticExpression* getVAR () const;
private:
  int _lineNumber;
  ArithmeticExpression *_var;
  ArithmeticExpression *_ae;
};

class IfThen: public Command {
public:
  IfThen (int lineNumber, BooleanExpression *be, int gotoline);
  ~IfThen ();
  virtual void print (std::ostream & o) const;

  virtual int getLINENUMBER () const;
  virtual BooleanExpression* getBE() const;
  virtual int getGOTOLINE () const;
private:
  int _lineNumber;
  BooleanExpression *_be;
  int _gotoline;
};

class Goto: public Command {
public:
  Goto (int lineNumber, int gotoline);
  ~Goto ();
  virtual void print (std::ostream & o) const;

  virtual int getLINENUMBER () const;
  virtual int getGOTOLINE () const;
private:
  int _lineNumber;
  int _gotoline;
};

class Gosub: public Command {
public:
  Gosub (int lineNumber, int jumptoline);
  ~Gosub ();
  virtual void print(std::ostream & o) const;

  virtual int getLINENUMBER () const;
  virtual int getGOTOLINE () const;
private:
  int _lineNumber;
  int _jumptoline;
};

class ReturnCommand: public Command {
public:
  ReturnCommand (int lineNumber, int gobackline);
  ~ReturnCommand ();
  virtual void print(std::ostream & o) const;
  virtual int getLINENUMBER () const;
private:
  int _lineNumber;
  int _gobackline;
};

class End: public Command {
public:
  End (int lineNumber);
  ~End ();
  virtual void print(std::ostream & o) const;
  virtual int getLINENUMBER () const;
private:
  int _lineNumber;
};

#endif