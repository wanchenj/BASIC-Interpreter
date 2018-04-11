#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <stack>
#include "Command.h"
#include "Interpreter.h"


using namespace std;


Interpreter::Interpreter(int argc, char* argv[]){
    co = new vector <Command*> ;
    whereDaLine = new map <int,int>; // < Original line numbe, the count of the line>
    MapVariable = new map<string,int>;
    MapArrayVariable = new map<string,int>;
    GosubLines = new stack<int>;
    Ini (argc, argv);
    Exe ();
}
Interpreter::~Interpreter(){
    delete whereDaLine;
    delete MapVariable;
    delete MapArrayVariable;
    delete GosubLines;
    for (unsigned int i = 0; i < co -> size(); ++i){
        delete (*co)[i];
    }
    delete co;
}


void Interpreter::Ini (int argc, char* argv[]){
    if(argc < 2){
        cerr << "Please provide an input file." << endl;
        return;
      }
      ifstream input(argv[1]);
    
      string curr; // the current line
    
      // INITIATE ALL THE DATA STRUCTURES
      
      int CommandIndex = -1;
    
      //loop to read all lines of the program
      while(getline(input, curr)) {
          
          if (curr.length() == 0)
              continue;
          
        stringstream ss;
        ss << curr;
        string command; // the command
        unsigned int line;  // the line number
        
        ss >> line;
        ss >> command;
        //Storing in Co and WhereDaLine
        CommandIndex++;
        whereDaLine -> insert(pair<int,int>(line, CommandIndex));

        if (command == "PRINT") {
          // you obviously need to put a lot of stuff here and in the other cases
          string t = "";
          string whole = "";
          while (ss >> t){
            whole += t;
          }
            
            ArithmeticExpression* aeProcess = AEProcess (whole,MapVariable,MapArrayVariable,line);
            Command *a = new PrintCommand (line, aeProcess);
            a -> print(std::cout);
            co -> push_back(a);
            
          //!!delete a;
        }
        else if (command == "LET") {
          string var = "";
          string expr = "";
    
          string str = "";
          getline(ss, str);
          str = truncate(str);
    
          stringstream strm(str);
          strm >> var;
          getline(strm, expr);
       
          ArithmeticExpression *aeVar = AEProcess(var,MapVariable, MapArrayVariable, line);
          ArithmeticExpression *aeExpr = AEProcess(expr,MapVariable, MapArrayVariable, line);
    
          Let *let = new Let(line, aeVar, aeExpr);
          let -> print(std::cout);
          co -> push_back(let);
          //!!delete let;
        }
        else if (command == "GOTO") {
          int gotoline;
          ss >> gotoline;
          Command *b = new Goto (line, gotoline);
          b -> print(std::cout);
          co -> push_back(b);
          //!!delete b;
        }
        else if (command == "IF") {
          string add;
          string total;
          while (ss >> add){
            total += add;
          }
          //before then
          int thenindex = total.rfind("THEN");
          string bestring = total.substr(0,thenindex);
          BooleanExpression *g = BEProcess(bestring,MapVariable, MapArrayVariable, line);
          //after then
          string gotol = total.substr(thenindex + 4, total.length());
          int gotoline;
          stringstream ss0;
          ss0 << gotol;
          ss0 >> gotoline;
    
          Command * h = new IfThen(line, g, gotoline);
          h -> print(std::cout);
          co -> push_back(h);
          //!!delete h;
        }
        else if (command == "GOSUB") {
          int gotoline;
          ss >> gotoline;
          Command *c = new Gosub(line, gotoline);
          c -> print(std::cout);
          co -> push_back(c);
          //!!delete c;
        }
        else if (command == "RETURN") {
          Command *d = new ReturnCommand(line, 0);
          d -> print (std::cout);
          co -> push_back(d);
          //!!delete d;
        }
        else if (command == "END") {
          Command *e = new End(line);
          e -> print (std::cout);
          co -> push_back(e);
          //!!delete e;
        }
        else {
          // This should never happen - print an error?
          cout << "Invalid command on line " << line << endl;
        }
      }
      // FINISHED PRETTY PRINTING
      // NOW EVALUATE
      return;
}

void Interpreter::Exe (){

    for (unsigned int i = 0; i < co -> size(); ++i){
        if ((*co)[i] -> getID() == 1){ //PrintCommand

            try
            {
                cout << (*co)[i] -> getAE()->evaluate() << endl;
            }
            catch (int err)
            {
                break;
            }
        }
        else if ((*co)[i] -> getID() == 2){ //Let
          try
          {
              (*co)[i] -> getAE()->evaluate();
          }
          catch (int err)
          {
              break;
          }
            (*co)[i] -> getVAR() -> setValue((*co)[i] -> getAE() -> evaluate());
        }
        else if ((*co)[i] -> getID() == 3){ //IfThen
            if ((*co)[i] -> getBE() -> evaluate()){
                // cout << "Boolean is true" << endl;
                map<int,int>::iterator it;
                it = (whereDaLine -> find((*co)[i] -> getGOTOLINE()));
                if(it != whereDaLine -> end()){
                    i = it -> second - 1; 
                    continue;
                }
                else {
                    cout << "Error in Line " << (*co)[i] -> getLINENUMBER() << ": IF jump to non-existent line " 
                    << (*co)[i] -> getGOTOLINE() <<"." << endl;
                    break;
                }
            } 
        }
        else if ((*co)[i] -> getID() == 4){ //Goto
            map<int,int>::iterator it;
            it = (whereDaLine -> find((*co)[i] -> getGOTOLINE()));
            if(it != whereDaLine -> end()){
                i = it -> second - 1; 
                continue;
            }
            else {
                cout << "Error in Line " << (*co)[i] -> getLINENUMBER() << ": GOTO to non-existent line " 
                << (*co)[i] -> getGOTOLINE() <<"." << endl;
                break;
            }
        }
        else if ((*co)[i] -> getID() == 5){ //Gosub
            map<int,int>::iterator it;
            it = (whereDaLine -> find((*co)[i] -> getGOTOLINE()));
            if(it != whereDaLine -> end()){
                GosubLines -> push(i);
                i = it -> second - 1; 
                continue;
            }
            else {
                cout << "Error in Line " << (*co)[i] -> getLINENUMBER() << ": GOSUB to non-existent line " 
                << (*co)[i] -> getGOTOLINE() <<"." << endl;
                break;
            }
        }
        else if ((*co)[i] -> getID() == 6){ //ReturnCommand
            if (!GosubLines -> empty()){
                i = GosubLines -> top();
                GosubLines -> pop();
            }
            else{
                cout << "Error in Line " << (*co)[i] -> getLINENUMBER() << ": No matching GOSUB for RETURN." << endl;
                break;
            }
        }
        else if ((*co)[i] -> getID() == 7){ //End
            break;
        }
    }
}


// ALL HELPER FUNCTIONS START HERE

//AEProcess is a recursive function only used in Interpreter::ini()
ArithmeticExpression* AEProcess (string passin, 
    map<string,int> *MapVariable, map<string,int> *MapArrayVariable, int lineNumber){
    
      stringstream ss;
    //middle split method
    //check first and last characters, if no () around
    char front;
    char back;
    int fp = -1;
    int bp = -1;
    for (unsigned int i = 0; i < passin.length(); ++i){
      if (passin[i] != ' '){
        front = passin[i];
        if (front == '('){
          fp = i;
        }
        break;
      }
    }
    for (int i = passin.length()-1; i >= 0; --i){
      if (passin[i] != ' '){
        back = passin[i];
        if (back == ')'){
          bp = i;
        }
        break;
      }
    }
  
    //base case
    ArithmeticExpression* aerec = NULL;
    if (front != '(' && back != ')'){ 
      ss << passin;
      int n;
      string varstr;
  
      if (ss >> n){
        aerec = new Constant(n);
        return aerec;
      }
      else{
        int firstIndex, lastIndex;
        for (unsigned int i = 0; i < passin.length(); ++i){
            if (passin[i] != ' '){
                firstIndex = i;
                break;
            }
        }
        for (unsigned int i = passin.length() - 1; i >= 0; --i){
            if (passin[i] != ' '){
                lastIndex = i;
                break;
            }
        }
        //Got rid of spaces on two sides
        varstr = passin.substr(firstIndex, lastIndex-firstIndex+1);
        if (varstr[varstr.length()-1] != ']'){
            aerec = new Variable(varstr, MapVariable);
            return aerec;
        }
        //only when there is a closed ']', find open '['
        for (unsigned int i = 0; i < varstr.length(); ++i){
            if (varstr[i] == '['){
                string partvarstr = varstr.substr(0,i); //no space in front, might be space in back
                stringstream ss2;
                ss2 << partvarstr;
                string partvar; //no extra spaces
                ss2 >> partvar;
                //extract ArrayVariable index
                string partindstr = varstr.substr(i+1, (varstr.length()-i-2));
  
                aerec = new ArrayVariable(partvar, AEProcess(partindstr
                  ,MapVariable, MapArrayVariable, lineNumber), MapArrayVariable);
                return aerec;
            }
        }
      }
    }
  
    //recursion
    int openp = 0;
    int closep = 0;
    int midIndex;
    for (unsigned int i = 0; i < passin.length(); ++i){
      if (passin[i] == '('){
        openp++;
      }
      else if (passin[i] == ')'){
        closep++;
      }
      else if (FindOperation(passin[i]) && !ifNegative(passin.substr(0, i)) && (openp == closep + 1)){
        midIndex = i;
        if (passin[i] == '+'){
          aerec = new Addition (AEProcess(passin.substr(fp + 1, midIndex - fp - 1)
          ,MapVariable, MapArrayVariable, lineNumber),
          AEProcess(passin.substr(midIndex + 1, bp - midIndex - 1)
          ,MapVariable, MapArrayVariable, lineNumber));
          return aerec;
        }
        else if (passin[i] == '-'){
          aerec = new Subtraction (AEProcess(passin.substr(fp + 1, midIndex - fp - 1)
          ,MapVariable, MapArrayVariable, lineNumber),
          AEProcess(passin.substr(midIndex + 1, bp - midIndex - 1)
          ,MapVariable, MapArrayVariable, lineNumber));
          return aerec;
        }
        else if (passin[i] == '*'){
          aerec = new Multiplication (AEProcess(passin.substr(fp + 1, midIndex - fp - 1)
          ,MapVariable, MapArrayVariable, lineNumber),
          AEProcess(passin.substr(midIndex + 1, bp - midIndex - 1)
          ,MapVariable, MapArrayVariable, lineNumber));
          return aerec;
        }
        else{
              aerec = new Division (
                AEProcess(passin.substr(fp + 1, midIndex - fp - 1) ,MapVariable, MapArrayVariable, lineNumber),
                AEProcess(passin.substr(midIndex + 1, bp - midIndex - 1),MapVariable, MapArrayVariable, lineNumber),
                lineNumber);
          return aerec;
        }
        break;
      }
    }
    return aerec;
  }
  
  BooleanExpression* BEProcess (string passin
    ,map<string,int> *MapVariable, map<string,int> *MapArrayVariable, int lineNumber){
    int MidIndex = -1;
    for (unsigned i = 0; i < passin.length(); ++i){
      if (FindBoolOperation(passin[i])){
        MidIndex = i;
        break;
      }
    }
    BooleanExpression *berec = NULL;

    if(passin.length() > 0 && passin[0] == '[') {
      passin = passin.substr(1, passin.length() - 2);
      MidIndex--;
    }
    if (passin[MidIndex] == '>'){
      berec = new Greater (AEProcess(passin.substr(0,MidIndex)
      ,MapVariable, MapArrayVariable, lineNumber), 
      AEProcess(passin.substr(MidIndex+1)
      ,MapVariable, MapArrayVariable, lineNumber));
      return berec;
    }
    if (passin[MidIndex] == '<'){
      berec = new Less (AEProcess(passin.substr(0,MidIndex)
      ,MapVariable, MapArrayVariable, lineNumber), 
      AEProcess(passin.substr(MidIndex+1)
      ,MapVariable, MapArrayVariable, lineNumber));
      return berec;
    }
    if (passin[MidIndex] == '='){
      berec = new IfEqual (AEProcess(passin.substr(0,MidIndex)
      ,MapVariable, MapArrayVariable, lineNumber), 
      AEProcess(passin.substr(MidIndex+1)
      ,MapVariable, MapArrayVariable, lineNumber));
      return berec;
    }
    return berec;
  }
  
  bool FindOperation (char a){
    if (a == '+' || a == '-' || a == '*' || a == '/'){
      return true;
    }
    return false;
  }
  
  bool FindBoolOperation (char a){
    if (a == '>' || a == '<' || a == '='){
      return true;
    }
    return false;
  }
  
  bool ifNegative (string a){
    for (int i = a.length()-1; i >= 0; ++i){
        if (a[i] != ' '){
            if (a[i] == '('){
                return true;
            }
            return false;
        }
    }
    return false;
  }
  
  string truncate(string str) {
    while(str.length() > 0 && str[0] == ' ') {
      str.erase(str.begin());
    }
    while(str.length() > 0 && str[str.length() - 1] == ' ') {
      str.erase(str.begin() + str.length() - 1);
    }
    if(str == "") return str;
    for(int i = str.size() - 1; i > 0; i--) {
      if(str[i] == ' ' && str[i - 1] == ' ') {
        str.erase(str.begin() + i);
      }
    }
  
    for(unsigned i = 0; i < str.length(); i++) {
      if(i > 0 && i < str.length() - 1 && str[i] == ' ' && str[i + 1] == '[') {
        str.erase(str.begin() + i);
      }
    }
  
    int inside = 0;
    for(unsigned i = 0; i < str.length(); i++) {
      if(str[i] == '[') inside++;
      else if(str[i] == ']') inside--;
      else if(str[i] == ' ' && inside > 0) {
        str.erase(str.begin() + i);
        i--;
      }
    }
  
    return str;
  }
