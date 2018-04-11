#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <stdlib.h>
#include <stack>
#include "Command.h"

using namespace std;

bool FindOperation (char a);
bool ifNegative (string a);
bool FindBoolOperation (char a);
BooleanExpression* BEProcess (string passin, map<string,int> *MapVariable, map<string,int> *MapArrayVariable, int lineNumber);
ArithmeticExpression* AEProcess (string passin, map<string,int> *MapVariable, map<string,int> *MapArrayVariable, int lineNumber);
string truncate(string str);

class Interpreter {
public:
    Interpreter(int argc, char* argv[]);
    ~Interpreter();
    void Ini (int argc, char* argv[]);
    void Exe ();
    map<string,int> *MapVariable;
    map<string,int> *MapArrayVariable;
    stack<int> *GosubLines;
    

private:
    vector<Command*> *co;
    map<int,int> *whereDaLine; // < Original line numbe, the count of the line>
};

#endif