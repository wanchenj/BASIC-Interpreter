# BASIC-Interpreter


This is a partial BASIC parser and interpreter coded by me in C++. It can process Variables [VAR], Arithmetic Expressions [AEXPR], Boolean Expressions [BEXPR], and some of the most commonly used Commands: ([LINE] indicates current line number, [LINEJ] indicates the line we want to go to.)


  [LINE] PRINT [AEXPR]: prints the value of the arithmetic expression.
  
  [LINE] LET [VAR] [AEXPR]: writes the value of the arithmetic expression into the variable [VAR].
  
  [LINE] LET [VAR] [[AEXPR1]] [AEXPR2]: write the value of [AEXPR2] into the array [VAR] at the position [AEXPR1].
  
  [LINE] GOTO [LINEJ]: Jump to the line [LINEJ]
  
  [LINE] IF [BEXPR] THEN [LINEJ]: if the Boolen expression [BEXPR] is true, then jump to the line [LINEJ]
  
  [LINE] GOSUB [LINEJ]: Jump to the line [LINEJ], and remember where you came from.
  
  [LINE] RETURN: Go back to the line immediately after the line whence the most recent GOSUB jump started.
  
  [LINE] END: Terminate the execution of the program.
    
    
A sample BASIC line looks like this:
4 IF   XYZ  > 5    THEN 22


To compile:
Use the makefile provided.


To run: use command line to run
Basic_Intepreter
