#include "Command.h"

//PrintCommand
PrintCommand::PrintCommand (int lineNumber, ArithmeticExpression *ae)
{
  _lineNumber = lineNumber;
  _ae = ae;
  ID = 1;
}

PrintCommand::~PrintCommand ()
{
  delete _ae;
}
  
void PrintCommand::print (std::ostream & o) const
{
  o << _lineNumber << " PRINT ";
  _ae->print (o);
  o << endl;
}

int PrintCommand::getLINENUMBER () const{
    return _lineNumber;
}
ArithmeticExpression* PrintCommand::getAE () const{
    return _ae;
}

//Let
Let::Let (int lineNumber, ArithmeticExpression *var, ArithmeticExpression *ae)
{
    _lineNumber = lineNumber;
    _var = var;
    _ae = ae;
    ID = 2;
}
Let::~Let ()
{
    delete _var;
    delete _ae;
}
void Let::print (std::ostream & o) const 
{
    o << _lineNumber << " LET ";
    _var->print (o);
    o << " ";
    _ae->print (o);
    o << endl;
}

int Let::getLINENUMBER () const{
    return _lineNumber;
}
ArithmeticExpression* Let::getAE () const{
    return _ae;
}
ArithmeticExpression* Let::getVAR () const{
    return _var;
}

//IfThen
IfThen::IfThen (int lineNumber, BooleanExpression *be, int gotoline){
    _lineNumber = lineNumber;
    _be = be;
    _gotoline = gotoline;
    ID = 3;
}
IfThen::~IfThen (){
    delete _be;
}
void IfThen::print (std::ostream & o) const {
    o << _lineNumber << " IF ";
    _be->print (o);
    o << " THEN <" << _gotoline << ">" << endl;
}

int IfThen::getLINENUMBER () const{
    return _lineNumber;
}
BooleanExpression* IfThen::getBE () const{
    return _be;
}
int IfThen::getGOTOLINE () const{
    return _gotoline;
}

//Goto
Goto::Goto (int lineNumber, int gotoline){
    _lineNumber = lineNumber;
    _gotoline = gotoline;
    ID = 4;
}
Goto::~Goto (){}
void Goto::print (std::ostream & o) const {
    o << _lineNumber << " GOTO <" << _gotoline << ">" << endl;
}

int Goto::getLINENUMBER () const{
    return _lineNumber;
}
int Goto::getGOTOLINE () const{
    return _gotoline;
}

//Gosub
Gosub::Gosub(int lineNumber, int jumptoline){
    _lineNumber = lineNumber;
    _jumptoline = jumptoline;
    ID = 5;
}
Gosub::~Gosub(){}
void Gosub::print (std::ostream & o) const {
    o << _lineNumber << " GOSUB <" << _jumptoline << ">" << endl;
}

int Gosub::getLINENUMBER () const{
    return _lineNumber;
}
int Gosub::getGOTOLINE () const{
    return _jumptoline;
}

//ReturnCommand
ReturnCommand::ReturnCommand(int lineNumber, int gobackline){
    _lineNumber = lineNumber;
    _gobackline = gobackline;
    ID = 6;
}
ReturnCommand::~ReturnCommand(){}
void ReturnCommand::print (std::ostream & o) const {
    o << _lineNumber << " RETURN" << endl;
}

int ReturnCommand::getLINENUMBER () const{
    return _lineNumber;
}

//End
End::End(int lineNumber){
    _lineNumber = lineNumber;
    ID = 7;
}
End::~End(){}
void End::print (std::ostream & o) const {
    o << _lineNumber << " END" << endl;
}

int End::getLINENUMBER () const{
    return _lineNumber;
}
